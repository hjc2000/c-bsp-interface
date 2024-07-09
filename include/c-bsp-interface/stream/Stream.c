#include "Stream.h"

int32_t Stream_ReadAtLeast(Stream *o, uint8_t *buffer, int32_t offset, int32_t minimum_bytes)
{
	return Stream_ReadExactly(o, buffer, offset, minimum_bytes);
}

int32_t Stream_ReadExactly(Stream *o, uint8_t *buffer, int32_t offset, int32_t count)
{
	int64_t total_read = 0;
	while (1)
	{
		int64_t remain_count = count - total_read;
		if (remain_count <= 0)
		{
			// 读取完成，返回
			return total_read;
		}

		int64_t have_read = o->Read(buffer, offset + total_read, remain_count);
		if (have_read == 0)
		{
			// 到达流结尾了，读到多少就多少，直接返回
			return total_read;
		}

		total_read += have_read;
	}
}

void Stream_CopyTo(Stream *o,
				   Stream *dst_stream,
				   volatile uint8_t const *cancellation_flag)
{
	uint8_t temp_buf[128];

	while (1)
	{
		if (*cancellation_flag)
		{
			return;
		}

		int32_t have_read = o->Read(temp_buf, 0, sizeof(temp_buf));
		if (have_read == 0)
		{
			return;
		}

		dst_stream->Write(temp_buf, 0, have_read);
	}
}
