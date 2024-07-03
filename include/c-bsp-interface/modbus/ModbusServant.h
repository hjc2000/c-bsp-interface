#pragma once
#include <c-bsp-interface/Endian.h>
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
#include <c-bsp-interface/modbus/ModbusMultibyteSizeEnum.h>
#include <stdint.h>

/// @brief 读写回调函数中心
typedef struct ModbusServantReadWriteCallbackHub
{
	/// @brief 传入数据地址，返回这个数据是对应什么 ModbusMultibyteSizeEnum
	/// @note 此函数指针必须设置。
	///
	/// @param data_addr 数据地址
	/// @return 这个地址的数据是对应什么 ModbusMultibyteSizeEnum
	ModbusMultibyteSizeEnum (*GetMultibyteDataSize)(uint32_t data_addr);

	uint8_t (*ReadByteCallback)(uint32_t data_addr);
	uint16_t (*Read2ByteCallback)(uint32_t data_addr);
	uint32_t (*Read4ByteCallback)(uint32_t data_addr);
	uint64_t (*Read8ByteCallback)(uint32_t data_addr);

	void (*WriteByteCallback)(uint32_t data_addr, uint8_t value);
	void (*Write2ByteCallback)(uint32_t data_addr, uint16_t value);
	void (*Write4ByteCallback)(uint32_t data_addr, uint32_t value);
	void (*Write8ByteCallback)(uint32_t data_addr, uint64_t value);

	uint8_t (*ReadBitCallback)(uint32_t data_addr);
	void (*WriteBitCallback)(uint32_t data_addr, uint8_t value);
} ModbusServantReadWriteCallbackHub;

/// @brief modbus 从机
typedef struct ModbusServant ModbusServant;

/// @brief 准备一个静态的 ModbusServant 对象，传进来进行初始化。
/// @param o
/// @param servant_address 本从站的地址（站号）。
/// @param crc16_endian CRC16 的 2 个字节用什么字节序存放。
/// @param bit_converter_unit 比特转换的单位。
///
/// @param read_write_callback_hub 调用者在栈上构造此结构体，为字段赋值后将指针传进来，
/// 随后这个对象可被销毁，内部不会引用此对象。
void ModbusServant_Init(ModbusServant *o,
						uint8_t servant_address,
						Endian crc16_endian,
						ModbusBitConverterUnit bit_converter_unit,
						ModbusServantReadWriteCallbackHub *read_write_callback_hub);

/// @brief 将接收缓冲区送给 ModbusServant 进行分析。分析完后会触发回调。
/// @param o
/// @param buffer
/// @param offset
/// @param count
void ModbusServant_ParseReceivedBuffer(ModbusServant *o,
									   uint8_t *buffer, int32_t offset, int32_t count);
