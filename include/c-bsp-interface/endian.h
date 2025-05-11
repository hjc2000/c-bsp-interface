#pragma once

typedef enum bsp_endian
{
	bsp_endian_big_endian,
	bsp_endian_little_endian,
} bsp_endian;

///
/// @brief 获取本机字节序
///
/// @return
///
bsp_endian bsp_local_host_endian();
