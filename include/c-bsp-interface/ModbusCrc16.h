#pragma once
#include <stdint.h>

typedef struct ModbusCrc16
{
	uint16_t _crc16_register;
	uint16_t _polynomial;
} ModbusCrc16;

void ModbusCrc16_Init(ModbusCrc16 *this);
void ModbusCrc16_Add(ModbusCrc16 *this, uint8_t data);
void ModbusCrc16_AddArray(ModbusCrc16 *this, uint8_t *datas, uint32_t count);
