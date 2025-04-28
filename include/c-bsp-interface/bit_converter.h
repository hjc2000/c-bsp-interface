#pragma once
#include <stdint.h>

/* #region 转数字 */

inline uint16_t bsp__bit_converter__byte_array_to_uint16(uint8_t const *buffer, int32_t offset)
{
	uint16_t const *p = (uint16_t const *)(buffer + offset);
	return *p;
}

inline int16_t bsp__bit_converter__ByteArrayToInt16(uint8_t const *buffer, int32_t offset)
{
	int16_t const *p = (int16_t const *)(buffer + offset);
	return *p;
}

inline uint16_t bsp__bit_converter__2_Byte_To_UInt16(uint8_t high, uint8_t low)
{
	return ((uint16_t)high << 8) | low;
}

inline uint32_t bsp__bit_converter__ByteArrayToUInt32(uint8_t const *buffer, int32_t offset)
{
	uint32_t const *p = (uint32_t const *)(buffer + offset);
	return *p;
}

inline int32_t bsp__bit_converter__ByteArrayToInt32(uint8_t const *buffer, int32_t offset)
{
	int32_t const *p = (int32_t const *)(buffer + offset);
	return *p;
}

inline uint32_t bsp__bit_converter__2_Uint16_To_UInt32(uint16_t high, uint16_t low)
{
	return ((uint32_t)high << 16) | low;
}

inline uint32_t bsp__bit_converter__4_Byte_To_UInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
	uint16_t high = bsp__bit_converter__2_Byte_To_UInt16(b3, b2);
	uint16_t low = bsp__bit_converter__2_Byte_To_UInt16(b1, b0);
	return bsp__bit_converter__2_Uint16_To_UInt32(high, low);
}

inline uint64_t bsp__bit_converter__ByteArrayToUInt64(uint8_t const *buffer, int32_t offset)
{
	uint64_t const *p = (uint64_t const *)(buffer + offset);
	return *p;
}

inline int64_t bsp__bit_converter__ByteArrayToInt64(uint8_t const *buffer, int32_t offset)
{
	int64_t const *p = (int64_t const *)(buffer + offset);
	return *p;
}

inline float bsp__bit_converter__ByteArrayToFloat(uint8_t const *buffer, int32_t offset)
{
	float const *p = (float const *)(buffer + offset);
	return *p;
}

inline double bsp__bit_converter__ByteArrayToDouble(uint8_t const *buffer, int32_t offset)
{
	double const *p = (double const *)(buffer + offset);
	return *p;
}

/* #endregion */

/* #region 转字节数组 */

void bsp__bit_converter__GetBytesFromUInt16(uint16_t value, uint8_t *out_buffer, int32_t offset);
void bsp__bit_converter__GetBytesFromInt16(int16_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__GetBytesFromUInt32(uint32_t value, uint8_t *out_buffer, int32_t offset);
void bsp__bit_converter__GetBytesFromInt32(int32_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__GetBytesFromUInt64(uint64_t value, uint8_t *out_buffer, int32_t offset);
void bsp__bit_converter__GetBytesFromInt64(int64_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__GetBytesFromFloat(float value, uint8_t *out_buffer, int32_t offset);
void bsp__bit_converter__GetBytesFromDouble(double value, uint8_t *out_buffer, int32_t offset);

/* #endregion */
