#pragma once
#include <c-bsp-interface/AsyncStream.h>
#include <c-bsp-interface/ModbusCrc16.h>
#include <stdint.h>

typedef enum AsyncModbusServant_Endian
{
	AsyncModbusServant_Endian_BigEndian,
	AsyncModbusServant_Endian_LittleEndian,
} AsyncModbusServant_Endian;

typedef struct AsyncModbusServant
{
	AsyncModbusServant_Endian _local_endian;
	AsyncModbusServant_Endian _remote_endian;

	/// @brief crc16 的计算结果要用什么字节序存放
	AsyncModbusServant_Endian _crc16_endian;

	/// @brief 从流中接收 modbus 请求帧，将响应帧写入流中。用户需要提供一个流。
	AsyncStream *_stream;

	/// @brief 用户需要提供一个接收缓冲区，大小自己定。
	uint8_t *_receive_buffer;

	/// @brief 本从机的站号
	uint8_t _servant_addresss;

	/// @brief 用户需要提供一个 ModbusCrc16 实例。
	ModbusCrc16 *_crc;

#pragma region 回调
	/// @brief crc 计算结果与接收到的 crc 不匹配。
	void (*OnCrcError)();

	/// @brief 接收完成，没有发生错误时的回调
	void (*OnReceiveCompeleted)(uint8_t *buffer, int32_t count);
#pragma endregion
} AsyncModbusServant;
