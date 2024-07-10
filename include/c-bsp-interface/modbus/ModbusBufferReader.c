#include "ModbusBufferReader.h"
#include <c-bsp-interface/memory/StackHeap.h>

typedef struct ModbusBufferReader
{
	uint8_t *_buffer;
	int32_t _position;
	ModbusBitConverterUnit _unit;
} ModbusBufferReader;

ModbusBufferReader *ModbusBufferReader_StackHeapAlloc(ModbusBitConverterUnit unit)
{
	ModbusBufferReader *self = StackHeapObjAlloc(sizeof(ModbusBufferReader));
	self->_buffer = 0;
	self->_position = 0;
	self->_unit = unit;
	return self;
}

void ModbusBufferReader_SetBuffer(ModbusBufferReader *self, uint8_t *buffer)
{
	self->_buffer = buffer;
}

uint8_t ModbusBufferReader_ReadUInt8(ModbusBufferReader *self)
{
	uint8_t value = self->_buffer[self->_position];
	self->_position++;
	return value;
}

int8_t ModbusBufferReader_ReadInt8(ModbusBufferReader *self)
{
	int8_t value = self->_buffer[self->_position];
	self->_position++;
	return value;
}

uint16_t ModbusBufferReader_ReadUInt16(ModbusBufferReader *self)
{
	uint16_t value = ModbusBitConverter_ToUInt16(self->_unit, self->_buffer, self->_position);
	self->_position += 2;
	return value;
}

int16_t ModbusBufferReader_ReadInt16(ModbusBufferReader *self)
{
	int16_t value = ModbusBitConverter_ToInt16(self->_unit, self->_buffer, self->_position);
	self->_position += 2;
	return value;
}

uint32_t ModbusBufferReader_ReadUInt32(ModbusBufferReader *self)
{
	uint32_t value = ModbusBitConverter_ToUInt32(self->_unit, self->_buffer, self->_position);
	self->_position += 4;
	return value;
}

int32_t ModbusBufferReader_ReadInt32(ModbusBufferReader *self)
{
	int32_t value = ModbusBitConverter_ToInt32(self->_unit, self->_buffer, self->_position);
	self->_position += 4;
	return value;
}

uint64_t ModbusBufferReader_ReadUInt64(ModbusBufferReader *self)
{
	uint64_t value = ModbusBitConverter_ToUInt64(self->_unit, self->_buffer, self->_position);
	self->_position += 8;
	return value;
}

int64_t ModbusBufferReader_ReadInt64(ModbusBufferReader *self)
{
	int64_t value = ModbusBitConverter_ToUInt64(self->_unit, self->_buffer, self->_position);
	self->_position += 8;
	return value;
}

float ModbusBufferReader_ReadFloat(ModbusBufferReader *self)
{
	float value = ModbusBitConverter_ToFloat(self->_unit, self->_buffer, self->_position);
	self->_position += 4;
	return value;
}

double ModbusBufferReader_ReadDouble(ModbusBufferReader *self)
{
	double value = ModbusBitConverter_ToFloat(self->_unit, self->_buffer, self->_position);
	self->_position += 8;
	return value;
}
