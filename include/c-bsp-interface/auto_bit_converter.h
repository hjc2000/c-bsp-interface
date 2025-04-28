#pragma once
#include "c-bsp-interface/bit_converter.h"
#include "c-bsp-interface/endian.h"
#include "c-bsp-interface/Reverse.h"
#include "type.h"
#include <stdint.h>

typedef struct bsp__auto_bit_converter
{
	bsp__bool _should_reverse;
} bsp__auto_bit_converter;

inline void bsp__auto_bit_converter__initialize(
	bsp__auto_bit_converter *self, bsp__endian remote_endian)
{
	self->_should_reverse = bsp__local_host_endian() != remote_endian;
}

/* #region 转数字 */

inline uint16_t bsp__auto_bit_converter__to_uint16(
	bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	uint16_t ret = BitConverter_ByteArrayToUInt16(buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

inline int16_t bsp__auto_bit_converter__to_int16(
	bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	int16_t ret = BitConverter_ByteArrayToInt16(buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

inline uint32_t bsp__auto_bit_converter__to_uint32(
	bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	uint32_t ret = BitConverter_ByteArrayToUInt32(buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

inline int32_t bsp__auto_bit_converter__to_int32(
	bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	int32_t ret = BitConverter_ByteArrayToInt32(buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

inline uint64_t bsp__auto_bit_converter__to_uint64(
	bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	uint64_t ret = BitConverter_ByteArrayToUInt64(buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

inline int64_t bsp__auto_bit_converter__to_int64(
	bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	int64_t ret = BitConverter_ByteArrayToInt64(buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

inline float bsp__auto_bit_converter__to_float(
	bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	float ret = BitConverter_ByteArrayToFloat(buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

inline double bsp__auto_bit_converter__to_double(
	bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	double ret = BitConverter_ByteArrayToDouble(buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

/* #endregion */

/* #region 转字节数组 */

inline void bsp__auto_bit_converter__get_bytes_from_uint16(
	bsp__auto_bit_converter *self, uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray(out_buffer + offset, 2);
	}
}

inline void bsp__auto_bit_converter__get_bytes_from_int16(
	bsp__auto_bit_converter *self, int16_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray(out_buffer + offset, 2);
	}
}

inline void bsp__auto_bit_converter__get_bytes_from_uint32(
	bsp__auto_bit_converter *self, uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

inline void bsp__auto_bit_converter__get_bytes_from_int32(
	bsp__auto_bit_converter *self, int32_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromInt32(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

inline void bsp__auto_bit_converter__get_bytes_from_uint64(
	bsp__auto_bit_converter *self, uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt64(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}

inline void bsp__auto_bit_converter__get_bytes_from_int64(
	bsp__auto_bit_converter *self, int64_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}

inline void bsp__auto_bit_converter__get_bytes_from_float(
	bsp__auto_bit_converter *self, float value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

inline void bsp__auto_bit_converter__get_bytes_from_double(
	bsp__auto_bit_converter *self, double value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}

/* #endregion */
