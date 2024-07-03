#pragma once
#include <c-bsp-interface/IKey.h>
#include <stdint.h>

typedef struct KeyScanner KeyScanner;

/// @brief 在栈堆上分配一个 KeyScanner 并初始化。
/// @param key_count
/// @param delay_milliseconds
/// @return
KeyScanner *KeyScanner_StackHeapAlloc(int32_t key_count,
									  void (*delay_milliseconds)(uint32_t ms));

/// @brief 设置一个按键到扫描器中指定的位置。
/// @param
/// @param index 按键的索引。不要大于 key_count - 1。
/// @param key 要被放入按键扫描器的按键。
void KeyScanner_SetKey(KeyScanner *o, int32_t index, IKey *key);

/// @brief 执行扫描
/// @param
void KeyScanner_Scan(KeyScanner *o);

/// @brief 查询指定的按键是否正被按下
/// @param
/// @param key_index
/// @return
uint8_t KeyScanner_KeyIsPressed(KeyScanner *o, int32_t key_index);

/// @brief 查询指定的按键是否有 key_down 事件。
/// @param
/// @param key_index
/// @return
uint8_t KeyScanner_HasKeyDownEvent(KeyScanner *o, int32_t key_index);

/// @brief 查询指定的按键是否有 key_up 事件。
/// @param
/// @param key_index
/// @return
uint8_t KeyScanner_HasKeyUpEvent(KeyScanner *o, int32_t key_index);
