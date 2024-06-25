#include "AutoBitConverter.h"
#include <c-bsp-interface/BitConverter.h>
#include <c-bsp-interface/Reverse.h>

static uint8_t AutoBitConverter_ShouldReverse(AutoBitConverter *this)
{
	return LocalHostEndian() != this->_remote_endian;
}

#pragma region 转为数字
uint16_t AutoBitConverter_ToUInt16(AutoBitConverter *this, uint8_t const *buffer, int32_t offset)
{
	uint16_t ret = BitConverter_ByteArrayToUInt16(buffer, offset);
	if (AutoBitConverter_ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

int16_t AutoBitConverter_ToInt16(AutoBitConverter *this, uint8_t const *buffer, int32_t offset)
{
	int16_t ret = BitConverter_ByteArrayToInt16(buffer, offset);
	if (AutoBitConverter_ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

uint32_t AutoBitConverter_ToUInt32(AutoBitConverter *this, uint8_t const *buffer, int32_t offset)
{
	uint32_t ret = BitConverter_ByteArrayToUInt32(buffer, offset);
	if (AutoBitConverter_ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

int32_t AutoBitConverter_ToInt32(AutoBitConverter *this, uint8_t const *buffer, int32_t offset)
{
	int32_t ret = BitConverter_ByteArrayToInt32(buffer, offset);
	if (AutoBitConverter_ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

uint64_t AutoBitConverter_ToUInt64(AutoBitConverter *this, uint8_t const *buffer, int32_t offset)
{
	uint64_t ret = BitConverter_ByteArrayToUInt64(buffer, offset);
	if (AutoBitConverter_ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

int64_t AutoBitConverter_ToInt64(AutoBitConverter *this, uint8_t const *buffer, int32_t offset)
{
	int64_t ret = BitConverter_ByteArrayToInt64(buffer, offset);
	if (AutoBitConverter_ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

float AutoBitConverter_ToFloat(AutoBitConverter *this, uint8_t const *buffer, int32_t offset)
{
	float ret = BitConverter_ByteArrayToFloat(buffer, offset);
	if (AutoBitConverter_ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

double AutoBitConverter_ToDouble(AutoBitConverter *this, uint8_t const *buffer, int32_t offset)
{
	double ret = BitConverter_ByteArrayToDouble(buffer, offset);
	if (AutoBitConverter_ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}
#pragma endregion
