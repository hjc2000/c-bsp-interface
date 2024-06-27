#pragma once
#include <c-bsp-interface/Endian.h>
#include <c-bsp-interface/modbus/ModbusCrc16.h>
#include <stdint.h>

typedef struct ModbusServant
{
#pragma region private
	/// @brief 从机站号
	uint8_t _servant_address;
	ModbusCrc16 _crc;
	Endian _crc16_endian;
#pragma endregion

} ModbusServant;

/// @brief 准备一个静态的 ModbusServant 对象，传进来进行初始化。
/// @param
/// @param servant_address
/// @param red_led
/// @param green_led
/// @param key0
/// @param key1
void ModbusServant_Init(ModbusServant *this,
						uint8_t servant_address,
						Endian crc16_endian);

/// @brief 将缓冲区喂给 ModbusServant
/// @param
/// @param buffer
/// @param offset
/// @param count
void ModbusServant_FeedBuffer(ModbusServant *this,
							  uint8_t *buffer, int32_t offset, int32_t count);
