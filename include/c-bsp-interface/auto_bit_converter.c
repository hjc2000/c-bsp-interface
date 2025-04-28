#include "auto_bit_converter.h" // IWYU pragma: keep
#include "c-bsp-interface/bit_converter.h"
#include "c-bsp-interface/reverse.h"

void bsp__auto_bit_converter__initialize(bsp__auto_bit_converter *self, bsp__endian remote_endian)
{
	self->_should_reverse = bsp__local_host_endian() != remote_endian;
}

// #region 转数字

uint16_t bsp__auto_bit_converter__to_uint16(bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	uint16_t ret = bsp__bit_converter__byte_array_to_uint16(buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array((uint8_t *)(&ret), sizeof(ret));
	}

	return ret;
}

int16_t bsp__auto_bit_converter__to_int16(bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	int16_t ret = bsp__bit_converter__byte_array_to_int16(buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array((uint8_t *)(&ret), sizeof(ret));
	}

	return ret;
}

uint32_t bsp__auto_bit_converter__to_uint32(bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	uint32_t ret = bsp__bit_converter__byte_array_to_uint32(buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array((uint8_t *)(&ret), sizeof(ret));
	}

	return ret;
}

int32_t bsp__auto_bit_converter__to_int32(bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	int32_t ret = bsp__bit_converter__byte_array_to_int32(buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array((uint8_t *)(&ret), sizeof(ret));
	}

	return ret;
}

uint64_t bsp__auto_bit_converter__to_uint64(bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	uint64_t ret = bsp__bit_converter__byte_array_to_uint64(buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array((uint8_t *)(&ret), sizeof(ret));
	}

	return ret;
}

int64_t bsp__auto_bit_converter__to_int64(bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	int64_t ret = bsp__bit_converter__byte_array_to_int64(buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array((uint8_t *)(&ret), sizeof(ret));
	}

	return ret;
}

float bsp__auto_bit_converter__to_float(bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	float ret = bsp__bit_converter__byte_array_to_float(buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array((uint8_t *)(&ret), sizeof(ret));
	}

	return ret;
}

double bsp__auto_bit_converter__to_double(bsp__auto_bit_converter *self, uint8_t const *buffer, int32_t offset)
{
	double ret = bsp__bit_converter__byte_array_to_double(buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array((uint8_t *)(&ret), sizeof(ret));
	}

	return ret;
}

// #endregion

// #region 转字节数组

void bsp__auto_bit_converter__get_bytes_from_uint16(bsp__auto_bit_converter *self, uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	bsp__bit_converter__get_bytes_from_uint16(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array(out_buffer + offset, sizeof(value));
	}
}

void bsp__auto_bit_converter__get_bytes_from_int16(bsp__auto_bit_converter *self, int16_t value, uint8_t *out_buffer, int32_t offset)
{
	bsp__bit_converter__get_bytes_from_int16(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array(out_buffer + offset, sizeof(value));
	}
}

void bsp__auto_bit_converter__get_bytes_from_uint32(bsp__auto_bit_converter *self, uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	bsp__bit_converter__get_bytes_from_uint32(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array(out_buffer + offset, sizeof(value));
	}
}

void bsp__auto_bit_converter__get_bytes_from_int32(bsp__auto_bit_converter *self, int32_t value, uint8_t *out_buffer, int32_t offset)
{
	bsp__bit_converter__get_bytes_from_int32(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array(out_buffer + offset, sizeof(value));
	}
}

void bsp__auto_bit_converter__get_bytes_from_uint64(bsp__auto_bit_converter *self, uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	bsp__bit_converter__get_bytes_from_uint64(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array(out_buffer + offset, sizeof(value));
	}
}

void bsp__auto_bit_converter__get_bytes_from_int64(bsp__auto_bit_converter *self, int64_t value, uint8_t *out_buffer, int32_t offset)
{
	bsp__bit_converter__get_bytes_from_int64(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array(out_buffer + offset, sizeof(value));
	}
}

void bsp__auto_bit_converter__get_bytes_from_float(bsp__auto_bit_converter *self, float value, uint8_t *out_buffer, int32_t offset)
{
	bsp__bit_converter__get_bytes_from_float(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array(out_buffer + offset, sizeof(value));
	}
}

void bsp__auto_bit_converter__get_bytes_from_double(bsp__auto_bit_converter *self, double value, uint8_t *out_buffer, int32_t offset)
{
	bsp__bit_converter__get_bytes_from_double(value, out_buffer, offset);
	if (self->_should_reverse)
	{
		bsp__reverse_byte_array(out_buffer + offset, sizeof(value));
	}
}

// #endregion
