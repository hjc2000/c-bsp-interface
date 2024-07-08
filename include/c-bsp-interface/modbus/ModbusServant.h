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
	/// @note 主机发过来一串数据，虽然 modbus 是以记录为单位的，但是主机经常需要将 uint32_t
	/// 之类的数据发送过来，而一个记录是 16 位，只有 2 个字节，所以需要占用多个记录去发送。
	/// 区分数据的字节数的唯一方式就是它的地址。它的地址决定了用途，也被事先规定了这是一个多大的
	/// 数据，所以需要此回调。
	/// @note GetMultibyteDataSize 回调函数会传入字节流中当前位置的字节的 modbus 数据地址，
	/// 用户需要在回调函数的返回值中告知此字节开始的数据是一个多少个字节的数据，这样才能正确触发
	/// Write2ByteCallback，Write4ByteCallback，Write8ByteCallback 等回调。
	///
	/// @param data_addr 数据地址
	/// @return 这个地址的数据是对应什么 ModbusMultibyteSizeEnum
	ModbusMultibyteSizeEnum (*GetMultibyteDataSize)(uint32_t data_addr);

	/// @brief 发送回调函数。
	/// @note 本类对象内部准备好响应帧后会回调此函数，将响应帧发送给主机。
	///
	/// @param buffer 装着响应帧的缓冲区。
	/// @param offset 响应帧在 buffer 中的偏移量。
	/// @param count 响应帧的字节数。
	void (*SendResponse)(uint8_t *buffer, int32_t offset, int32_t count);

	uint16_t (*Read2ByteCallback)(uint32_t data_addr);
	uint32_t (*Read4ByteCallback)(uint32_t data_addr);
	uint64_t (*Read8ByteCallback)(uint32_t data_addr);

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
