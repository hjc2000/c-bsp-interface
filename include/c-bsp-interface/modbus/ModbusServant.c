#include "ModbusServant.h"
#include <c-bsp-interface/memory/StackHeap.h>

/// @brief 处理广播的 PDU
/// @note 被调用说明 CRC 校验通过了。
///
/// @param
/// @param pdu modbus PDU
/// @param count pdu 的字节数
static void HandleBrocastPdu(ModbusServant *this, uint8_t *pdu, int32_t count)
{
}

/// @brief 处理普通的 PDU
/// @note 被调用说明 CRC 校验通过了。
///
/// @param
/// @param pdu modbus PDU
/// @param count pdu 的字节数
static void HandlePdu(ModbusServant *this, uint8_t *pdu, int32_t count)
{
}

void ModbusServant_Init(ModbusServant *this,
						uint8_t servant_address,
						Endian crc16_endian,
						ModbusBitConverterUnit bit_converter_unit)
{
	this->_servant_address = servant_address;
	this->_crc16_endian = crc16_endian;
	this->_bit_converter_unit = bit_converter_unit;
	this->_send_buffer_size = 512;
	this->_send_buffer = StackHeapAlloc(this->_send_buffer_size);
	ModbusCrc16_Init(&this->_crc);
}

void ModbusServant_ParseReceivedBuffer(ModbusServant *this,
									   uint8_t *buffer, int32_t offset, int32_t count)
{
	if (count <= 3)
	{
		/* ADU 比 PDU 多出来 3 个字节。其中 CRC16 占用 2 个字节，站号占用 1 个字节。
		 * 如果整个 ADU 的大小小于等于 3，说明 PDU 为空，这种帧没有意义。
		 */
		return;
	}

	uint8_t *adu = buffer + offset;
	if (adu[0] != this->_servant_address && adu[0] != 0)
	{
		// 站号与本站号不匹配，且不等于 0，即不是广播帧。
		return;
	}

	// 站号匹配或者是广播帧
	// 进行 CRC 校验
	ModbusCrc16_ResetRegister(&this->_crc);
	ModbusCrc16_AddArray(&this->_crc, adu, count - 2);
	uint8_t crc16_check_result = ModbusCrc16_CompareRegister(&this->_crc,
															 adu + count - 2,
															 this->_crc16_endian);
	if (!crc16_check_result)
	{
		// CRC 校验错误时从机应该沉默。
		return;
	}

	// CRC 校验通过
	uint8_t *pdu = adu + 1;
	if (adu[0] == 0)
	{
		// 广播帧
		HandleBrocastPdu(this, pdu, count - 2);
		return;
	}

	// 普通帧
	HandlePdu(this, pdu, count - 2);
}

void ModbusServant_PushBackUInt32(ModbusServant *this, uint32_t value)
{
}
