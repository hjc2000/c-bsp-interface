#include "ModbusServant.h"
#include <c-bsp-interface/container/Stack.h>
#include <c-bsp-interface/memory/StackHeap.h>
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
#include <c-bsp-interface/modbus/ModbusCrc16.h>
#include <c-bsp-interface/modbus/ModbusFunctionCode.h>

/// @brief modbus 从机
typedef struct ModbusServant
{
	/// @brief 从机站号
	uint8_t _servant_address;
	ModbusCrc16 _crc;
	Endian _crc16_endian;
	ModbusBitConverterUnit _bit_converter_unit;

	/// @brief 发送缓冲区。将各种不同大小的数据入栈，最后就可以将整个缓冲区从栈底开始发送出去。
	Stack *_send_buffer_stack;

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

static void CalculateAndPushCrc16(ModbusServant *o)
{
	ModbusCrc16_ResetRegister(&o->_crc);
	ModbusCrc16_AddArray(&o->_crc,
						 Stack_Buffer(o->_send_buffer_stack),
						 Stack_Sp(o->_send_buffer_stack));

	uint8_t crc16_high_byte = ModbusCrc16_HighByte(&o->_crc);
	uint8_t crc16_low_byte = ModbusCrc16_LowByte(&o->_crc);
	if (o->_crc16_endian == BigEndian)
	{
		Stack_Push(o->_send_buffer_stack, &crc16_high_byte, 1);
		Stack_Push(o->_send_buffer_stack, &crc16_low_byte, 1);
	}
	else
	{
		Stack_Push(o->_send_buffer_stack, &crc16_low_byte, 1);
		Stack_Push(o->_send_buffer_stack, &crc16_high_byte, 1);
	}
}

#pragma region 不同功能码的请求处理函数
/// @brief 读一组线圈
/// @param o
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void ReadCoils(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
#pragma region 获取请求信息
	// 信息域缓冲区
	uint8_t *info_buffer = pdu + 1;
	int32_t info_buffer_offset = 0;

	// 起始位地址
	uint16_t start_bit_addr = ModbusBitConverter_ToUInt16(ModbusBitConverterUnit_Whole,
														  info_buffer,
														  info_buffer_offset);
	info_buffer_offset += 2;

	// 位数据个数
	int32_t bit_count = ModbusBitConverter_ToUInt16(ModbusBitConverterUnit_Whole,
													info_buffer,
													info_buffer_offset);
	info_buffer_offset += 2;
#pragma endregion

#pragma region 准备响应帧
	// 清空发送缓冲区
	Stack_Clear(o->_send_buffer_stack);

	// 放入站号
	Stack_Push(o->_send_buffer_stack, &o->_servant_address, 1);

	// 放入功能码
	/* 功能码在 modbus 传输中占用 1 字节，但是枚举量是一个 int，占用 4 字节。
	 * 这里要赋值给 uint8_t 类型的变量，然后才能将指针传给 Stack_Push 函数。
	 */
	uint8_t function_code = ModbusFunctionCode_ReadCoils;
	Stack_Push(o->_send_buffer_stack, &function_code, 1);

	// 放入数据字节数
	uint8_t byte_count = bit_count / 8;
	Stack_Push(o->_send_buffer_stack, &byte_count, 1);
#pragma endregion

#pragma region 放入位数据
	uint8_t bit_register = 0;

	// 位数据不需要多个字节，每个位的地址加 1。（每个线圈占用 1 个地址，且必须连续逐 1 递增）
	for (int i = 0; i < bit_count; i++)
	{
		uint8_t bit_value = o->ReadBitCallback(start_bit_addr + i);
		if (bit_value)
		{
			bit_register |= 1 << (i % 8);
		}

		if (i % 8 == 7)
		{
			Stack_Push(o->_send_buffer_stack, &bit_register, 1);
			bit_register = 0;
		}
	}
#pragma endregion

	CalculateAndPushCrc16(o);

	// 发送响应帧
	o->SendResponse(Stack_Buffer(o->_send_buffer_stack), 0, Stack_Sp(o->_send_buffer_stack));
}

/// @brief 读取一组输入位
/// @param o
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void ReadInputBits(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
#pragma region 获取请求信息
	// 信息域缓冲区
	uint8_t *info_buffer = pdu + 1;
	int32_t offset = 0;

	// 起始位地址
	uint16_t start_bit_addr = ModbusBitConverter_ToUInt16(ModbusBitConverterUnit_Whole,
														  info_buffer,
														  offset);
	offset += 2;

	// 位数据个数
	int32_t bit_count = ModbusBitConverter_ToUInt16(ModbusBitConverterUnit_Whole,
													info_buffer,
													offset);
	offset += 2;
#pragma endregion

#pragma region 准备响应帧
	// 清空发送缓冲区
	Stack_Clear(o->_send_buffer_stack);

	// 放入站号
	Stack_Push(o->_send_buffer_stack, &o->_servant_address, 1);

	// 放入功能码
	/* 功能码在 modbus 传输中占用 1 字节，但是枚举量是一个 int，占用 4 字节。
	 * 这里要赋值给 uint8_t 类型的变量，然后才能将指针传给 Stack_Push 函数。
	 */
	uint8_t function_code = ModbusFunctionCode_ReadInputBits;
	Stack_Push(o->_send_buffer_stack, &function_code, 1);

	// 放入数据字节数
	uint8_t byte_count = bit_count / 8;
	Stack_Push(o->_send_buffer_stack, &byte_count, 1);
#pragma endregion

#pragma region 放入位数据
	uint8_t bit_register = 0;

	// 位数据不需要多个字节，每个位的地址加 1。
	for (int i = 0; i < bit_count; i++)
	{
		uint8_t bit_value = o->ReadBitCallback(start_bit_addr + i);
		if (bit_value)
		{
			bit_register |= 1 << (i % 8);
		}

		if (i % 8 == 7)
		{
			Stack_Push(o->_send_buffer_stack, &bit_register, 1);
			bit_register = 0;
		}
	}
#pragma endregion

	CalculateAndPushCrc16(o);

	// 发送响应帧
	o->SendResponse(Stack_Buffer(o->_send_buffer_stack), 0, Stack_Sp(o->_send_buffer_stack));
}

/// @brief 读一组保持寄存器
/// @param o
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void ReadHoldingRegisters(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
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
#pragma endregion

#pragma region 准备响应帧
	// 清空发送缓冲区
	Stack_Clear(o->_send_buffer_stack);

	// 放入站号
	Stack_Push(o->_send_buffer_stack, &o->_servant_address, 1);

	// 放入功能码
	/* 功能码在 modbus 传输中占用 1 字节，但是枚举量是一个 int，占用 4 字节。
	 * 这里要赋值给 uint8_t 类型的变量，然后才能将指针传给 Stack_Push 函数。
	 */
	uint8_t function_code = ModbusFunctionCode_ReadHoldingRegisters;
	Stack_Push(o->_send_buffer_stack, &function_code, 1);

	// 放入数据字节数
	uint8_t byte_count = record_count * 2;
	Stack_Push(o->_send_buffer_stack, &byte_count, 1);
#pragma endregion

#pragma region 放入数据
	/* 记录的地址的偏移量。
	 * 例如读取一个 uint32_t ，有 2 个记录，则 record_addr_offset 递增 2.
	 * 每读取 1 个记录，record_addr_offset 递增 1.
	 */
	int32_t record_addr_offset = 0;
	while (1)
	{
		if (record_addr_offset == record_count)
		{
			break;
		}

		if (record_addr_offset > record_count)
		{
			// 超出了就不对了，说明上位机想要读取的记录数与本从机的数据大小不符，上位机错了
			// TODO: 发回例外响应。
			return;
		}

		int32_t current_record_addr = start_record_addr + record_addr_offset;
		ModbusMultibyteSizeEnum current_data_size_enum = o->GetMultibyteDataSize(current_record_addr);
		switch (current_data_size_enum)
		{
		case ModbusMultibyteSizeEnum_2Byte:
		{
			uint16_t data = o->Read2ByteCallback(current_record_addr);
			uint8_t temp_buffer[sizeof(data)];
			ModbusBitConverter_GetBytesFromUInt16(o->_bit_converter_unit,
												  data,
												  temp_buffer,
												  0);

			Stack_Push(o->_send_buffer_stack, temp_buffer, sizeof(temp_buffer));
			record_addr_offset += 1;
			break;
		}
		case ModbusMultibyteSizeEnum_4Byte:
		{
			uint32_t data = o->Read4ByteCallback(current_record_addr);
			uint8_t temp_buffer[sizeof(data)];
			ModbusBitConverter_GetBytesFromUInt32(o->_bit_converter_unit,
												  data,
												  temp_buffer,
												  0);

			Stack_Push(o->_send_buffer_stack, temp_buffer, sizeof(temp_buffer));
			record_addr_offset += 2;
			break;
		}
		case ModbusMultibyteSizeEnum_8Byte:
		{
			uint64_t data = o->Read8ByteCallback(current_record_addr);
			uint8_t temp_buffer[sizeof(data)];
			ModbusBitConverter_GetBytesFromUInt64(o->_bit_converter_unit,
												  data,
												  temp_buffer,
												  0);

			Stack_Push(o->_send_buffer_stack, temp_buffer, sizeof(temp_buffer));
			record_addr_offset += 4;
			break;
		}
		default:
		{
			// 不支持的数据大小。
			// 从机出错了，不应该有任何一个地址的数据的大小不在 ModbusMultibyteSizeEnum 的范围内。
			while (1)
			{
				// 卡在死循环，便于调试的时候发现错误
			}
		}
		}
	}
#pragma endregion

	CalculateAndPushCrc16(o);

	// 发送响应帧
	o->SendResponse(Stack_Buffer(o->_send_buffer_stack), 0, Stack_Sp(o->_send_buffer_stack));
}

/// @brief 读取一组输入寄存器
/// @param o
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void ReadInputRegisters(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
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
#pragma endregion

#pragma region 准备响应帧
	// 清空发送缓冲区
	Stack_Clear(o->_send_buffer_stack);

	// 放入站号
	Stack_Push(o->_send_buffer_stack, &o->_servant_address, 1);

	// 放入功能码
	/* 功能码在 modbus 传输中占用 1 字节，但是枚举量是一个 int，占用 4 字节。
	 * 这里要赋值给 uint8_t 类型的变量，然后才能将指针传给 Stack_Push 函数。
	 */
	uint8_t function_code = ModbusFunctionCode_ReadHoldingRegisters;
	Stack_Push(o->_send_buffer_stack, &function_code, 1);

	// 放入数据字节数
	uint8_t byte_count = record_count * 2;
	Stack_Push(o->_send_buffer_stack, &byte_count, 1);
#pragma endregion

#pragma region 放入数据
	/* 记录的地址的偏移量。
	 * 例如读取一个 uint32_t ，有 2 个记录，则 record_addr_offset 递增 2.
	 * 每读取 1 个记录，record_addr_offset 递增 1.
	 */
	int32_t record_addr_offset = 0;
	while (1)
	{
		if (record_addr_offset == record_count)
		{
			break;
		}

		if (record_addr_offset > record_count)
		{
			// 超出了就不对了，说明上位机想要读取的记录数与本从机的数据大小不符，上位机错了
			// TODO: 发回例外响应。
			return;
		}

		int32_t current_record_addr = start_record_addr + record_addr_offset;
		ModbusMultibyteSizeEnum current_data_size_enum = o->GetMultibyteDataSize(current_record_addr);
		switch (current_data_size_enum)
		{
		case ModbusMultibyteSizeEnum_2Byte:
		{
			uint16_t data = o->Read2ByteCallback(current_record_addr);
			uint8_t temp_buffer[sizeof(data)];
			ModbusBitConverter_GetBytesFromUInt16(o->_bit_converter_unit,
												  data,
												  temp_buffer,
												  0);

			Stack_Push(o->_send_buffer_stack, temp_buffer, sizeof(temp_buffer));
			record_addr_offset += 1;
			break;
		}
		case ModbusMultibyteSizeEnum_4Byte:
		{
			uint32_t data = o->Read4ByteCallback(current_record_addr);
			uint8_t temp_buffer[sizeof(data)];
			ModbusBitConverter_GetBytesFromUInt32(o->_bit_converter_unit,
												  data,
												  temp_buffer,
												  0);

			Stack_Push(o->_send_buffer_stack, temp_buffer, sizeof(temp_buffer));
			record_addr_offset += 2;
			break;
		}
		case ModbusMultibyteSizeEnum_8Byte:
		{
			uint64_t data = o->Read8ByteCallback(current_record_addr);
			uint8_t temp_buffer[sizeof(data)];
			ModbusBitConverter_GetBytesFromUInt64(o->_bit_converter_unit,
												  data,
												  temp_buffer,
												  0);

			Stack_Push(o->_send_buffer_stack, temp_buffer, sizeof(temp_buffer));
			record_addr_offset += 4;
			break;
		}
		default:
		{
			// 不支持的数据大小。
			// 从机出错了，不应该有任何一个地址的数据的大小不在 ModbusMultibyteSizeEnum 的范围内。
			while (1)
			{
				// 卡在死循环，便于调试的时候发现错误
			}
		}
		}
	}
#pragma endregion

	CalculateAndPushCrc16(o);

	// 发送响应帧
	o->SendResponse(Stack_Buffer(o->_send_buffer_stack), 0, Stack_Sp(o->_send_buffer_stack));
}

/// @brief 写单个线圈
/// @param o
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void WriteSingleCoil(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
	CalculateAndPushCrc16(o);

	// 发送响应帧
	o->SendResponse(Stack_Buffer(o->_send_buffer_stack), 0, Stack_Sp(o->_send_buffer_stack));
}

/// @brief 写一组线圈
/// @param o
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void WriteCoils(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
	CalculateAndPushCrc16(o);

	// 发送响应帧
	o->SendResponse(Stack_Buffer(o->_send_buffer_stack), 0, Stack_Sp(o->_send_buffer_stack));
}

/// @brief 写一组保持寄存器
/// @param o
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void WriteHoldingRegisters(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
	CalculateAndPushCrc16(o);

	// 发送响应帧
	o->SendResponse(Stack_Buffer(o->_send_buffer_stack), 0, Stack_Sp(o->_send_buffer_stack));
}

/// @brief 诊断
/// @param o
/// @param pdu 传进来的是完整的 PDU，包括 1 字节的功能码和后面的信息域。
/// @param pdu_size
static void Diagnosis(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
	CalculateAndPushCrc16(o);

	// 发送响应帧
	o->SendResponse(Stack_Buffer(o->_send_buffer_stack), 0, Stack_Sp(o->_send_buffer_stack));
}
#pragma endregion

/// @brief 处理普通的 PDU
/// @note 被调用说明 CRC 校验通过了。
///
/// @param
/// @param pdu modbus PDU
/// @param pdu_size pdu 的字节数
static void HandlePdu(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
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
		ReadCoils(o, pdu, pdu_size);
		break;
	}
	case ModbusFunctionCode_ReadInputBits:
	{
		// 读取一组输入位
		ReadInputBits(o, pdu, pdu_size);
		break;
	}
	case ModbusFunctionCode_ReadHoldingRegisters:
	{
		// 读取一组保持寄存器
		ReadHoldingRegisters(o, pdu, pdu_size);
		break;
	}
	case ModbusFunctionCode_ReadInputRegisters:
	{
		// 读取一组输入寄存器
		ReadInputRegisters(o, pdu, pdu_size);
		break;
	}
	case ModbusFunctionCode_WriteSingleCoil:
	{
		// 写单个线圈
		WriteSingleCoil(o, pdu, pdu_size);
		break;
	}
	case ModbusFunctionCode_WriteCoils:
	{
		// 写入一组线圈
		WriteCoils(o, pdu, pdu_size);
		break;
	}
	case ModbusFunctionCode_WriteHoldingRegisters:
	{
		// 写入多个保持寄存器
		WriteHoldingRegisters(o, pdu, pdu_size);
		break;
	}
	case ModbusFunctionCode_Diagnosis:
	{
		// 诊断
		Diagnosis(o, pdu, pdu_size);
		break;
	}
	}
}

/// @brief 处理广播的 PDU
/// @note 被调用说明 CRC 校验通过了。
///
/// @param
/// @param pdu modbus PDU
/// @param pdu_size pdu 的字节数
static void HandleBrocastPdu(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
	HandlePdu(o, pdu, pdu_size);
}

void ModbusServant_Init(ModbusServant *o,
						uint8_t servant_address,
						Endian crc16_endian,
						ModbusBitConverterUnit bit_converter_unit,
						ModbusServantReadWriteCallbackHub *read_write_callback_hub)
{
	o->_servant_address = servant_address;
	o->_crc16_endian = crc16_endian;
	o->_bit_converter_unit = bit_converter_unit;
	o->_send_buffer_stack = Stack_StackHeapAlloc(512);

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

	ModbusCrc16_Init(&o->_crc);
}

void ModbusServant_ParseReceivedBuffer(ModbusServant *o,
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
	if (adu[0] != o->_servant_address && adu[0] != 0)
	{
		// 站号与本站号不匹配，且不等于 0，即不是广播帧。
		return;
	}

	// 站号匹配或者是广播帧
	// 进行 CRC 校验
	ModbusCrc16_ResetRegister(&o->_crc);
	ModbusCrc16_AddArray(&o->_crc, adu, size - 2);
	uint8_t crc16_check_result = ModbusCrc16_CompareRegister(&o->_crc,
															 adu + size - 2,
															 o->_crc16_endian);
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
		HandleBrocastPdu(o, pdu, pdu_size);
		return;
	}

	// 普通帧
	HandlePdu(o, pdu, pdu_size);
}
