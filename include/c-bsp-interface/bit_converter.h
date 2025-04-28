#pragma once
#include <stdint.h>

/* #region 转数字 */

uint16_t bsp__bit_converter__byte_array_to_uint16(uint8_t const *buffer, int32_t offset);

int16_t bsp__bit_converter__byte_array_to_int16(uint8_t const *buffer, int32_t offset);

uint16_t bsp__bit_converter__2_byte_to_uint16(uint8_t high, uint8_t low);

uint32_t bsp__bit_converter__byte_array_to_uint32(uint8_t const *buffer, int32_t offset);

int32_t bsp__bit_converter__byte_array_to_int32(uint8_t const *buffer, int32_t offset);

uint32_t bsp__bit_converter__2_uint16_to_uint32(uint16_t high, uint16_t low);

uint32_t bsp__bit_converter__4_byte_to_uint32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);

uint64_t bsp__bit_converter__byte_array_to_uint64(uint8_t const *buffer, int32_t offset);

int64_t bsp__bit_converter__byte_array_to_int64(uint8_t const *buffer, int32_t offset);

float bsp__bit_converter__byte_array_to_float(uint8_t const *buffer, int32_t offset);

double bsp__bit_converter__byte_array_to_double(uint8_t const *buffer, int32_t offset);

/* #endregion */

/* #region 转字节数组 */

void bsp__bit_converter__get_bytes_from_uint16(uint16_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__get_bytes_from_int16(int16_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__get_bytes_from_uint32(uint32_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__get_bytes_from_int32(int32_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__get_bytes_from_uint64(uint64_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__get_bytes_from_int64(int64_t value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__get_bytes_from_float(float value, uint8_t *out_buffer, int32_t offset);

void bsp__bit_converter__get_bytes_from_double(double value, uint8_t *out_buffer, int32_t offset);

/* #endregion */
