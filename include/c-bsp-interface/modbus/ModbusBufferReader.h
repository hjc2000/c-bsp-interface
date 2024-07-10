#pragma once
#include <c-bsp-interface/modbus/ModbusBitConverter.h>

/// @brief 读取接收缓冲区。每次读取，内部记录的当前位置会自动递增。
typedef struct ModbusBufferReader ModbusBufferReader;

/// @brief 在栈堆上构造
/// @warning 构造后需要使用 ModbusBufferReader_SetBuffer 设置一个缓冲区才能读取。
/// 读取完 1 个缓冲区后需要再次调用 ModbusBufferReader_SetBuffer 设置一个新的缓冲区。
///
/// @param unit 转换单位
/// @return
ModbusBufferReader *ModbusBufferReader_StackHeapAlloc(ModbusBitConverterUnit unit);

/// @brief 设置一个缓冲区。设置后才能读取，否则就会读取空指针或野指针指向的内存。
/// @param self
/// @param buffer
void ModbusBufferReader_SetBuffer(ModbusBufferReader *self, uint8_t *buffer);

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
