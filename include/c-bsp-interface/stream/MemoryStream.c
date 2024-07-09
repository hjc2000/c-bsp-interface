#include "MemoryStream.h"
#include <c-bsp-interface/memory/StackHeap.h>

typedef struct MemoryStream
{
	uint8_t *_buffer;
	int32_t _buffer_size;

	/// @brief 指向当前要读或写的位置。Read 和 Write 会操作的第一个字节就是 _position 指向的字节。
	int32_t _position;

	/// @brief 流的长度。
	/// @note 流的长度可以小于缓冲区长度。此标志用来表示流的长度，也是缓冲区中有效数据的长度。
	/// @note 缓冲区中，第 _length 字节是无效的数据。
	/// 	@li 当 _length = 0 时，_buffer[0] 是无效数据，流中没有数据。
	/// 	@li _length 不为 0 时，[0 , _length - 1] 闭区间上是有效数据。
	int32_t _length;

#pragma region Stream
	uint8_t (*CanRead)();
	uint8_t (*CanWrite)();
	uint8_t (*CanSeek)();

	int64_t (*Length)();
	void (*SetLength)(int64_t value);

	/// @brief 从流中读取数据写入 buffer。
	/// @param buffer 要将读取到的数据写入的缓冲区。
	/// @param offset 将读取到的数据写入 dst_buf 时的起始位置。
	/// @param count 要读取的字节数。
	///
	/// @return 实际读取的字节数。如果返回 0，说明此流结束。
	/// 返回负数说明发生错误。
	int32_t (*Read)(uint8_t *buffer, int32_t offset, int32_t count);

	/// @brief 将 buffer 中的数据写入流中。
	/// @param buffer
	/// @param offset
	/// @param count
	/// @return 成功返回 0，失败返回负数的错误代码。
	int32_t (*Write)(uint8_t const *buffer, int32_t offset, int32_t count);

	/// @brief 冲洗流
	/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
	/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
	void (*Flush)();

	/// @brief 关闭流。
	/// @note 关闭后对流的操作将会引发异常。
	void (*Close)();

	int64_t (*Position)();
	void (*SetPosition)(int64_t value);
#pragma endregion
} MemoryStream;

MemoryStream *MemoryStream_StackHeapAlloc(int32_t max_size)
{
	MemoryStream *o = StackHeapAlignAlloc(sizeof(MemoryStream), 4);
	o->_buffer = StackHeapAlloc(max_size);
	o->_buffer_size = max_size;
	o->_position = 0;
	o->_length = 0;
	return o;
}

void MemoryStream_AsStream(MemoryStream *o, Stream *stream)
{
	stream->CanRead = o->CanRead;
	stream->CanWrite = o->CanWrite;
	stream->CanSeek = o->CanSeek;
	stream->Length = o->Length;
	stream->SetLength = o->SetLength;
	stream->Read = o->Read;
	stream->Write = o->Write;
	stream->Flush = o->Flush;
	stream->Close = o->Close;
	stream->Position = o->Position;
	stream->SetPosition = o->SetPosition;
}
