#pragma once
#include <c-bsp-interface/modbus/ModbusBitConverter.h>

/// @brief 读取接收缓冲区。每次读取，内部记录的当前位置会自动递增。
typedef struct ModbusBufferReader
{
	uint8_t *_buffer;
	int32_t _position;
	ModbusBitConverterUnit _unit;
} ModbusBufferReader;

/// @brief 初始化
/// @param self
/// @param buffer
/// @param unit
void ModbusBufferReader_Init(ModbusBufferReader *self,
							 uint8_t *buffer,
							 ModbusBitConverterUnit unit);

uint8_t ModbusBufferReader_ReadUInt8(ModbusBufferReader *self);
int8_t ModbusBufferReader_ReadInt8(ModbusBufferReader *self);

uint16_t ModbusBufferReader_ReadUInt16(ModbusBufferReader *self);
int16_t ModbusBufferReader_ReadInt16(ModbusBufferReader *self);

uint32_t ModbusBufferReader_ReadUInt32(ModbusBufferReader *self);
int32_t ModbusBufferReader_ReadInt32(ModbusBufferReader *self);

uint64_t ModbusBufferReader_ReadUInt64(ModbusBufferReader *self);
int64_t ModbusBufferReader_ReadInt64(ModbusBufferReader *self);

float ModbusBufferReader_ReadFloat(ModbusBufferReader *self);
double ModbusBufferReader_ReadDouble(ModbusBufferReader *self);
