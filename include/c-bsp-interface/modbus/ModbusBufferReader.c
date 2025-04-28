#include "ModbusBufferReader.h"
#include <c-bsp-interface/memory/StackHeap.h>

void ModbusBufferReader_Init(ModbusBufferReader *self,
							 uint8_t *buffer,
							 ModbusBitConverterUnit unit)
{
	self->_buffer = buffer;
	self->_position = 0;
	self->_unit = unit;
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
	uint16_t value = Modbusbsp__bit_converter__ToUInt16(self->_unit, self->_buffer, self->_position);
	self->_position += 2;
	return value;
}

int16_t ModbusBufferReader_ReadInt16(ModbusBufferReader *self)
{
	int16_t value = Modbusbsp__bit_converter__ToInt16(self->_unit, self->_buffer, self->_position);
	self->_position += 2;
	return value;
}

uint32_t ModbusBufferReader_ReadUInt32(ModbusBufferReader *self)
{
	uint32_t value = Modbusbsp__bit_converter__ToUInt32(self->_unit, self->_buffer, self->_position);
	self->_position += 4;
	return value;
}

int32_t ModbusBufferReader_ReadInt32(ModbusBufferReader *self)
{
	int32_t value = Modbusbsp__bit_converter__ToInt32(self->_unit, self->_buffer, self->_position);
	self->_position += 4;
	return value;
}

uint64_t ModbusBufferReader_ReadUInt64(ModbusBufferReader *self)
{
	uint64_t value = Modbusbsp__bit_converter__ToUInt64(self->_unit, self->_buffer, self->_position);
	self->_position += 8;
	return value;
}

int64_t ModbusBufferReader_ReadInt64(ModbusBufferReader *self)
{
	int64_t value = Modbusbsp__bit_converter__ToInt64(self->_unit, self->_buffer, self->_position);
	self->_position += 8;
	return value;
}

float ModbusBufferReader_ReadFloat(ModbusBufferReader *self)
{
	float value = Modbusbsp__bit_converter__ToFloat(self->_unit, self->_buffer, self->_position);
	self->_position += 4;
	return value;
}

double ModbusBufferReader_ReadDouble(ModbusBufferReader *self)
{
	double value = Modbusbsp__bit_converter__ToDouble(self->_unit, self->_buffer, self->_position);
	self->_position += 8;
	return value;
}
