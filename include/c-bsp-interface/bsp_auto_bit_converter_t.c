#include "bsp_auto_bit_converter_t.h"
#include <c-bsp-interface/BitConverter.h>
#include <c-bsp-interface/memory/StackHeap.h>
#include <c-bsp-interface/Reverse.h>

// #region 转数字

uint32_t AutoBitConverter_ToUInt32(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset)
{
	uint32_t ret = BitConverter_ByteArrayToUInt32(buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

int32_t AutoBitConverter_ToInt32(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset)
{
	int32_t ret = BitConverter_ByteArrayToInt32(buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

uint64_t AutoBitConverter_ToUInt64(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset)
{
	uint64_t ret = BitConverter_ByteArrayToUInt64(buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

int64_t AutoBitConverter_ToInt64(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset)
{
	int64_t ret = BitConverter_ByteArrayToInt64(buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

float AutoBitConverter_ToFloat(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset)
{
	float ret = BitConverter_ByteArrayToFloat(buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

double AutoBitConverter_ToDouble(bsp_auto_bit_converter_t *self, uint8_t const *buffer, int32_t offset)
{
	double ret = BitConverter_ByteArrayToDouble(buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

// #endregion

// #region 转字节数组

void AutoBitConverter_GetBytesFromUInt16(bsp_auto_bit_converter_t *self,
										 uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray(out_buffer + offset, 2);
	}
}

void AutoBitConverter_GetBytesFromInt16(bsp_auto_bit_converter_t *self,
										int16_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray(out_buffer + offset, 2);
	}
}

void AutoBitConverter_GetBytesFromUInt32(bsp_auto_bit_converter_t *self,
										 uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

void AutoBitConverter_GetBytesFromInt32(bsp_auto_bit_converter_t *self,
										int32_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (bsp_auto_bit_converter_t__should_reverse(self))
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

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
