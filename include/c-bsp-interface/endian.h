#pragma once

typedef enum bsp__endian
{
	bsp__endian__big_endian,
	bsp__endian__little_endian,
} bsp__endian;

///
/// @brief 获取本机字节序
///
/// @return
///
bsp__endian bsp__local_host_endian();
