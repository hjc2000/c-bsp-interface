#pragma once
#include <stdint.h>
#include <string.h>

/* #region 转数字 */

inline uint16_t bsp__bit_converter__byte_array_to_uint16(uint8_t const *buffer, int32_t offset)
{
	uint16_t const *p = (uint16_t const *)(buffer + offset);
	return *p;
}

inline int16_t bsp__bit_converter__byte_array_to_int16(uint8_t const *buffer, int32_t offset)
{
	int16_t const *p = (int16_t const *)(buffer + offset);
	return *p;
}

inline uint16_t bsp__bit_converter__2_byte_to_uint16(uint8_t high, uint8_t low)
{
	return ((uint16_t)high << 8) | low;
}

inline uint32_t bsp__bit_converter__byte_array_to_uint32(uint8_t const *buffer, int32_t offset)
{
	uint32_t const *p = (uint32_t const *)(buffer + offset);
	return *p;
}

inline int32_t bsp__bit_converter__byte_array_to_int32(uint8_t const *buffer, int32_t offset)
{
	int32_t const *p = (int32_t const *)(buffer + offset);
	return *p;
}

inline uint32_t bsp__bit_converter__2_uint16_to_uint32(uint16_t high, uint16_t low)
{
	return ((uint32_t)high << 16) | low;
}

inline uint32_t bsp__bit_converter__4_byte_to_uint32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
	uint16_t high = bsp__bit_converter__2_byte_to_uint16(b3, b2);
	uint16_t low = bsp__bit_converter__2_byte_to_uint16(b1, b0);
	return bsp__bit_converter__2_uint16_to_uint32(high, low);
}

inline uint64_t bsp__bit_converter__byte_array_to_uint64(uint8_t const *buffer, int32_t offset)
{
	uint64_t const *p = (uint64_t const *)(buffer + offset);
	return *p;
}

inline int64_t bsp__bit_converter__byte_array_to_int64(uint8_t const *buffer, int32_t offset)
{
	int64_t const *p = (int64_t const *)(buffer + offset);
	return *p;
}

inline float bsp__bit_converter__byte_array_to_float(uint8_t const *buffer, int32_t offset)
{
	float const *p = (float const *)(buffer + offset);
	return *p;
}

inline double bsp__bit_converter__byte_array_to_double(uint8_t const *buffer, int32_t offset)
{
	double const *p = (double const *)(buffer + offset);
	return *p;
}

/* #endregion */

/* #region 转字节数组 */

inline void bsp__bit_converter__get_bytes_from_uint16(uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, sizeof(value));
}

inline void bsp__bit_converter__get_bytes_from_int16(int16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, sizeof(value));
}

inline void bsp__bit_converter__get_bytes_from_uint32(uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, sizeof(value));
}

inline void bsp__bit_converter__get_bytes_from_int32(int32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, sizeof(value));
}

inline void bsp__bit_converter__get_bytes_from_uint64(uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, sizeof(value));
}

inline void bsp__bit_converter__get_bytes_from_int64(int64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, sizeof(value));
}

inline void bsp__bit_converter__get_bytes_from_float(float value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, sizeof(value));
}

inline void bsp__bit_converter__get_bytes_from_double(double value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, buffer, sizeof(value));
}

/* #endregion */
