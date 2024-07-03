#include "ModbusServant.h"
#include <c-bsp-interface/container/Stack.h>
#include <c-bsp-interface/memory/StackHeap.h>
#include <c-bsp-interface/modbus/FunctionCode.h>
#include <c-bsp-interface/modbus/ModbusCrc16.h>

/// @brief modbus 从机
typedef struct ModbusServant
{
	/// @brief 从机站号
	uint8_t _servant_address;
	ModbusCrc16 _crc;
	Endian _crc16_endian;
	ModbusBitConverterUnit _bit_converter_unit;
	Stack *_send_buffer_stack;

#pragma region 读写数据回调函数
	/// @brief 传入数据地址，返回这个数据是对应什么 ModbusMultibyteSizeEnum
	/// @param data_addr 数据地址
	/// @return 这个地址的数据是对应什么 ModbusMultibyteSizeEnum
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

static void HandleReadCoils(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
}

/// @brief 处理普通的 PDU
/// @note 被调用说明 CRC 校验通过了。
///
/// @param
/// @param pdu modbus PDU
/// @param pdu_size pdu 的字节数
static void HandlePdu(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
{
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
