#pragma once
#include <c-bsp-interface/IDigitalLed.h>
#include <c-bsp-interface/IKey.h>

typedef struct ModbusServant
{
#pragma region private
	/// @brief 从机站号
	uint8_t _servant_address;
	IDigitalLed *_red_led;
	IDigitalLed *_green_led;
	IKey *_key0;
	IKey *_key1;
#pragma endregion

} ModbusServant;

void ModbusServant_Init(ModbusServant *this,
						uint8_t servant_address,
						IDigitalLed *red_led,
						IDigitalLed *green_led,
						IKey *key0,
						IKey *key1);

/// @brief 将缓冲区喂给 ModbusServant
/// @param buffer
/// @param offset
/// @param count
void ModbusServant_FeedBuffer(ModbusServant *this,
							  uint8_t *buffer, int32_t offset, int32_t count);
