#pragma once
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
#include <c-bsp-interface/stream/Stream.h>

typedef struct ModbusStreamWriter ModbusStreamWriter;

ModbusStreamWriter *ModbusStreamWriter_StackHeapAlloc(Stream *dst_stream,
													  ModbusBitConverterUnit unit);
