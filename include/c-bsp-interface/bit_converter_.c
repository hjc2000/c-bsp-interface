#include "BitConverter.h"
#include <string.h>

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
