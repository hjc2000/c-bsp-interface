#pragma once
#include <stdint.h>

///
/// @brief 反转字节数组
///
/// @param array
///
/// @param size
///
void bsp__reverse_byte_array(uint8_t *array, int32_t size);

///
/// @brief 将字节数组中的字节以每个单元为单位，在单元内进行字节序反转。
///
/// @param array 字节数组。
///
/// @param element_size 每个单元的大小。
///
/// @param element_count 单元的个数。
///
void bsp__reverse_byte_array_per_element(uint8_t *array, int32_t element_size, int32_t element_count);
