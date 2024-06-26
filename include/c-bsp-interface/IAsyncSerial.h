#pragma once
#include <stdint.h>

/// @brief 校验方式
typedef enum Serial_ParityOption
{
	/// @brief 无校验
	Serial_ParityOption_None,

	/// @brief 偶校验
	Serial_ParityOption_Even,

	/// @brief 奇校验
	Serial_ParityOption_Odd,
} Serial_ParityOption;

/// @brief 停止位占的波特数
typedef enum Serial_StopBitsOption
{
	/// @brief 0.5
	Serial_StopBitsOption_ZeroPointFive,

	/// @brief 1
	Serial_StopBitsOption_One,

	/// @brief 1.5
	Serial_StopBitsOption_OnePointFive,

	/// @brief 2
	Serial_StopBitsOption_Two,
} Serial_StopBitsOption;

/// @brief 硬件流控。
typedef enum Serial_HardwareFlowControlOption
{
	Serial_HardwareFlowControlOption_None,
	Serial_HardwareFlowControlOption_RTS,
	Serial_HardwareFlowControlOption_CTS,
	Serial_HardwareFlowControlOption_RTS_CTS,
} Serial_HardwareFlowControlOption;

/// @brief 异步读写串口接口。
/// @note 本结构体继承 @ref AsyncStream。
typedef struct IAsyncSerial
{
#pragma region 属性
	/// @brief 波特率。
	uint32_t (*BaudRate)();
	void (*SetBaudRate)(uint32_t value);

	/// @brief 数据位的个数。
	uint8_t (*DataBits)();
	void (*SetDataBits)(uint8_t value);

	/// @brief 校验位。
	Serial_ParityOption (*Parity)();
	void (*SetParity)(Serial_ParityOption value);

	/// @brief 停止位个数
	Serial_StopBitsOption (*StopBits)();
	void (*SetStopBits)(Serial_StopBitsOption value);

	/// @brief 硬件流控。
	Serial_HardwareFlowControlOption (*HardwareFlowControl)();
	void (*SetHardwareFlowControl)(Serial_HardwareFlowControlOption value);
#pragma endregion

	/// @brief 打开串口。成功返回 0，失败返回负数的错误代码
	int32_t (*Open)();

#pragma region AsyncStream
	/// @brief 异步读取。此函数不会阻塞，会立刻返回。
	/// @return 成功返回 0，失败返回负数的错误代码。
	/// @note 错误代码：
	/// 	@li -1：函数参数非法
	int32_t (*ReadAsync)(uint8_t *buffer, int32_t offset, int32_t count);

	/// @brief ReadAsync 读取完成后触发此回调。
	///
	/// @param buffer
	/// @param offset
	///
	/// @param have_read 读取了多少字节。可能小于调用 ReadAsync 时传入的 count。
	/// @note 如果一定要那么多字节的数据，调用者自行再次调用 ReadAsync。
	void (*ReadCompleteCallback)(uint8_t *buffer, int32_t offset, int32_t have_read);

	/// @brief 异步写。此函数不会阻塞，会立刻返回。
	/// @return 成功返回 0，失败返回负数的错误代码。
	int32_t (*WriteAsync)(uint8_t const *buffer, int32_t offset, int32_t count);

	/// @brief 调用 WriteAsync 后，写完成会触发此回调。
	void (*WriteCompleteCallback)();
#pragma endregion
} IAsyncSerial;
