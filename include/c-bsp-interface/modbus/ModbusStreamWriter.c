#include "ModbusStreamWriter.h"
#include <c-bsp-interface/memory/StackHeap.h>

typedef struct ModbusStreamWriter
{
	Stream *_stream;
	ModbusBitConverterUnit _unit;
} ModbusStreamWriter;

ModbusStreamWriter *ModbusStreamWriter_StackHeapAlloc(Stream *dst_stream,
													  ModbusBitConverterUnit unit)
{
	ModbusStreamWriter *self = StackHeapObjAlloc(sizeof(ModbusStreamWriter));
	self->_stream = dst_stream;
	self->_unit = unit;
	return self;
}

void ModbusStreamWriter_WriteUInt8(ModbusStreamWriter *self, uint8_t data)
{
	self->_stream->Write(self->_stream->_self, &data, 0, 1);
}

void ModbusStreamWriter_WriteUInt16(ModbusStreamWriter *self, uint16_t data)
{
	uint8_t temp_buffer[sizeof(data)];
	ModbusBitConverter_GetBytesFromUInt16(self->_unit,
										  data,
										  temp_buffer,
										  0);

	self->_stream->Write(self->_stream->_self, temp_buffer, 0, sizeof(temp_buffer));
}

void ModbusStreamWriter_WriteUInt32(ModbusStreamWriter *self, uint32_t data)
{
	uint8_t temp_buffer[sizeof(data)];
	ModbusBitConverter_GetBytesFromUInt32(self->_unit,
										  data,
										  temp_buffer,
										  0);

	self->_stream->Write(self->_stream->_self, temp_buffer, 0, sizeof(temp_buffer));
}

void ModbusStreamWriter_WriteUInt64(ModbusStreamWriter *self, uint64_t data)
{
	uint8_t temp_buffer[sizeof(data)];
	ModbusBitConverter_GetBytesFromUInt64(self->_unit,
										  data,
										  temp_buffer,
										  0);

	self->_stream->Write(self->_stream->_self, temp_buffer, 0, sizeof(temp_buffer));
}
