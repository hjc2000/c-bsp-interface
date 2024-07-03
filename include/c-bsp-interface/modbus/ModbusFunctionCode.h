#pragma once

/// @brief 功能码枚举。
typedef enum ModbusFunctionCode
{
	/// @brief 读取一组线圈
	ModbusFunctionCode_ReadCoils = 0x01,

	/// @brief 读取一组输入位
	ModbusFunctionCode_ReadInputBits = 0x02,

	/// @brief 读取一组保持寄存器
	ModbusFunctionCode_ReadHoldingRegisters = 0x03,

	/// @brief 读取一组输入寄存器
	ModbusFunctionCode_ReadInputRegisters = 0x04,

	/// @brief 写单个线圈
	ModbusFunctionCode_WriteSingleCoil = 0x05,

	/// @brief 写入一组线圈
	ModbusFunctionCode_WriteCoils = 0x0f,

	/// @brief 写入多个保持寄存器
	ModbusFunctionCode_WriteHoldingRegisters = 0x10,

	/// @brief 诊断
	ModbusFunctionCode_Diagnosis = 0x08,
} ModbusFunctionCode;
