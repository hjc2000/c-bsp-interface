#pragma once
#include <c-bsp-interface/Endian.h>
#include <stdint.h>

typedef struct AutoBitConverter
{
	Endian _remote_endian;
} AutoBitConverter;

uint16_t AutoBitConverter_ToUInt16(AutoBitConverter *this, uint8_t *buffer, int offset);
int16_t AutoBitConverter_ToInt16(AutoBitConverter *this, uint8_t *buffer, int offset);

uint32_t AutoBitConverter_ToUInt32(AutoBitConverter *this, uint8_t *buffer, int offset);
int32_t AutoBitConverter_ToInt32(AutoBitConverter *this, uint8_t *buffer, int offset);

uint64_t AutoBitConverter_ToUInt64(AutoBitConverter *this, uint8_t *buffer, int offset);
int64_t AutoBitConverter_ToInt64(AutoBitConverter *this, uint8_t *buffer, int offset);

float AutoBitConverter_ToFloat(AutoBitConverter *this, uint8_t *buffer, int offset);
double AutoBitConverter_ToDouble(AutoBitConverter *this, uint8_t *buffer, int offset);
