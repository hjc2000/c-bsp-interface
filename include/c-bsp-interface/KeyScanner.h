#pragma once
#include <c-bsp-interface/Bitset.h>
#include <c-bsp-interface/IKey.h>
#include <stdint.h>

typedef struct KeyScanner
{
	Bitset _last_key_pressed_state_bitset;
	Bitset _key_pressed_state_bitset;
	Bitset _key_down_event_bitset;
	Bitset _key_up_event_bitset;

	/**
	 * @brief 将按键实例的指针放到数组中，赋值给本字段
	 *
	 */
	IKey **_keys;

	/**
	 * @brief 按键个数
	 *
	 */
	uint32_t _key_count;

	/**
	 * @brief 延时函数。用来消抖。
	 *
	 */
	void (*DelayMilliseconds)(uint32_t ms);
} KeyScanner;

void KeyScanner_Scan(KeyScanner *this);

uint8_t KeyScanner_KeyIsPressed(KeyScanner *this, uint32_t key_index);
uint8_t KeyScanner_HasKeyDownEvent(KeyScanner *this, uint32_t key_index);
uint8_t KeyScanner_HasKeyUpEvent(KeyScanner *this, uint32_t key_index);