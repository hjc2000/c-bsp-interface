#pragma once
#include <c-bsp-interface/stream/Stream.h>

typedef struct MemoryStream MemoryStream;

MemoryStream *MemoryStream_StackHeapAlloc(int32_t max_size);

/// @brief 将本对象变成 Stream
/// @param o
/// @param stream 接收本对象的方法的 Stream 结构体对象。
void MemoryStream_AsStream(MemoryStream *o, Stream *stream);
