#include "AutoBitConverter.h"
#include <c-bsp-interface/Reverse.h>

static uint8_t ShouldReverse(AutoBitConverter *this)
{
	return LocalHostEndian() != this->_remote_endian;
}

uint16_t AutoBitConverter_ToUInt16(AutoBitConverter *this, uint8_t *buffer, int32_t offset)
{
	uint16_t ret = *(uint16_t *)(buffer + offset);
	if (ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

int16_t AutoBitConverter_ToInt16(AutoBitConverter *this, uint8_t *buffer, int32_t offset)
{
	int16_t ret = *(int16_t *)(buffer + offset);
	if (ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 2);
	}

	return ret;
}

uint32_t AutoBitConverter_ToUInt32(AutoBitConverter *this, uint8_t *buffer, int32_t offset)
{
	uint32_t ret = *(uint32_t *)(buffer + offset);
	if (ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

int32_t AutoBitConverter_ToInt32(AutoBitConverter *this, uint8_t *buffer, int32_t offset)
{
	int32_t ret = *(int32_t *)(buffer + offset);
	if (ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

uint64_t AutoBitConverter_ToUInt64(AutoBitConverter *this, uint8_t *buffer, int32_t offset)
{
	uint64_t ret = *(uint64_t *)(buffer + offset);
	if (ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

int64_t AutoBitConverter_ToInt64(AutoBitConverter *this, uint8_t *buffer, int32_t offset)
{
	int64_t ret = *(int64_t *)(buffer + offset);
	if (ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}

float AutoBitConverter_ToFloat(AutoBitConverter *this, uint8_t *buffer, int32_t offset)
{
	float ret = *(float *)(buffer + offset);
	if (ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 4);
	}

	return ret;
}

double AutoBitConverter_ToDouble(AutoBitConverter *this, uint8_t *buffer, int32_t offset)
{
	double ret = *(double *)(buffer + offset);
	if (ShouldReverse(this))
	{
		ReverseByteArray((uint8_t *)(&ret), 8);
	}

	return ret;
}
