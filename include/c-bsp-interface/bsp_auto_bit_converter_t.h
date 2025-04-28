#pragma once
#include <c-bsp-interface/bsp_endian_t.h>
#include <stdint.h>

typedef struct bsp_auto_bit_converter_t
{
	bsp_endian_t _remote_endian;
} bsp_auto_bit_converter_t;

void AutoBitConverter_Initialize(bsp_auto_bit_converter_t *self, bsp_endian_t remote_endian);

/* #region 转数字 */

uint16_t AutoBitConverter_ToUInt16(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset);
int16_t AutoBitConverter_ToInt16(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset);

uint32_t AutoBitConverter_ToUInt32(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset);
int32_t AutoBitConverter_ToInt32(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset);

uint64_t AutoBitConverter_ToUInt64(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset);
int64_t AutoBitConverter_ToInt64(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset);

float AutoBitConverter_ToFloat(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset);
double AutoBitConverter_ToDouble(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset);

/* #endregion */

/* #region 转字节数组 */

void AutoBitConverter_GetBytesFromUInt16(bsp_auto_bit_converter_t *self,
										 uint16_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt16(bsp_auto_bit_converter_t *self,
										int16_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromUInt32(bsp_auto_bit_converter_t *self,
										 uint32_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt32(bsp_auto_bit_converter_t *self,
										int32_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromUInt64(bsp_auto_bit_converter_t *self,
										 uint64_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt64(bsp_auto_bit_converter_t *self,
										int64_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromFloat(bsp_auto_bit_converter_t *self,
										float value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromDouble(bsp_auto_bit_converter_t *self,
										 double value, uint8_t *out_buffer, int32_t offset);

/* #endregion */
