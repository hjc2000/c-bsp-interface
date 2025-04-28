#pragma once

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
bsp_endian_t bsp_local_host_endian();
