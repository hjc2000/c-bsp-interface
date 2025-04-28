#include "bsp_auto_bit_converter_t.h"
#include <c-bsp-interface/BitConverter.h>
#include <c-bsp-interface/memory/StackHeap.h>
#include <c-bsp-interface/Reverse.h>

// #region 转字节数组

void AutoBitConverter_GetBytesFromUInt64(bsp_auto_bit_converter_t *self,
										 uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}

void AutoBitConverter_GetBytesFromInt64(bsp_auto_bit_converter_t *self,
										int64_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}

void AutoBitConverter_GetBytesFromFloat(bsp_auto_bit_converter_t *self,
										float value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

void AutoBitConverter_GetBytesFromDouble(bsp_auto_bit_converter_t *self,
										 double value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}

// #endregion
