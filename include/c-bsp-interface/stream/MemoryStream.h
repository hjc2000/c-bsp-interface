#pragma once
#include <c-bsp-interface/stream/Stream.h>

typedef struct MemoryStream MemoryStream;

/// @brief 在栈堆上构造 MemoryStream
/// @param buffer_size 缓冲区大小。决定了 MemoryStream 最多能储存的字节数。
/// @return
MemoryStream *MemoryStream_StackHeapAlloc(int32_t buffer_size);

/// @brief 将 MemoryStream 作为 Stream
/// @param self
/// @return Stream 接口。
Stream MemoryStream_AsStream(MemoryStream *self);

/// @brief 获取本流的缓冲区
/// @return
uint8_t *MemoryStream_Buffer(MemoryStream *self);

/// @brief 获取内部缓冲区大小。这就是本流能够储存的最大的字节数。
/// @return
int32_t MemoryStream_BufferSize(MemoryStream *self);

/// @brief 从当前 Position 到 Length，总共有多少个可读字节。
/// @return
int32_t MemoryStream_AvaliableToRead(MemoryStream *self);

/// @brief 从当前的 Position 开始，缓冲区中剩余的可写入空间。
/// @return
int32_t MemoryStream_AvaliableToWrite(MemoryStream *self);

uint8_t MemoryStream_CanRead(MemoryStream *self);
uint8_t MemoryStream_CanWrite(MemoryStream *self);
uint8_t MemoryStream_CanSeek(MemoryStream *self);

/// @brief 本流的长度。
/// @note 写入多少字节，长度就是多少。长度不是指缓冲区的大小。
/// @return
int64_t MemoryStream_Length(MemoryStream *self);

/// @brief 设置本流的长度。
/// @note 一般是用来减小长度以丢弃末尾的数据。如果是增大长度，会导致流的末尾出现一些
/// 垃圾数据。
///
/// @param value 要设置成的长度。
/// @exception value 大于 max_size 会抛出 std::invalid_argument。
void MemoryStream_SetLength(MemoryStream *self, int64_t value);

/// @brief
/// @param buffer
/// @param offset
/// @param count
/// @return
/// @exception buffer 为空指针会抛出 std::invalid_argument 异常。
int32_t MemoryStream_Read(MemoryStream *self,
						  uint8_t *buffer, int32_t offset, int32_t count);

/// @brief
/// @param buffer
/// @param offset
/// @param count
/// @return 成功返回 0，失败返回负数的错误代码。
/// @exception std::invalid_argument
int32_t MemoryStream_Write(MemoryStream *self,
						   uint8_t const *buffer, int32_t offset, int32_t count);

void MemoryStream_Flush(MemoryStream *self);

/// @brief 没有任何作用。
void MemoryStream_Close(MemoryStream *self);

/// @brief 清空流，将 长度和位置都恢复为 0.
void MemoryStream_Clear(MemoryStream *self);

int64_t MemoryStream_Position(MemoryStream *self);
void MemoryStream_SetPosition(MemoryStream *self, int64_t value);
