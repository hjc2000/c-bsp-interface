#pragma once
#include "c-bsp-interface/endian.h"
#include "type.h"
#include <stdint.h>

typedef struct bsp__auto_bit_converter
{
	bsp__bool _should_reverse;
} bsp__auto_bit_converter;

void bsp__auto_bit_converter__initialize(bsp__auto_bit_converter *self, bsp__endian remote_endian);

/* #region 转数字 */

uint16_t bsp__auto_bit_converter__to_uint16(bsp__auto_bit_converter *self,
											uint8_t const *buffer,
											int32_t offset);

int16_t bsp__auto_bit_converter__to_int16(bsp__auto_bit_converter *self,
										  uint8_t const *buffer,
										  int32_t offset);

uint32_t bsp__auto_bit_converter__to_uint32(bsp__auto_bit_converter *self,
											uint8_t const *buffer,
											int32_t offset);

int32_t bsp__auto_bit_converter__to_int32(bsp__auto_bit_converter *self,
										  uint8_t const *buffer,
										  int32_t offset);

uint64_t bsp__auto_bit_converter__to_uint64(bsp__auto_bit_converter *self,
											uint8_t const *buffer,
											int32_t offset);

int64_t bsp__auto_bit_converter__to_int64(bsp__auto_bit_converter *self,
										  uint8_t const *buffer,
										  int32_t offset);

float bsp__auto_bit_converter__to_float(bsp__auto_bit_converter *self,
										uint8_t const *buffer,
										int32_t offset);

double bsp__auto_bit_converter__to_double(bsp__auto_bit_converter *self,
										  uint8_t const *buffer,
										  int32_t offset);

/* #endregion */

/* #region 转字节数组 */

void bsp__auto_bit_converter__get_bytes_from_uint16(bsp__auto_bit_converter *self, uint16_t value, uint8_t *out_buffer, int32_t offset);

void bsp__auto_bit_converter__get_bytes_from_int16(bsp__auto_bit_converter *self, int16_t value, uint8_t *out_buffer, int32_t offset);

void bsp__auto_bit_converter__get_bytes_from_uint32(bsp__auto_bit_converter *self, uint32_t value, uint8_t *out_buffer, int32_t offset);

void bsp__auto_bit_converter__get_bytes_from_int32(bsp__auto_bit_converter *self, int32_t value, uint8_t *out_buffer, int32_t offset);

void bsp__auto_bit_converter__get_bytes_from_uint64(bsp__auto_bit_converter *self, uint64_t value, uint8_t *out_buffer, int32_t offset);

void bsp__auto_bit_converter__get_bytes_from_int64(bsp__auto_bit_converter *self, int64_t value, uint8_t *out_buffer, int32_t offset);

void bsp__auto_bit_converter__get_bytes_from_float(bsp__auto_bit_converter *self, float value, uint8_t *out_buffer, int32_t offset);

void bsp__auto_bit_converter__get_bytes_from_double(bsp__auto_bit_converter *self, double value, uint8_t *out_buffer, int32_t offset);

/* #endregion */
