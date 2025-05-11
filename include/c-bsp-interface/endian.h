#pragma once

typedef enum bsp_endian_enum
{
	bsp_endian_big_endian,
	bsp_endian_little_endian,
} bsp_endian_enum;

///
/// @brief 获取本机字节序
///
/// @return
///
bsp_endian_enum bsp_local_host_endian();
