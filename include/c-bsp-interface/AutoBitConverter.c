#include "AutoBitConverter.h"
#include <c-bsp-interface/BitConverter.h>
#include <c-bsp-interface/Reverse.h>
#include <c-bsp-interface/memory/StackHeap.h>

typedef struct AutoBitConverter
{
	Endian _remote_endian;
} AutoBitConverter;

AutoBitConverter *AutoBitConverter_StackHeapAlloc(Endian remote_endian)
{
	AutoBitConverter *o = StackHeapObjAlloc(sizeof(AutoBitConverter));
	o->_remote_endian = remote_endian;
	return o;
}

static uint8_t AutoBitConverter_ShouldReverse(AutoBitConverter *o)
{
	return LocalHostEndian() != o->_remote_endian;
}

#pragma region 转数字
uint16_t AutoBitConverter_ToUInt16(AutoBitConverter *o, uint8_t const *buffer, int32_t offset)
{
	uint16_t ret = BitConverter_ByteArrayToUInt16(buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

int16_t AutoBitConverter_ToInt16(AutoBitConverter *o, uint8_t const *buffer, int32_t offset)
{
	int16_t ret = BitConverter_ByteArrayToInt16(buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

uint32_t AutoBitConverter_ToUInt32(AutoBitConverter *o, uint8_t const *buffer, int32_t offset)
{
	uint32_t ret = BitConverter_ByteArrayToUInt32(buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

int32_t AutoBitConverter_ToInt32(AutoBitConverter *o, uint8_t const *buffer, int32_t offset)
{
	int32_t ret = BitConverter_ByteArrayToInt32(buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

uint64_t AutoBitConverter_ToUInt64(AutoBitConverter *o, uint8_t const *buffer, int32_t offset)
{
	uint64_t ret = BitConverter_ByteArrayToUInt64(buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

int64_t AutoBitConverter_ToInt64(AutoBitConverter *o, uint8_t const *buffer, int32_t offset)
{
	int64_t ret = BitConverter_ByteArrayToInt64(buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

float AutoBitConverter_ToFloat(AutoBitConverter *o, uint8_t const *buffer, int32_t offset)
{
	float ret = BitConverter_ByteArrayToFloat(buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

double AutoBitConverter_ToDouble(AutoBitConverter *o, uint8_t const *buffer, int32_t offset)
{
	double ret = BitConverter_ByteArrayToDouble(buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}
#pragma endregion

#pragma region 转字节数组
void AutoBitConverter_GetBytesFromUInt16(AutoBitConverter *o,
										 uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray(out_buffer + offset, 2);
	}
}

void AutoBitConverter_GetBytesFromInt16(AutoBitConverter *o,
										int16_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray(out_buffer + offset, 2);
	}
}

void AutoBitConverter_GetBytesFromUInt32(AutoBitConverter *o,
										 uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

void AutoBitConverter_GetBytesFromInt32(AutoBitConverter *o,
										int32_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

void AutoBitConverter_GetBytesFromUInt64(AutoBitConverter *o,
										 uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}

void AutoBitConverter_GetBytesFromInt64(AutoBitConverter *o,
										int64_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}

void AutoBitConverter_GetBytesFromFloat(AutoBitConverter *o,
										float value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray(out_buffer + offset, 4);
	}
}

void AutoBitConverter_GetBytesFromDouble(AutoBitConverter *o,
										 double value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter_GetBytesFromUInt16(value, out_buffer, offset);
	if (AutoBitConverter_ShouldReverse(o))
	{
		ReverseByteArray(out_buffer + offset, 8);
	}
}
#pragma endregion
