#pragma once
#include <c-bsp-interface/bsp_endian_t.h>
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
#include <c-bsp-interface/stream/Stream.h>

typedef struct ModbusStreamWriter ModbusStreamWriter;

ModbusStreamWriter *ModbusStreamWriter_StackHeapAlloc(Stream *dst_stream,
													  ModbusBitConverterUnit unit);

void ModbusStreamWriter_WriteUInt8(ModbusStreamWriter *self, uint8_t data);
void ModbusStreamWriter_WriteUInt16(ModbusStreamWriter *self, uint16_t data);
void ModbusStreamWriter_WriteUInt32(ModbusStreamWriter *self, uint32_t data);
void ModbusStreamWriter_WriteUInt64(ModbusStreamWriter *self, uint64_t data);
void ModbusStreamWriter_WriteFloat(ModbusStreamWriter *self, float data);
void ModbusStreamWriter_WriteDouble(ModbusStreamWriter *self, double data);

void ModbusStreamWriter_WriteCrc16(ModbusStreamWriter *self,
								   uint16_t crc16_register, bsp_endian_t crc16_endian);
