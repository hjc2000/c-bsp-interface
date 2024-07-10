#include "MemoryStream.h"
#include <c-bsp-interface/memory/StackHeap.h>
#include <string.h>

typedef struct MemoryStream
{
	int32_t _buffer_size;
	uint8_t *_buffer;

	/// @brief 指向当前要读或写的位置。Read 和 Write 会操作的第一个字节就是 _position 指向的字节。
	int32_t _position;

	/// @brief 流的长度。
	/// @note 流的长度可以小于缓冲区长度。此标志用来表示流的长度，也是缓冲区中有效数据的长度。
	/// @note 缓冲区中，第 _length 字节是无效的数据。
	/// 	@li 当 _length = 0 时，_buffer[0] 是无效数据，流中没有数据。
	/// 	@li _length 不为 0 时，[0 , _length - 1] 闭区间上是有效数据。
	int32_t _length;
} MemoryStream;

MemoryStream *MemoryStream_StackHeapAlloc(int32_t buffer_size)
{
	MemoryStream *self = StackHeapAlignAlloc(sizeof(MemoryStream), 4);
	self->_buffer_size = buffer_size;
	self->_buffer = StackHeapAlloc(buffer_size);
	self->_position = 0;
	self->_length = 0;
	return self;
}

Stream MemoryStream_AsStream(MemoryStream *self)
{
	Stream stream;
	stream._self = self;

	stream.CanRead = (uint8_t(*)(void *self))MemoryStream_CanRead;
	stream.CanWrite = (uint8_t(*)(void *self))MemoryStream_CanWrite;
	stream.CanSeek = (uint8_t(*)(void *self))MemoryStream_CanSeek;

	stream.Length = (int64_t(*)(void *self))MemoryStream_Length;
	stream.SetLength = (void (*)(void *self, int64_t value))MemoryStream_SetLength;

	stream.Position = (int64_t(*)(void *self))MemoryStream_Position;
	stream.SetPosition = (void (*)(void *self, int64_t value))MemoryStream_SetPosition;

	stream.Read = (int32_t(*)(void *self, uint8_t *buffer, int32_t offset, int32_t count))MemoryStream_Read;
	stream.Write = (int32_t(*)(void *self, uint8_t const *buffer, int32_t offset, int32_t count))MemoryStream_Write;

	stream.Close = (void (*)(void *self))MemoryStream_Close;
	stream.Flush = (void (*)(void *self))MemoryStream_Flush;

	return stream;
}

uint8_t *MemoryStream_Buffer(MemoryStream *self)
{
	return self->_buffer;
}

int32_t MemoryStream_BufferSize(MemoryStream *self)
{
	return self->_buffer_size;
}

int32_t MemoryStream_AvaliableToRead(MemoryStream *self)
{
	return self->_length - self->_position;
}

int32_t MemoryStream_AvaliableToWrite(MemoryStream *self)
{
	return self->_buffer_size - self->_position;
}

uint8_t MemoryStream_CanRead(MemoryStream *self)
{
	return 1;
}

uint8_t MemoryStream_CanWrite(MemoryStream *self)
{
	return 1;
}

uint8_t MemoryStream_CanSeek(MemoryStream *self)
{
	return 1;
}

int64_t MemoryStream_Length(MemoryStream *self)
{
	return self->_length;
}

void MemoryStream_SetLength(MemoryStream *self, int64_t value)
{
	if (value > self->_buffer_size)
	{
		return;
	}

	self->_length = value;
	if (self->_position > self->_length)
	{
		self->_position = self->_length;
	}
}

int32_t MemoryStream_Read(MemoryStream *self, uint8_t *buffer, int32_t offset, int32_t count)
{
	if (MemoryStream_AvaliableToRead(self) == 0)
	{
		return 0;
	}

	int32_t have_read;
	if (MemoryStream_AvaliableToRead(self) <= count)
	{
		have_read = MemoryStream_AvaliableToRead(self);
	}
	else
	{
		have_read = count;
	}

	// 从本对象的缓冲区复制到传进来的缓冲区
	memcpy(buffer + offset, self->_buffer + self->_position, have_read);
	return have_read;
}

int32_t MemoryStream_Write(MemoryStream *self,
						   uint8_t const *buffer, int32_t offset, int32_t count)
{
	if (count > MemoryStream_AvaliableToWrite(self))
	{
		return -1;
	}

	// 从传进来的缓冲区复制到本对象的缓冲区
	memcpy(self->_buffer + self->_position, buffer + offset, count);
	self->_position += count;
	if (self->_position > self->_length)
	{
		// 写完后当前位置超过流的长度，则将流的长度设为当前位置，使流的长度增大。
		self->_length = self->_position;
	}

	return 0;
}

void MemoryStream_Flush(MemoryStream *self)
{
}

void MemoryStream_Close(MemoryStream *self)
{
}

void MemoryStream_Clear(MemoryStream *self)
{
	self->_position = 0;
	self->_length = 0;
}

int64_t MemoryStream_Position(MemoryStream *self)
{
	return self->_position;
}

void MemoryStream_SetPosition(MemoryStream *self, int64_t value)
{
	if (self->_position > self->_length)
	{
		return;
	}

	self->_position = value;
}
