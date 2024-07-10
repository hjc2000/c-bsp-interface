#include "ModbusBufferReader.h"

typedef struct ModbusBufferReader
{
	uint8_t *_buffer;
	uint8_t *_position;
	ModbusBitConverterUnit _unit;
} ModbusBufferReader;
