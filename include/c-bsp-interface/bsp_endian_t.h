#pragma once
#include <stdint.h>

typedef enum bsp_endian_t
{
	BigEndian,
	LittleEndian,
} bsp_endian_t;

///
/// @brief 获取本机字节序
///
/// @return
///
inline bsp_endian_t bsp__local_host_endian()
{
	int32_t a = 1;
	int8_t *p = (int8_t *)(&a);
	if (*p)
	{
		return LittleEndian;
	}

	return BigEndian;
}
