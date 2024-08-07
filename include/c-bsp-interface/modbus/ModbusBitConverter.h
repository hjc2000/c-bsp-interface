#pragma once
#include <stdint.h>

/*
	收发的数据为
		0x12345678

	规定内存地址从下往上递增，最下方的是最低地址。

	大端序的内存布局为：
		0x78
		0x56
		0x34
		0x12

	小端序的内存布局为：
		0x12
		0x34
		0x56
		0x78

	用 modbus 发送，字节流为 0x12, 0x34, 0x56, 0x78，即以大端序发送。
	接收方接收到了字节流，放到字节数组中，从 0 索引处开始放，则放到内存后的布局为：
		0x78
		0x56
		0x34
		0x12

	这是大端序的内存布局。如果是大端序的计算机，直接这样就行了，如果是小端序的计算机，需要翻转
	这个字节数组。

	用 modbus 还有一种方式是逐个记录按大端序发送。0x12345678 会被拆成 2 个记录。
		* 第 1 个记录为低 16 位，发送的字节流为 0x56, 0x78
		* 第 2 个记录为高 16 位，发送的字节流为 0x12, 0x34
	则总的字节流为：0x56, 0x78, 0x12, 0x34

	接收端接收后，放到字节数组中，内存布局为：
		0x34
		0x12
		0x78
		0x56

	如果是小端序计算机，只需要逐 2 字节翻转，就会变成 0x12345678 的小端序内存布局，即
		0x12
		0x34
		0x56
		0x78
	如果是大端序的计算机，需要在此基础上再执行整体翻转。
 */

/// @brief ModbusBitConverter 进行比特转换时的操作单位。
typedef enum ModbusBitConverterUnit
{
	/// @brief 以记录为单位。这是 modbus 保持寄存器的最小单位。
	ModbusBitConverterUnit_Record,

	/// @brief 以整体为一个单位，不拆分成记录
	ModbusBitConverterUnit_Whole,
} ModbusBitConverterUnit;

#pragma region 转数字
uint8_t ModbusBitConverter_ToUInt8(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset);

uint8_t ModbusBitConverter_ToInt8(ModbusBitConverterUnit unit,
								  uint8_t const *buffer, int32_t offset);

uint16_t ModbusBitConverter_ToUInt16(ModbusBitConverterUnit unit,
									 uint8_t const *buffer, int32_t offset);

int16_t ModbusBitConverter_ToInt16(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset);

uint32_t ModbusBitConverter_ToUInt32(ModbusBitConverterUnit unit,
									 uint8_t const *buffer, int32_t offset);

int32_t ModbusBitConverter_ToInt32(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset);

uint64_t ModbusBitConverter_ToUInt64(ModbusBitConverterUnit unit,
									 uint8_t const *buffer, int32_t offset);

int64_t ModbusBitConverter_ToInt64(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset);

float ModbusBitConverter_ToFloat(ModbusBitConverterUnit unit,
								 uint8_t const *buffer, int32_t offset);

double ModbusBitConverter_ToDouble(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset);
#pragma endregion

#pragma region 转字节数组
void ModbusBitConverter_GetBytesFromUInt8(ModbusBitConverterUnit unit,
										  uint8_t value, uint8_t *out_buffer, int32_t offset);

void ModbusBitConverter_GetBytesFromUInt16(ModbusBitConverterUnit unit,
										   uint16_t value, uint8_t *out_buffer, int32_t offset);

void ModbusBitConverter_GetBytesFromInt16(ModbusBitConverterUnit unit,
										  int16_t value, uint8_t *out_buffer, int32_t offset);

void ModbusBitConverter_GetBytesFromUInt32(ModbusBitConverterUnit unit,
										   uint32_t value, uint8_t *out_buffer, int32_t offset);

void ModbusBitConverter_GetBytesFromInt32(ModbusBitConverterUnit unit,
										  int32_t value, uint8_t *out_buffer, int32_t offset);

void ModbusBitConverter_GetBytesFromUInt64(ModbusBitConverterUnit unit,
										   uint64_t value, uint8_t *out_buffer, int32_t offset);

void ModbusBitConverter_GetBytesFromInt64(ModbusBitConverterUnit unit,
										  int64_t value, uint8_t *out_buffer, int32_t offset);

void ModbusBitConverter_GetBytesFromFloat(ModbusBitConverterUnit unit,
										  float value, uint8_t *out_buffer, int32_t offset);

void ModbusBitConverter_GetBytesFromDouble(ModbusBitConverterUnit unit,
										   double value, uint8_t *out_buffer, int32_t offset);
#pragma endregion
