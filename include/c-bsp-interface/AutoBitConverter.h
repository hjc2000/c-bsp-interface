#pragma once
#include <c-bsp-interface/Endian.h>
#include <stdint.h>

typedef struct AutoBitConverter
{
	Endian _remote_endian;
} AutoBitConverter;

#pragma region 转化为数字类型
uint16_t AutoBitConverter_ToUInt16(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
int16_t AutoBitConverter_ToInt16(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);

uint32_t AutoBitConverter_ToUInt32(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
int32_t AutoBitConverter_ToInt32(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);

uint64_t AutoBitConverter_ToUInt64(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
int64_t AutoBitConverter_ToInt64(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);

float AutoBitConverter_ToFloat(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
double AutoBitConverter_ToDouble(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
#pragma endregion
