#pragma once
#include <stdint.h>

/// @brief LED 灯的接口
typedef struct IDigitalLed
{
	void (*TurnOn)();
	void (*TurnOff)();
	void (*Toggle)();
} IDigitalLed;
