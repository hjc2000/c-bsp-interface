#pragma once
#include <stdint.h>

/// @brief LED 灯的接口
typedef struct IDigitalLed
{
	void (*TurnOn)();
	void (*TurnOff)();
	void (*Toggle)();

	/// @brief LED 灯的状态。
	/// @return 返回 true 表示 LED 灯当前为亮，返回 false 表示 LED 灯当前为灭。
	uint8_t (*State)();
} IDigitalLed;
