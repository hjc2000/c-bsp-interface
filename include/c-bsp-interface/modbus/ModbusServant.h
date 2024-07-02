#pragma once
#include <c-bsp-interface/AutoBitConverter.h>
#include <c-bsp-interface/Endian.h>
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
	AutoBitConverter *_auto_bit_converter;
#pragma endregion

#pragma region 主机请求回调
	/// @brief 功能码 0x03，读一组保持寄存器。
	/// @param data_addr 数据地址
	/// @param record_count 记录数
	void (*ReadHoldingRegistersCallback)(uint32_t data_addr, int32_t record_count);

	/// @brief 功能码 0x10，写一组保持寄存器。
	void (*WriteHoldingRegistersCallback)(uint32_t data_addr,
										  uint8_t *buffer,
										  int32_t count);
#pragma endregion

} ModbusServant;

/// @brief 准备一个静态的 ModbusServant 对象，传进来进行初始化。
/// @param
/// @param servant_address
/// @param red_led
/// @param green_led
/// @param key0
/// @param key1
void ModbusServant_Init(ModbusServant *this,
						uint8_t servant_address,
						Endian crc16_endian);

/// @brief 将接收缓冲区送给 ModbusServant 进行分析。分析完后会触发回调。
/// @param
/// @param buffer
/// @param offset
/// @param count
void ModbusServant_ParseReceivedBuffer(ModbusServant *this,
									   uint8_t *buffer, int32_t offset, int32_t count);

/// @brief 发送一个 uint32_t 数据。
/// @param
/// @param value
///
/// @param unit 这个 uint32_t 数据要用什么单位发送。
/// @example 例如 value = 0x12345678。
/// @li 如果以记录为单位发送，则低 16 位作为第 1 个记录，用大端序发送。
/// 	高 16 位作为第 2 个记录，用大端序发送。则字节流为 0x56, 0x78, 0x12, 0x34，
///		从左往右依次发送。
/// @li 如果以整体为一个单位发送，则整体用大端序发送。发送的字节流为：0x12, 0x34, 0x56, 0x78
///		从左往右依次发送。
void ModbusServant_SendUInt32(ModbusServant *this,
							  uint32_t value,
							  ModbusServant_SendingUnit unit);
