#include "ModbusServant.h"
#include <c-bsp-interface/modbus/ModbusCrc16.h>

/// @brief 对帧进行 CRC16 校验
/// @param frame 帧指针
/// @param count 帧的长度。单位：字节。
/// @return
static uint8_t CheckCrc16(uint8_t *frame, int32_t count)
{
}

/// @brief 处理广播帧
/// @note 在 ModbusServant_FeedBuffer 函数中被调用，ModbusServant_FeedBuffer 函数已经对站号
/// 进行过滤了。
///
/// @param
/// @param frame
/// @param count
static void HandleBrocastFrame(ModbusServant *this, uint8_t *frame, int32_t count)
{
}

/// @brief 处理普通帧
/// @note 在 ModbusServant_FeedBuffer 函数中被调用，ModbusServant_FeedBuffer 函数已经对站号
/// 进行过滤了。
///
/// @param
/// @param frame
/// @param count
static void HandleFrame(ModbusServant *this, uint8_t *frame, int32_t count)
{
}

void ModbusServant_Init(ModbusServant *this,
						uint8_t servant_address,
						IDigitalLed *red_led,
						IDigitalLed *green_led,
						IKey *key0,
						IKey *key1)
{
	this->_servant_address = servant_address;
	this->_red_led = red_led;
	this->_green_led = green_led;
	this->_key0 = key0;
	this->_key1 = key1;
}

void ModbusServant_FeedBuffer(ModbusServant *this,
							  uint8_t *buffer, int32_t offset, int32_t count)
{
	if (count <= 0)
	{
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
