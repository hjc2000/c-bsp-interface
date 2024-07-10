#pragma once
#include <c-bsp-interface/Endian.h>
#include <stdint.h>

typedef struct ModbusCrc16 ModbusCrc16;

/// @brief 在栈堆上构造 ModbusCrc16 对象
/// @return 构造出的对象的指针。
ModbusCrc16 *ModbusCrc16_StackHeapAlloc();

/// @brief 开始新的一轮校验时需要重置 CRC16 寄存器，否则添加计算的字节会与上一轮校验的字节
/// 叠加在一起。
/// @param
void ModbusCrc16_ResetRegister(ModbusCrc16 *o);

/// @brief 添加一个数进行计算。
/// @param o
/// @param data
void ModbusCrc16_Add(ModbusCrc16 *o, uint8_t data);

/// @brief 添加一个数组中的数进行计算。会逐字节添加，进行计算。
/// @param o
/// @param datas
/// @param count
void ModbusCrc16_AddArray(ModbusCrc16 *o, uint8_t *datas, uint32_t count);

/// @brief 获取 CRC16 寄存器的值
/// @param o
/// @return
uint16_t ModbusCrc16_Register(ModbusCrc16 *o);

/// @brief 获取 CRC16 寄存器的高字节
/// @param o
/// @return
uint8_t ModbusCrc16_HighByte(ModbusCrc16 *o);

/// @brief 获取 CRC16 寄存器的低字节
/// @param o
/// @return
uint8_t ModbusCrc16_LowByte(ModbusCrc16 *o);

/// @brief 将本对象的 CRC16 寄存器与另一个 CRC16 寄存器对比，看是否相等。
/// @param o
/// @param crc16_register_buffer CRC16 寄存器的 2 个字节被存放在此缓冲区中。
///
/// @param crc16_register_buffer_endian crc16_register_buffer
/// 中的 CRC16 寄存器的 2 个字节是以什么字节序存放的。
///
/// @return 相等返回 true，不相等返回 false。
uint8_t ModbusCrc16_CompareRegister(ModbusCrc16 *o,
									uint8_t *crc16_register_buffer,
									Endian crc16_register_buffer_endian);

typedef struct Stream Stream;

/// @brief 将 CRC16 寄存器写入流。
/// @param self
/// @param endian 写入流时使用的字节序。
void ModbusCrc16_WriteRegisterToStream(ModbusCrc16 *self, Stream *stream, Endian endian);
