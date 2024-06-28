#pragma once
#include <c-bsp-interface/Endian.h>
#include <c-bsp-interface/modbus/ModbusCrc16.h>
#include <stdint.h>

/// @brief modbus 从机
typedef struct ModbusServant
{
#pragma region private
	/// @brief 从机站号
	uint8_t _servant_address;
	ModbusCrc16 _crc;
	Endian _crc16_endian;
#pragma endregion

#pragma region 主机请求回调
	uint8_t (*ReadBitCallback)(uint32_t bit_addr);
	void (*WriteBitCallback)(uint32_t bit_addr, uint8_t value);

	/// @brief 主机请求读取 16 位保持寄存器时会触发此回调。
	/// @note 每次回调只读取 1 个 16 位保持寄存器，主机请求读取一组保持寄存器，则会回调多次。
	///
	/// @param data_addr 数据地址
	/// @return 返回的值将被发送给主机。
	uint16_t (*ReadUint16Callback)(uint32_t data_addr);

	/// @brief 主机请求写 16 位保持寄存器时会触发此回调。
	/// @note 每次回调只写一个 16 位数据，主机要写一组，则会触发多次回调。
	///
	/// @param data_addr 数据地址
	/// @param value 数据值
	void (*WriteUInt16Callback)(uint32_t data_addr, uint16_t value);

	uint32_t (*ReadUInt32Callback)(uint32_t data_addr);
	void (*WriteUInt32Callback)(uint32_t data_addr, uint32_t value);
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

/// @brief 将缓冲区送给 ModbusServant
/// @param
/// @param buffer
/// @param offset
/// @param count
void ModbusServant_FeedBuffer(ModbusServant *this,
							  uint8_t *buffer, int32_t offset, int32_t count);
