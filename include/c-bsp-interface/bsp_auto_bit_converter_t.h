#pragma once
#include "c-bsp-interface/BitConverter.h"
#include "c-bsp-interface/Reverse.h"
#include <c-bsp-interface/bsp_endian_t.h>
#include <stdint.h>

typedef struct bsp_auto_bit_converter_t
{
	bsp_endian_t _remote_endian;
} bsp_auto_bit_converter_t;

extern inline void bsp_auto_bit_converter_t__initialize(bsp_auto_bit_converter_t *self,
														bsp_endian_t remote_endian)
{
	self->_remote_endian = remote_endian;
}

extern inline uint8_t bsp_auto_bit_converter_t__should_reverse(bsp_auto_bit_converter_t *self)
{
	return bsp_local_host_endian() != self->_remote_endian;
}

/* #region 转数字 */

extern inline uint16_t bsp_auto_bit_converter_t__to_uint16(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset)
{
	uint16_t ret = BitConverter_ByteArrayToUInt16(buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

extern inline int16_t bsp_auto_bit_converter_t__to_int16(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset)
{
	int16_t ret = BitConverter_ByteArrayToInt16(buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

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
