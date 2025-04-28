#pragma once
#include <c-bsp-interface/bsp_endian_t.h>
#include <stdint.h>

typedef struct AutoBitConverter
{
	bsp_endian_t _remote_endian;
} AutoBitConverter;

void AutoBitConverter_Initialize(AutoBitConverter *self, bsp_endian_t remote_endian);

/* #region 转数字 */

uint16_t AutoBitConverter_ToUInt16(AutoBitConverter *self, uint8_t const *buffer, int32_t offset);
int16_t AutoBitConverter_ToInt16(AutoBitConverter *self, uint8_t const *buffer, int32_t offset);

uint32_t AutoBitConverter_ToUInt32(AutoBitConverter *self, uint8_t const *buffer, int32_t offset);
int32_t AutoBitConverter_ToInt32(AutoBitConverter *self, uint8_t const *buffer, int32_t offset);

uint64_t AutoBitConverter_ToUInt64(AutoBitConverter *self, uint8_t const *buffer, int32_t offset);
int64_t AutoBitConverter_ToInt64(AutoBitConverter *self, uint8_t const *buffer, int32_t offset);

float AutoBitConverter_ToFloat(AutoBitConverter *self, uint8_t const *buffer, int32_t offset);
double AutoBitConverter_ToDouble(AutoBitConverter *self, uint8_t const *buffer, int32_t offset);

/* #endregion */

/* #region 转字节数组 */

void AutoBitConverter_GetBytesFromUInt16(AutoBitConverter *self,
										 uint16_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt16(AutoBitConverter *self,
										int16_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromUInt32(AutoBitConverter *self,
										 uint32_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt32(AutoBitConverter *self,
										int32_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromUInt64(AutoBitConverter *self,
										 uint64_t value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromInt64(AutoBitConverter *self,
										int64_t value, uint8_t *out_buffer, int32_t offset);

void AutoBitConverter_GetBytesFromFloat(AutoBitConverter *self,
										float value, uint8_t *out_buffer, int32_t offset);
void AutoBitConverter_GetBytesFromDouble(AutoBitConverter *self,
										 double value, uint8_t *out_buffer, int32_t offset);

/* #endregion */
