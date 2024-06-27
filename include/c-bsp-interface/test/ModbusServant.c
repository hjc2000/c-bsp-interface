#include "ModbusServant.h"

/// @brief 处理广播帧
/// @param
/// @param frame
/// @param count
static void HandleBrocastFrame(ModbusServant *this, uint8_t *frame, int32_t count)
{
	uint8_t crc16_check_result = ModbusCrc16_CompareRegister(&this->_crc,
															 frame + count - 2,
															 this->_crc16_endian);
	if (!crc16_check_result)
	{
		// TODO: 返回例外响应，告诉主机 CRC 错了。
		return;
	}
}

/// @brief 处理普通帧
/// @param
/// @param frame
/// @param count
static void HandleFrame(ModbusServant *this, uint8_t *frame, int32_t count)
{
	uint8_t crc16_check_result = ModbusCrc16_CompareRegister(&this->_crc,
															 frame + count - 2,
															 this->_crc16_endian);
	if (!crc16_check_result)
	{
		// TODO: 返回例外响应，告诉主机 CRC 错了。
		return;
	}
}

void ModbusServant_Init(ModbusServant *this,
						uint8_t servant_address,
						Endian crc16_endian)
{
	this->_servant_address = servant_address;
	ModbusCrc16_Init(&this->_crc);
}

void ModbusServant_FeedBuffer(ModbusServant *this,
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
	if (frame[0] != this->_servant_address)
	{
		// 接收到的帧的从机站号与本站号不匹配
		if (frame[0] == 0)
		{
			// 广播帧
			HandleBrocastFrame(this, frame, count);
		}

		return;
	}

	HandleFrame(this, frame, count);
}
