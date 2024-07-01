#pragma once
#include <c-bsp-interface/Bitset.h>
#include <c-bsp-interface/IKey.h>
#include <stdint.h>

typedef struct KeyScanner
{
	Bitset *_last_key_pressed_state_bitset;
	Bitset *_key_pressed_state_bitset;
	Bitset *_key_down_event_bitset;
	Bitset *_key_up_event_bitset;

	/// @brief 将按键实例的指针放到数组中，赋值给本字段
	IKey **_keys;

	/// @brief 按键个数
	int32_t _key_count;

	/// @brief 延时函数。用来消抖。
	void (*DelayMilliseconds)(uint32_t ms);
} KeyScanner;

KeyScanner *KeyScanner_StackHeapAlloc(int32_t key_count,
									  void (*delay_milliseconds)(uint32_t ms));

/// @brief 设置一个按键到扫描器中指定的位置。
/// @param
/// @param index
/// @param key
void KeyScanner_SetKey(KeyScanner *this, int32_t index, IKey *key);

/// @brief 执行扫描
/// @param
void KeyScanner_Scan(KeyScanner *this);

/// @brief 查询指定的按键是否正被按下
/// @param
/// @param key_index
/// @return
uint8_t KeyScanner_KeyIsPressed(KeyScanner *this, int32_t key_index);

/// @brief 查询指定的按键是否有 key_down 事件。
/// @param
/// @param key_index
/// @return
uint8_t KeyScanner_HasKeyDownEvent(KeyScanner *this, int32_t key_index);

/// @brief 查询指定的按键是否有 key_up 事件。
/// @param
/// @param key_index
/// @return
uint8_t KeyScanner_HasKeyUpEvent(KeyScanner *this, int32_t key_index);
