#pragma once

typedef enum ModbusMultibyteSizeEnum
{
	ModbusMultibyteSizeEnum_2Byte,
	ModbusMultibyteSizeEnum_4Byte,
	ModbusMultibyteSizeEnum_8Byte,
} ModbusMultibyteSizeEnum;

/// @brief 获取 ModbusMultibyteSizeEnum 枚举值代表的是几个字节。
/// @param value ModbusMultibyteSizeEnum 枚举值。
/// @return 代表多少个字节。
int ModbusMultibyteSizeEnum_To_ByteCount(ModbusMultibyteSizeEnum value);
