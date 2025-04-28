#include "ModbusServant.h"
#include <c-bsp-interface/memory/StackHeap.h>
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
#include <c-bsp-interface/modbus/ModbusBufferReader.h>
#include <c-bsp-interface/modbus/ModbusCrc16.h>
#include <c-bsp-interface/modbus/ModbusFunctionCode.h>
#include <c-bsp-interface/modbus/ModbusStreamWriter.h>
#include <c-bsp-interface/stream/MemoryStream.h>

/// @brief modbus 从机
typedef struct ModbusServant
{
	/// @brief 从机站号
	uint8_t _servant_address;
	ModbusCrc16 *_crc;
	bsp_endian_t _crc16_endian;
	ModbusBitConverterUnit _bit_converter_unit;
	MemoryStream *_send_buffer_memory_stream;
	ModbusStreamWriter *_writer;

#pragma region 读写回调函数
	ModbusMultibyteSizeEnum (*GetMultibyteDataSize)(uint32_t data_addr);
	void (*SendResponse)(uint8_t *buffer, int32_t offset, int32_t count);

	uint16_t (*Read2ByteCallback)(uint32_t data_addr);
	uint32_t (*Read4ByteCallback)(uint32_t data_addr);
	uint64_t (*Read8ByteCallback)(uint32_t data_addr);

	void (*Write2ByteCallback)(uint32_t data_addr, uint16_t value);
	void (*Write4ByteCallback)(uint32_t data_addr, uint32_t value);
	void (*Write8ByteCallback)(uint32_t data_addr, uint64_t value);

	uint8_t (*ReadBitCallback)(uint32_t data_addr);
	void (*WriteBitCallback)(uint32_t data_addr, uint8_t value);
#pragma endregion

} ModbusServant;

static void CalculateAndWriteCrc16ToMemoryStream(ModbusServant *self)
{
	ModbusCrc16_ResetRegister(self->_crc);
	ModbusCrc16_AddArray(self->_crc,
						 MemoryStream_Buffer(self->_send_buffer_memory_stream),
						 MemoryStream_Position(self->_send_buffer_memory_stream));

	ModbusStreamWriter_WriteCrc16(self->_writer,
								  ModbusCrc16_Register(self->_crc),
								  self->_crc16_endian);
}

/// @brief 读一组线圈
/// @param self
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void ReadCoils(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
	ModbusBufferReader reader;
	ModbusBufferReader_Init(&reader, pdu + 1, self->_bit_converter_unit);

	// 起始位地址
	uint16_t start_bit_addr = ModbusBufferReader_ReadUInt16(&reader);

	// 位数据个数
	int32_t bit_count = ModbusBufferReader_ReadUInt16(&reader);

#pragma region 准备响应帧
	// 清空发送缓冲区
	MemoryStream_Clear(self->_send_buffer_memory_stream);

	// 放入站号
	MemoryStream_Write(self->_send_buffer_memory_stream,
					   &self->_servant_address, 0, 1);

	// 放入功能码
	ModbusStreamWriter_WriteUInt8(self->_writer, ModbusFunctionCode_ReadCoils);

	// 放入数据字节数
	uint8_t byte_count = bit_count / 8;
	if (bit_count % 8 != 0)
	{
		byte_count++;
	}

	ModbusStreamWriter_WriteUInt8(self->_writer, byte_count);
#pragma endregion

#pragma region 放入位数据
	// 能被 8 整除的部分先每 8 个位为一组
	for (int group = 0; group < bit_count / 8; group++)
	{
		uint8_t bit_register = 0;
		for (int i = 0; i < 8; i++)
		{
			// 每个位的地址比前一个位增加 1
			uint8_t bit_value = self->ReadBitCallback(start_bit_addr + group * 8 + i);
			if (bit_value)
			{
				bit_register |= 1 << (i % 8);
			}
		}

		ModbusStreamWriter_WriteUInt8(self->_writer, bit_register);
	}

	// 剩下几个位，不够被 8 整除
	uint8_t bit_register = 0;
	for (int i = 0; i < bit_count % 8; i++)
	{
		// 每个位的地址比前一个位增加 1
		uint8_t bit_value = self->ReadBitCallback(start_bit_addr + (bit_count / 8) * 8 + i);
		if (bit_value)
		{
			bit_register |= 1 << (i % 8);
		}
	}

	ModbusStreamWriter_WriteUInt8(self->_writer, bit_register);
#pragma endregion

	CalculateAndWriteCrc16ToMemoryStream(self);

	// 发送响应帧
	self->SendResponse(MemoryStream_Buffer(self->_send_buffer_memory_stream),
					   0,
					   MemoryStream_Position(self->_send_buffer_memory_stream));
}

/// @brief 读取一组输入位
/// @param self
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void ReadInputBits(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
	ReadCoils(self, pdu, pdu_size);
}

/// @brief 读一组保持寄存器
/// @param self
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void ReadHoldingRegisters(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
	ModbusBufferReader reader;
	ModbusBufferReader_Init(&reader, pdu + 1, self->_bit_converter_unit);

	// 起始记录地址
	uint16_t start_record_addr = ModbusBufferReader_ReadUInt16(&reader);

	// 要读取的记录数
	int32_t record_count = ModbusBufferReader_ReadUInt16(&reader);

#pragma region 准备响应帧
	// 清空发送缓冲区
	MemoryStream_Clear(self->_send_buffer_memory_stream);

	// 放入站号
	ModbusStreamWriter_WriteUInt8(self->_writer, self->_servant_address);

	// 放入功能码
	ModbusStreamWriter_WriteUInt8(self->_writer, ModbusFunctionCode_ReadHoldingRegisters);

	// 放入数据字节数
	ModbusStreamWriter_WriteUInt8(self->_writer, record_count * 2);
#pragma endregion

#pragma region 放入数据
	int32_t record_addr_offset = 0;
	while (1)
	{
		if (record_addr_offset == record_count)
		{
			// 主机要读的数据已经全部读完了
			break;
		}

		if (record_addr_offset > record_count)
		{
			// 超出了就不对了，说明上位机想要读取的记录数与本从机的数据大小不符，上位机错了
			// TODO: 发回例外响应。
			return;
		}

		int32_t current_record_addr = start_record_addr + record_addr_offset;
		ModbusMultibyteSizeEnum current_data_size_enum = self->GetMultibyteDataSize(current_record_addr);
		switch (current_data_size_enum)
		{
		case ModbusMultibyteSizeEnum_2Byte:
			{
				uint16_t data = self->Read2ByteCallback(current_record_addr);
				ModbusStreamWriter_WriteUInt16(self->_writer, data);
				record_addr_offset += 1;
				break;
			}
		case ModbusMultibyteSizeEnum_4Byte:
			{
				uint32_t data = self->Read4ByteCallback(current_record_addr);
				ModbusStreamWriter_WriteUInt32(self->_writer, data);
				record_addr_offset += 2;
				break;
			}
		case ModbusMultibyteSizeEnum_8Byte:
			{
				uint64_t data = self->Read8ByteCallback(current_record_addr);
				ModbusStreamWriter_WriteUInt64(self->_writer, data);
				record_addr_offset += 4;
				break;
			}
		default:
			{
				// 不支持的数据大小。
				// 从机出错了，GetMultibyteDataSize 回调函数的返回值不能不在 ModbusMultibyteSizeEnum 的范围内。
				while (1)
				{
					// 卡在死循环，便于调试的时候发现错误
				}
			}
		}
	}
#pragma endregion

	CalculateAndWriteCrc16ToMemoryStream(self);

	// 发送响应帧
	self->SendResponse(MemoryStream_Buffer(self->_send_buffer_memory_stream),
					   0,
					   MemoryStream_Position(self->_send_buffer_memory_stream));
}

/// @brief 读取一组输入寄存器
/// @param self
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void ReadInputRegisters(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
	ReadHoldingRegisters(self, pdu, pdu_size);
}

/// @brief 写单个线圈
/// @param self
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void WriteSingleCoil(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
#pragma region 获取请求信息
	ModbusBufferReader reader;
	ModbusBufferReader_Init(&reader, pdu + 1, self->_bit_converter_unit);

	// 位地址
	uint16_t bit_addr = ModbusBufferReader_ReadUInt16(&reader);

	// 位数据。0x0000 表示 OFF，0xff00 表示 ON
	int32_t bit_data = ModbusBufferReader_ReadUInt16(&reader);

	uint8_t bit_value;
	if (bit_data == 0x0000)
	{
		bit_value = 0;
	}
	else if (bit_data == 0xff00)
	{
		bit_value = 1;
	}
	else
	{
		// 非法的数据
		// 0x0000 表示 OFF，0xff00 表示 ON，其他的都是非法的
		// TODO: 发回例外响应
		return;
	}
#pragma endregion

	self->WriteBitCallback(bit_addr, bit_value);

#pragma region 准备响应帧
	// 清空发送缓冲区
	MemoryStream_Clear(self->_send_buffer_memory_stream);

	// 放入站号
	ModbusStreamWriter_WriteUInt8(self->_writer, self->_servant_address);

	// 放入功能码
	ModbusStreamWriter_WriteUInt8(self->_writer, ModbusFunctionCode_WriteSingleCoil);

	// 放入位地址
	ModbusStreamWriter_WriteUInt16(self->_writer, bit_addr);

	// 放入位数据
	ModbusStreamWriter_WriteUInt16(self->_writer, bit_value ? 0xff00 : 0x0000);
#pragma endregion

	CalculateAndWriteCrc16ToMemoryStream(self);

	// 发送响应帧
	self->SendResponse(MemoryStream_Buffer(self->_send_buffer_memory_stream),
					   0,
					   MemoryStream_Position(self->_send_buffer_memory_stream));
}

/// @brief 检查主机发过来的位数据个数和字节数是否对应。
/// @param bit_count
/// @param byte_count
/// @return 对应则返回 true，否则返回 false.
static uint8_t WriteCoils_CheckByteCount(int32_t bit_count, int32_t byte_count)
{
	int32_t calculated_byte_count = bit_count / 8;
	if (bit_count % 8 != 0)
	{
		calculated_byte_count++;
	}

	return calculated_byte_count == byte_count;
}

/// @brief 写一组线圈
/// @param self
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void WriteCoils(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
#pragma region 获取请求信息
	ModbusBufferReader reader;
	ModbusBufferReader_Init(&reader, pdu + 1, self->_bit_converter_unit);

	// 起始位地址
	uint16_t start_bit_addr = ModbusBufferReader_ReadUInt16(&reader);

	// 位数据个数
	int32_t bit_count = ModbusBufferReader_ReadUInt16(&reader);

	// 数据字节数
	int32_t byte_count = ModbusBufferReader_ReadUInt8(&reader);

	if (!WriteCoils_CheckByteCount(bit_count, byte_count))
	{
		// TODO: 例外响应
		return;
	}
#pragma endregion

	for (int32_t i = 0; i < byte_count; i++)
	{
		// 获取储存着位数据的字节
		int32_t bits = ModbusBufferReader_ReadUInt8(&reader);
		for (int32_t j = 0; j < 8; j++)
		{
			int32_t current_bit_addr_offset = i * 8 + j;
			int32_t current_bit_addr = start_bit_addr + current_bit_addr_offset;
			uint8_t mask = (uint8_t)1 << j;
			self->WriteBitCallback(current_bit_addr, bits & mask);
		}
	}

#pragma region 准备响应帧
	// 清空发送缓冲区
	MemoryStream_Clear(self->_send_buffer_memory_stream);

	// 放入站号
	ModbusStreamWriter_WriteUInt8(self->_writer, self->_servant_address);

	// 放入功能码
	ModbusStreamWriter_WriteUInt8(self->_writer, ModbusFunctionCode_ReadCoils);

	ModbusStreamWriter_WriteUInt16(self->_writer, start_bit_addr);
	ModbusStreamWriter_WriteUInt16(self->_writer, bit_count);
#pragma endregion

	CalculateAndWriteCrc16ToMemoryStream(self);

	// 发送响应帧
	self->SendResponse(MemoryStream_Buffer(self->_send_buffer_memory_stream),
					   0,
					   MemoryStream_Position(self->_send_buffer_memory_stream));
}

/// @brief WriteHoldingRegisters 用来检查数据字节数是否合法。
/// @param record_count
/// @param byte_count
/// @return 合法返回 true，非法返回 false.
static uint8_t WriteHoldingRegisters_CheckByteCount(int32_t record_count, int32_t byte_count)
{
	return record_count * 2 == byte_count;
}

/// @brief 写一组保持寄存器
/// @param self
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void WriteHoldingRegisters(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
#pragma region 获取请求信息
	// 信息域缓冲区
	uint8_t *info_buffer = pdu + 1;
	int32_t info_buffer_offset = 0;

	// 起始记录地址
	uint16_t start_record_addr = ModbusBitConverter_ToUInt16(ModbusBitConverterUnit_Whole,
															 info_buffer,
															 info_buffer_offset);
	info_buffer_offset += 2;

	// 要读取的记录数
	int32_t record_count = ModbusBitConverter_ToUInt16(ModbusBitConverterUnit_Whole,
													   info_buffer,
													   info_buffer_offset);
	info_buffer_offset += 2;

	// 数据字节数
	int32_t byte_count = ModbusBitConverter_ToUInt8(ModbusBitConverterUnit_Whole,
													info_buffer,
													info_buffer_offset);
	info_buffer_offset += 1;

	if (!WriteHoldingRegisters_CheckByteCount(record_count, byte_count))
	{
		// TODO: 例外响应
		return;
	}
#pragma endregion

	int32_t record_addr_offset = 0;
	while (1)
	{
		if (record_addr_offset == record_count)
		{
			break;
		}

		if (record_addr_offset > record_count)
		{
			return;
		}

		int32_t current_record_addr = start_record_addr + record_addr_offset;
		ModbusMultibyteSizeEnum current_data_size_enum = self->GetMultibyteDataSize(current_record_addr);
		switch (current_data_size_enum)
		{
		case ModbusMultibyteSizeEnum_2Byte:
			{
				uint16_t value = ModbusBitConverter_ToUInt16(ModbusBitConverterUnit_Whole,
															 info_buffer,
															 info_buffer_offset);
				info_buffer_offset += 2;
				self->Write2ByteCallback(current_record_addr, value);
				record_addr_offset += 1;
				break;
			}
		case ModbusMultibyteSizeEnum_4Byte:
			{
				uint32_t value = ModbusBitConverter_ToUInt32(ModbusBitConverterUnit_Whole,
															 info_buffer,
															 info_buffer_offset);
				info_buffer_offset += 4;
				self->Write4ByteCallback(current_record_addr, value);
				record_addr_offset += 2;
				break;
			}
		case ModbusMultibyteSizeEnum_8Byte:
			{
				uint64_t value = ModbusBitConverter_ToUInt64(ModbusBitConverterUnit_Whole,
															 info_buffer,
															 info_buffer_offset);
				info_buffer_offset += 8;
				self->Write8ByteCallback(current_record_addr, value);
				record_addr_offset += 4;
				break;
			}
		default:
			{
				// 不支持的数据大小。
				// 从机出错了，GetMultibyteDataSize 回调函数的返回值不能不在 ModbusMultibyteSizeEnum 的范围内。
				while (1)
				{
					// 卡在死循环，便于调试的时候发现错误
				}
			}
		}
	}

#pragma region 准备响应帧
	// 清空发送缓冲区
	MemoryStream_Clear(self->_send_buffer_memory_stream);

	// 放入站号
	ModbusStreamWriter_WriteUInt8(self->_writer, self->_servant_address);

	// 放入功能码
	ModbusStreamWriter_WriteUInt8(self->_writer, ModbusFunctionCode_ReadHoldingRegisters);

	ModbusStreamWriter_WriteUInt16(self->_writer, start_record_addr);
	ModbusStreamWriter_WriteUInt16(self->_writer, record_count);
#pragma endregion

	CalculateAndWriteCrc16ToMemoryStream(self);

	// 发送响应帧
	self->SendResponse(MemoryStream_Buffer(self->_send_buffer_memory_stream),
					   0,
					   MemoryStream_Position(self->_send_buffer_memory_stream));
}

/// @brief 诊断
/// @param self
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void Diagnosis(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
}

/// @brief 处理普通的 PDU
/// @note 被调用说明 CRC 校验通过了。
///
/// @param self
/// @param pdu modbus PDU
/// @param pdu_size pdu 的字节数
static void HandlePdu(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
	if (pdu_size < 1)
	{
		// PDU 只有一个功能码，此操作没有意义
		return;
	}

	ModbusFunctionCode function_code = pdu[0];
	switch (function_code)
	{
	case ModbusFunctionCode_ReadCoils:
		{
			// 读取一组线圈
			ReadCoils(self, pdu, pdu_size);
			break;
		}
	case ModbusFunctionCode_ReadInputBits:
		{
			// 读取一组输入位
			ReadInputBits(self, pdu, pdu_size);
			break;
		}
	case ModbusFunctionCode_ReadHoldingRegisters:
		{
			// 读取一组保持寄存器
			ReadHoldingRegisters(self, pdu, pdu_size);
			break;
		}
	case ModbusFunctionCode_ReadInputRegisters:
		{
			// 读取一组输入寄存器
			ReadInputRegisters(self, pdu, pdu_size);
			break;
		}
	case ModbusFunctionCode_WriteSingleCoil:
		{
			// 写单个线圈
			WriteSingleCoil(self, pdu, pdu_size);
			break;
		}
	case ModbusFunctionCode_WriteCoils:
		{
			// 写入一组线圈
			WriteCoils(self, pdu, pdu_size);
			break;
		}
	case ModbusFunctionCode_WriteHoldingRegisters:
		{
			// 写入多个保持寄存器
			WriteHoldingRegisters(self, pdu, pdu_size);
			break;
		}
	case ModbusFunctionCode_Diagnosis:
		{
			// 诊断
			Diagnosis(self, pdu, pdu_size);
			break;
		}
	}
}

/// @brief 处理广播的 PDU
/// @note 被调用说明 CRC 校验通过了。
///
/// @param self
/// @param pdu modbus PDU
/// @param pdu_size pdu 的字节数
static void HandleBrocastPdu(ModbusServant *self, uint8_t *pdu, int32_t pdu_size)
{
	HandlePdu(self, pdu, pdu_size);
}

ModbusServant *ModbusServant_StackHeapAlloc(uint8_t servant_address,
											bsp_endian_t crc16_endian,
											ModbusBitConverterUnit bit_converter_unit,
											ModbusServantReadWriteCallbackHub *read_write_callback_hub)
{
	ModbusServant *o = StackHeapObjAlloc(sizeof(ModbusServant));
	o->_servant_address = servant_address;
	o->_crc16_endian = crc16_endian;
	o->_bit_converter_unit = bit_converter_unit;
	o->_send_buffer_memory_stream = MemoryStream_StackHeapAlloc(512);
	o->_writer = ModbusStreamWriter_StackHeapAlloc(MemoryStream_AsStream(o->_send_buffer_memory_stream),
												   o->_bit_converter_unit);

#pragma region 读写数据回调函数
	o->GetMultibyteDataSize = read_write_callback_hub->GetMultibyteDataSize;
	o->SendResponse = read_write_callback_hub->SendResponse;

	o->Read2ByteCallback = read_write_callback_hub->Read2ByteCallback;
	o->Read4ByteCallback = read_write_callback_hub->Read4ByteCallback;
	o->Read8ByteCallback = read_write_callback_hub->Read8ByteCallback;

	o->Write2ByteCallback = read_write_callback_hub->Write2ByteCallback;
	o->Write4ByteCallback = read_write_callback_hub->Write4ByteCallback;
	o->Write8ByteCallback = read_write_callback_hub->Write8ByteCallback;

	o->ReadBitCallback = read_write_callback_hub->ReadBitCallback;
	o->WriteBitCallback = read_write_callback_hub->WriteBitCallback;
#pragma endregion

	o->_crc = ModbusCrc16_StackHeapAlloc();
	return o;
}

void ModbusServant_ParseReceivedBuffer(ModbusServant *self,
									   uint8_t *buffer, int32_t offset, int32_t size)
{
	if (size <= 3)
	{
		/* ADU 比 PDU 多出来 3 个字节。其中 CRC16 占用 2 个字节，站号占用 1 个字节。
		 * 如果整个 ADU 的大小小于等于 3，说明 PDU 为空，这种帧没有意义。
		 */
		return;
	}

	uint8_t *adu = buffer + offset;
	if (adu[0] != self->_servant_address && adu[0] != 0)
	{
		// 站号与本站号不匹配，且不等于 0，即不是广播帧。
		return;
	}

	// 站号匹配或者是广播帧
	// 进行 CRC 校验
	ModbusCrc16_ResetRegister(self->_crc);
	ModbusCrc16_AddArray(self->_crc, adu, size - 2);
	uint8_t crc16_check_result = ModbusCrc16_CompareRegister(self->_crc,
															 adu + size - 2,
															 self->_crc16_endian);
	if (!crc16_check_result)
	{
		// CRC 校验错误时从机应该沉默。
		return;
	}

	// CRC 校验通过
	// PDU 包括功能码和信息域。
	// ADU 去掉头部 1 个字节的站号和尾部 2 个字节的 CRC16 后就变成 PDU。
	uint8_t *pdu = adu + 1;

	// PDU 比起 ADU 少了 1 个字节的站号和 2 个字节的 CRC16。
	int32_t pdu_size = size - 3;
	if (adu[0] == 0)
	{
		// 广播帧
		HandleBrocastPdu(self, pdu, pdu_size);
		return;
	}

	// 普通帧
	HandlePdu(self, pdu, pdu_size);
}
