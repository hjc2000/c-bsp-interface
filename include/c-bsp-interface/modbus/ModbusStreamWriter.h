#pragma once
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
#include <c-bsp-interface/stream/Stream.h>

typedef struct ModbusStreamWriter ModbusStreamWriter;

ModbusStreamWriter *ModbusStreamWriter_StackHeapAlloc(Stream *dst_stream,
													  ModbusBitConverterUnit unit);

void ModbusStreamWriter_WriteUInt8(ModbusStreamWriter *self, uint8_t data);
void ModbusStreamWriter_WriteUInt16(ModbusStreamWriter *self, uint16_t data);
void ModbusStreamWriter_WriteUInt32(ModbusStreamWriter *self, uint32_t data);
void ModbusStreamWriter_WriteUInt64(ModbusStreamWriter *self, uint64_t data);