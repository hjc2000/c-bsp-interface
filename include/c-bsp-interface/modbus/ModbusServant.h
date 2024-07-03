#pragma once
#include <c-bsp-interface/Endian.h>
#include <c-bsp-interface/container/Stack.h>
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
#include <c-bsp-interface/modbus/ModbusCrc16.h>
#include <stdint.h>

/// @brief 发送数据时使用的单位
typedef enum ModbusServant_SendingUnit
{
	/// @brief 以记录为单位。这是 modbus 保持寄存器的最小单位。
	ModbusServant_SendingUnit_Record,

	/// @brief 以整体为一个单位，不拆分成记录
	ModbusServant_ReverseMethod_Whole,
} ModbusServant_SendingUnit;

/// @brief modbus 从机
typedef struct ModbusServant
{
#pragma region private
	/// @brief 从机站号
	uint8_t _servant_address;
	ModbusCrc16 _crc;
	Endian _crc16_endian;
	ModbusBitConverterUnit _bit_converter_unit;
	Stack *_send_buffer_stack;
#pragma endregion

#pragma region 主机请求回调
	/// @brief 功能码 0x03，读一组保持寄存器。
	/// @param data_addr 数据地址
	/// @param record_count 记录数
	void (*ReadHoldingRegistersCallback)(uint32_t data_addr, int32_t record_count);

	/// @brief 功能码 0x10，写一组保持寄存器。
	void (*WriteHoldingRegistersCallback)(uint32_t data_addr, uint8_t *buffer, int32_t count);
#pragma endregion

} ModbusServant;

/// @brief 准备一个静态的 ModbusServant 对象，传进来进行初始化。
/// @param o
/// @param servant_address
/// @param crc16_endian
/// @param bit_converter_unit
void ModbusServant_Init(ModbusServant *o,
						uint8_t servant_address,
						Endian crc16_endian,
						ModbusBitConverterUnit bit_converter_unit);

/// @brief 将接收缓冲区送给 ModbusServant 进行分析。分析完后会触发回调。
/// @param o
/// @param buffer
/// @param offset
/// @param count
void ModbusServant_ParseReceivedBuffer(ModbusServant *o,
									   uint8_t *buffer, int32_t offset, int32_t count);
