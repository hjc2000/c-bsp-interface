#pragma once
#include <stdint.h>

typedef struct ModbusCrc16
{
	/// @brief CRC16 寄存器。用户不要手动修改
	uint16_t _crc16_register;

	/// @brief 生成数。用户不要手动修改。
	uint16_t _polynomial;
} ModbusCrc16;

/// @brief 初始化。会使用默认的生成多项式。
/// @param
void ModbusCrc16_Init(ModbusCrc16 *this);

/// @brief 添加一个数进行计算。
/// @param
/// @param data
void ModbusCrc16_Add(ModbusCrc16 *this, uint8_t data);

/// @brief 添加一个数组中的数进行计算。会逐字节添加，进行计算。
/// @param
/// @param datas
/// @param count
void ModbusCrc16_AddArray(ModbusCrc16 *this, uint8_t *datas, uint32_t count);
