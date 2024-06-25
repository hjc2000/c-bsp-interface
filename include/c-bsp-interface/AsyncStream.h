#pragma once
#include <stdint.h>

/// @brief 异步流接口
typedef struct AsyncStream
{
	/// @brief 异步读取。此函数不会阻塞，会立刻返回。
	/// @return 成功返回 0，失败返回负数的错误代码。
	/// @note 错误代码：
	/// 	@li -1：函数参数非法
	int32_t (*ReadAsync)(uint8_t *buffer, int32_t offset, int32_t count);

	/// @brief ReadAsync 读取完成后触发此回调。
	///
	/// @param have_read 读取了多少字节。可能小于调用 ReadAsync 时传入的 count。
	/// @note 如果一定要那么多字节的数据，调用者自行再次调用 ReadAsync。
	void (*ReadCompleteCallback)(int32_t have_read);

	/// @brief 异步写。此函数不会阻塞，会立刻返回。
	/// @return 成功返回 0，失败返回负数的错误代码。
	int32_t (*WriteAsync)(uint8_t const *buffer, int32_t offset, int32_t count);

	/// @brief 调用 WriteAsync 后，写完成会触发此回调。
	void (*WriteCompleteCallback)();
} AsyncStream;
