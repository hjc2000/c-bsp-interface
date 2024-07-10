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
