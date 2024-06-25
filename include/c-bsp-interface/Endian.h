#pragma once

typedef enum Endian
{
	BigEndian,
	LittleEndian,
} Endian;

/// @brief 获取本机字节序
/// @return
Endian LocalHostEndian();
