#pragma once
#include <c-bsp-interface/Endian.h>
#include <stdint.h>

/// @brief 在通信时需要在本机字节序和远程字节序之间转换。本结构体提供了一系列方法来进行这种操作。
/// 设置好远程的字节序后，在转换时如果远程字节序与本机不一样，就会反转字节数组。
typedef struct AutoBitConverter
{
	Endian _remote_endian;
} AutoBitConverter;

#pragma region 转数字
uint16_t AutoBitConverter_ToUInt16(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
int16_t AutoBitConverter_ToInt16(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);

uint32_t AutoBitConverter_ToUInt32(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
int32_t AutoBitConverter_ToInt32(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);

uint64_t AutoBitConverter_ToUInt64(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
int64_t AutoBitConverter_ToInt64(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);

float AutoBitConverter_ToFloat(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
double AutoBitConverter_ToDouble(AutoBitConverter *this, uint8_t const *buffer, int32_t offset);
#pragma endregion

#pragma region 转字节数组
void AutoBitConverter_GetBytesFromUInt16(AutoBitConverter *this,
										 uint16_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt16(AutoBitConverter *this,
										int16_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromUInt32(AutoBitConverter *this,
										 uint32_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt32(AutoBitConverter *this,
										int32_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromUInt64(AutoBitConverter *this,
										 uint64_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt64(AutoBitConverter *this,
										int64_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromFloat(AutoBitConverter *this,
										float value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromDouble(AutoBitConverter *this,
										 double value, uint8_t *out_buffer, int32_t offset);
#pragma endregion
