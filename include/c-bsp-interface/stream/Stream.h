#pragma once
#include <stdint.h>

typedef struct Stream
{
	/// @brief 相当于 this 指针。调用 Stream 的方法需要将此字段传进去。
	void *_self;

	uint8_t (*CanRead)(void *self);
	uint8_t (*CanWrite)(void *self);
	uint8_t (*CanSeek)(void *self);

	int64_t (*Length)(void *self);
	void (*SetLength)(void *self, int64_t value);

	/// @brief 从流中读取数据写入 buffer。
	/// @param self
	/// @param buffer 要将读取到的数据写入的缓冲区。
	/// @param offset 将读取到的数据写入 dst_buf 时的起始位置。
	/// @param count 要读取的字节数。
	/// @return 实际读取的字节数。如果返回 0，说明此流结束。
	int32_t (*Read)(void *self, uint8_t *buffer, int32_t offset, int32_t count);

	/// @brief 将 buffer 中的数据写入流中。
	/// @param self
	/// @param buffer
	/// @param offset
	/// @param count
	void (*Write)(void *self, uint8_t const *buffer, int32_t offset, int32_t count);

	/// @brief 冲洗流
	/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
	/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
	///
	/// @param self
	void (*Flush)(void *self);

	/// @brief 关闭流。
	/// @note 关闭后对流的操作将会引发异常。
	///
	/// @param self
	void (*Close)(void *self);

	/// @brief 当前位置
	/// @param self
	/// @return
	int64_t (*Position)(void *self);
	void (*SetPosition)(void *self, int64_t value);
} Stream;
