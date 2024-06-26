#pragma once
#include <c-bsp-interface/AsyncStream.h>
#include <c-bsp-interface/IDigitalLed.h>
#include <c-bsp-interface/IKey.h>
#include <c-bsp-interface/ModbusCrc16.h>

typedef struct ModbusServant
{
	AsyncStream *_stream;
	IDigitalLed *_red_led;
	IDigitalLed *_green_led;
	IKey *_key0;
	IKey *_key1;

	/// @brief 延时函数。用来消抖。
	void (*DelayMilliseconds)(uint32_t ms);
} ModbusServant;

/// @brief 单例模式，只能启动一个实例。
/// @param
void ModbusServant_Start(ModbusServant *this);
