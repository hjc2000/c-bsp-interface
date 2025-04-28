#include "bit_converter.h"
#include <string.h>

#pragma region 转字节数组

void bsp__bit_converter__GetBytesFromUInt16(uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 2);
}

void bsp__bit_converter__GetBytesFromInt16(int16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 2);
}

void bsp__bit_converter__GetBytesFromUInt32(uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 4);
}

void bsp__bit_converter__GetBytesFromInt32(int32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 4);
}

void bsp__bit_converter__GetBytesFromUInt64(uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 8);
}

void bsp__bit_converter__GetBytesFromInt64(int64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 8);
}

void bsp__bit_converter__GetBytesFromFloat(float value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 4);
}

void bsp__bit_converter__GetBytesFromDouble(double value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, 8);
}

#pragma endregion
