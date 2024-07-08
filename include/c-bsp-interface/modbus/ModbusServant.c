#include "ModbusServant.h"
#include <c-bsp-interface/container/Stack.h>
#include <c-bsp-interface/memory/StackHeap.h>
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

	uint8_t (*ReadByteCallback)(uint32_t data_addr);
	uint16_t (*Read2ByteCallback)(uint32_t data_addr);
	uint32_t (*Read4ByteCallback)(uint32_t data_addr);
	uint64_t (*Read8ByteCallback)(uint32_t data_addr);

	void (*WriteByteCallback)(uint32_t data_addr, uint8_t value);
	void (*Write2ByteCallback)(uint32_t data_addr, uint16_t value);
	void (*Write4ByteCallback)(uint32_t data_addr, uint32_t value);
	void (*Write8ByteCallback)(uint32_t data_addr, uint64_t value);

	uint8_t (*ReadBitCallback)(uint32_t data_addr);
	void (*WriteBitCallback)(uint32_t data_addr, uint8_t value);
#pragma endregion

} ModbusServant;

#pragma region 读写回调处理函数
// 读一组线圈
static void ReadCoils(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
}

// 读取一组输入位
static void ReadInputBits(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
}

// 读一组保持寄存器
static void ReadHoldingRegisters(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
}

static void ReadInputRegisters(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
}

static void WriteSingleCoil(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
}

static void WriteCoils(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
}

static void WriteHoldingRegisters(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
}

static void Diagnosis(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
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

	o->ReadByteCallback = read_write_callback_hub->ReadByteCallback;
	o->Read2ByteCallback = read_write_callback_hub->Read2ByteCallback;
	o->Read4ByteCallback = read_write_callback_hub->Read4ByteCallback;
	o->Read8ByteCallback = read_write_callback_hub->Read8ByteCallback;

	o->WriteByteCallback = read_write_callback_hub->WriteByteCallback;
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
	// PDU 包括功能码和信息域。是 ADU 去掉头部 1 个字节的站号和尾部 2 个字节的 CRC16 后的结果。
	uint8_t *pdu = adu + 1;
	if (adu[0] == 0)
	{
		// 广播帧
		HandleBrocastPdu(o, pdu, size - 3);
		return;
	}

	// 普通帧
	HandlePdu(o, pdu, size - 3);
}
