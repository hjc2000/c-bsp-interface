#include "BitConverter.h"
#include <string.h>

#pragma region 转数字
uint16_t BitConverter_ByteArrayToUInt16(uint8_t const *buffer, int32_t offset)
{
	uint16_t const *p = (uint16_t const *)(buffer + offset);
	return *p;
}

int16_t BitConverter_ByteArrayToInt16(uint8_t const *buffer, int32_t offset)
{
	int16_t const *p = (int16_t const *)(buffer + offset);
	return *p;
}

uint16_t BitConverter_2_Byte_To_UInt16(uint8_t high, uint8_t low)
{
	return ((uint16_t)high << 8) | low;
}

uint32_t BitConverter_ByteArrayToUInt32(uint8_t const *buffer, int32_t offset)
{
	uint32_t const *p = (uint32_t const *)(buffer + offset);
	return *p;
}

int32_t BitConverter_ByteArrayToInt32(uint8_t const *buffer, int32_t offset)
{
	int32_t const *p = (int32_t const *)(buffer + offset);
	return *p;
}

uint32_t BitConverter_4_Byte_To_UInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
	uint16_t high = BitConverter_2_Byte_To_UInt16(b3, b2);
	uint16_t low = BitConverter_2_Byte_To_UInt16(b1, b0);
	return BitConverter_2_Uint16_To_UInt32(high, low);
}

uint32_t BitConverter_2_Uint16_To_UInt32(uint16_t high, uint16_t low)
{
	return ((uint32_t)high << 16) | low;
}

uint64_t BitConverter_ByteArrayToUInt64(uint8_t const *buffer, int32_t offset)
{
	uint64_t const *p = (uint64_t const *)(buffer + offset);
	return *p;
}

int64_t BitConverter_ByteArrayToInt64(uint8_t const *buffer, int32_t offset)
{
	int64_t const *p = (int64_t const *)(buffer + offset);
	return *p;
}

float BitConverter_ByteArrayToFloat(uint8_t const *buffer, int32_t offset)
{
	float const *p = (float const *)(buffer + offset);
	return *p;
}

double BitConverter_ByteArrayToDouble(uint8_t const *buffer, int32_t offset)
{
	double const *p = (double const *)(buffer + offset);
	return *p;
}
#pragma endregion

#pragma region 转字节数组
void BitConverter_GetBytesFromUInt16(uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 2);
}

void BitConverter_GetBytesFromInt16(int16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 2);
}

void BitConverter_GetBytesFromUInt32(uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 4);
}

void BitConverter_GetBytesFromInt32(int32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 4);
}

void BitConverter_GetBytesFromUInt64(uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 8);
}

void BitConverter_GetBytesFromInt64(int64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 8);
}

void BitConverter_GetBytesFromFloat(float value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 4);
}

void BitConverter_GetBytesFromDouble(double value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 8);
}
#pragma endregion
