#include "ModbusServant.h"

/// @brief 处理广播帧
/// @note 被调用说明 CRC 校验通过了。
///
/// @param
/// @param pdu_frame 包含功能码和数据，不包含站号和 CRC16
/// @param count 字节数
static void HandleBrocastFrame(ModbusServant *this, uint8_t *pdu_frame, int32_t count)
{
}

/// @brief 处理普通帧
/// @note 被调用说明 CRC 校验通过了。
///
/// @param
/// @param pdu_frame 包含功能码和数据，不包含站号和 CRC16
/// @param count 字节数
static void HandleFrame(ModbusServant *this, uint8_t *pdu_frame, int32_t count)
{
}

#pragma region 公共函数
void ModbusServant_Init(ModbusServant *this,
						uint8_t servant_address,
						Endian crc16_endian)
{
	this->_servant_address = servant_address;
	this->_crc16_endian = crc16_endian;
	ModbusCrc16_Init(&this->_crc);
}

void ModbusServant_SendBuffer(ModbusServant *this,
							  uint8_t *buffer, int32_t offset, int32_t count)
{
	if (count <= 2)
	{
		/* 因为 CRC16 占 2 字节，所以帧大小不可能小于等于 2 字节，如果出现这种情况，
		 * 一定是帧出错了。
		 *
		 * 此时连帧都不完整，也不知道是发给谁的，所以就不发回例外响应了。
		 */
		return;
	}

	uint8_t *frame = buffer + offset;
	if (frame[0] != this->_servant_address && frame[0] != 0)
	{
		// 站号与本站号不匹配，且不等于 0，即不是广播帧。
		return;
	}

	// 站号匹配或者是广播帧
	// 进行 CRC 校验
	ModbusCrc16_ResetRegister(&this->_crc);
	ModbusCrc16_AddArray(&this->_crc, frame, count - 2);
	uint8_t crc16_check_result = ModbusCrc16_CompareRegister(&this->_crc,
															 frame + count - 2,
															 this->_crc16_endian);
	if (!crc16_check_result)
	{
		// CRC 校验错误时从机应该沉默。
		return;
	}

	// CRC 校验通过
	if (frame[0] == 0)
	{
		// 广播帧
		HandleBrocastFrame(this, frame, count - 2);
		return;
	}

	// 普通帧
	HandleFrame(this, frame, count - 2);
}
#pragma endregion
