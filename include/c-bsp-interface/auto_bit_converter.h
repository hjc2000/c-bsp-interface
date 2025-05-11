#pragma once
#include "c-bsp-interface/endian.h"
#include "type.h"
#include <stdint.h>

typedef struct bsp_auto_bit_converter
{
	bsp_bool _should_reverse;
} bsp_auto_bit_converter;

void bsp_auto_bit_converter_initialize(bsp_auto_bit_converter *self, bsp_endian_enum remote_endian);

/* #region 转数字 */

uint16_t bsp_auto_bit_converter_to_uint16(bsp_auto_bit_converter *self,
										  uint8_t const *buffer,
										  int32_t offset);

int16_t bsp_auto_bit_converter_to_int16(bsp_auto_bit_converter *self,
										uint8_t const *buffer,
										int32_t offset);

uint32_t bsp_auto_bit_converter_to_uint32(bsp_auto_bit_converter *self,
										  uint8_t const *buffer,
										  int32_t offset);

int32_t bsp_auto_bit_converter_to_int32(bsp_auto_bit_converter *self,
										uint8_t const *buffer,
										int32_t offset);

uint64_t bsp_auto_bit_converter_to_uint64(bsp_auto_bit_converter *self,
										  uint8_t const *buffer,
										  int32_t offset);

int64_t bsp_auto_bit_converter_to_int64(bsp_auto_bit_converter *self,
										uint8_t const *buffer,
										int32_t offset);

float bsp_auto_bit_converter_to_float(bsp_auto_bit_converter *self,
									  uint8_t const *buffer,
									  int32_t offset);

double bsp_auto_bit_converter_to_double(bsp_auto_bit_converter *self,
										uint8_t const *buffer,
										int32_t offset);

/* #endregion */

/* #region 转字节数组 */

void bsp_auto_bit_converter_get_bytes_from_uint16(bsp_auto_bit_converter *self, uint16_t value, uint8_t *out_buffer, int32_t offset);

void bsp_auto_bit_converter_get_bytes_from_int16(bsp_auto_bit_converter *self, int16_t value, uint8_t *out_buffer, int32_t offset);

void bsp_auto_bit_converter_get_bytes_from_uint32(bsp_auto_bit_converter *self, uint32_t value, uint8_t *out_buffer, int32_t offset);

void bsp_auto_bit_converter_get_bytes_from_int32(bsp_auto_bit_converter *self, int32_t value, uint8_t *out_buffer, int32_t offset);

void bsp_auto_bit_converter_get_bytes_from_uint64(bsp_auto_bit_converter *self, uint64_t value, uint8_t *out_buffer, int32_t offset);

void bsp_auto_bit_converter_get_bytes_from_int64(bsp_auto_bit_converter *self, int64_t value, uint8_t *out_buffer, int32_t offset);

void bsp_auto_bit_converter_get_bytes_from_float(bsp_auto_bit_converter *self, float value, uint8_t *out_buffer, int32_t offset);

void bsp_auto_bit_converter_get_bytes_from_double(bsp_auto_bit_converter *self, double value, uint8_t *out_buffer, int32_t offset);

/* #endregion */
