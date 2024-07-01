#pragma once
#include <c-bsp-interface/IKey.h>
#include <stdint.h>

typedef struct KeyScanner KeyScanner;

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
