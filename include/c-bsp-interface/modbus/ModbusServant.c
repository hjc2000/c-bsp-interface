#include "ModbusServant.h"
#include <c-bsp-interface/memory/StackHeap.h>
#include <c-bsp-interface/modbus/FunctionCode.h>

static void HandleReadCoils(ModbusServant *o, uint8_t *pdu, int32_t pdu_size)
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

void ModbusServant_Init(ModbusServant *o,
						uint8_t servant_address,
						Endian crc16_endian,
						ModbusBitConverterUnit bit_converter_unit,
						ModbusMultibyteSizeEnum (*get_multibyte_data_size)(uint32_t data_addr))
{
	o->_servant_address = servant_address;
	o->_crc16_endian = crc16_endian;
	o->_bit_converter_unit = bit_converter_unit;
	o->_send_buffer_stack = Stack_StackHeapAlloc(512);
	o->GetMultibyteDataSize = get_multibyte_data_size;
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
