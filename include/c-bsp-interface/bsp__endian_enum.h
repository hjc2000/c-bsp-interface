#pragma once
#include <stdint.h>

typedef enum bsp__endian_enum
{
	bsp__endian_enum__big_endian,
	bsp__endian_enum__little_endian,
} bsp__endian_enum;

///
/// @brief 获取本机字节序
///
/// @return
///
inline bsp__endian_enum bsp__local_host_endian()
{
	int32_t a = 1;
	int8_t *p = (int8_t *)(&a);
	if (*p)
	{
		return bsp__endian_enum__little_endian;
	}

	return bsp__endian_enum__big_endian;
}
