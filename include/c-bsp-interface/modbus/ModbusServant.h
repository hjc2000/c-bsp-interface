#pragma once
#include <c-bsp-interface/Endian.h>
#include <c-bsp-interface/container/Stack.h>
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
#include <c-bsp-interface/modbus/ModbusCrc16.h>
#include <c-bsp-interface/modbus/ModbusMultibyteSizeEnum.h>
#include <stdint.h>

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

	/// @brief 传入数据地址，返回这个数据是对应什么 ModbusMultibyteSizeEnum
	/// @param data_addr 数据地址
	/// @return 这个地址的数据是对应什么 ModbusMultibyteSizeEnum
	ModbusMultibyteSizeEnum (*GetMultibyteDataSize)(uint32_t data_addr);
#pragma endregion

#pragma region 主机请求回调
	/// @brief 功能码 0x03，读一组保持寄存器。
	/// @param data_addr 数据地址
	/// @param record_count 记录数
	void (*ReadHoldingRegistersCallback)(uint32_t data_addr, int32_t record_count);

	/// @brief 功能码 0x10，写一组保持寄存器。
	/// @param data_addr 数据地址
	/// @param buffer 主机发过来的要写入的数据值组成的字节数组。应用层自己选择将这里面的字节解释成什么样。
	/// @param count buffer 的字节数。
	void (*WriteHoldingRegistersCallback)(uint32_t data_addr, uint8_t *buffer, int32_t count);
#pragma endregion

} ModbusServant;

/// @brief 准备一个静态的 ModbusServant 对象，传进来进行初始化。
/// @param o
/// @param servant_address 本从站的地址（站号）。
/// @param crc16_endian CRC16 的 2 个字节用什么字节序存放。
/// @param bit_converter_unit 比特转换的单位。
/// @param get_multibyte_data_size 传入数据地址，返回这个数据是对应什么 ModbusMultibyteSizeEnum
void ModbusServant_Init(ModbusServant *o,
						uint8_t servant_address,
						Endian crc16_endian,
						ModbusBitConverterUnit bit_converter_unit,
						ModbusMultibyteSizeEnum (*get_multibyte_data_size)(uint32_t data_addr));

/// @brief 将接收缓冲区送给 ModbusServant 进行分析。分析完后会触发回调。
/// @param o
/// @param buffer
/// @param offset
/// @param count
void ModbusServant_ParseReceivedBuffer(ModbusServant *o,
									   uint8_t *buffer, int32_t offset, int32_t count);
