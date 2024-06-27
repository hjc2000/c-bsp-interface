#pragma once

/// @brief 功能码枚举。
typedef enum FunctionCode
{
	/// @brief 读取一组线圈
	ReadCoils = 0x01,

	/// @brief 读取一组输入位
	ReadInputBits = 0x02,

	/// @brief 读取一组保持寄存器
	ReadHoldingRegisters = 0x03,

	/// @brief 读取一组输入寄存器
	ReadInputRegisters = 0x04,

	/// @brief 写单个线圈
	WriteSingleCoil = 0x05,

	/// @brief 写入一组线圈
	WriteCoils = 0x0f,

	/// @brief 写入多个保持寄存器
	WriteHoldingRegisters = 0x10,

	/// @brief 诊断
	Diagnosis = 0x08,
} FunctionCode;
