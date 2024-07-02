#include "ModbusBitConverter.h"
#include <c-bsp-interface/Endian.h>
#include <c-bsp-interface/Reverse.h>

#pragma region 转数字
uint16_t ModbusBitConverter_ToUInt16(ModbusBitConverterUnit unit,
									 uint8_t const *buffer, int32_t offset)
{
	uint16_t const *p = (uint16_t const *)(buffer + offset);
	uint16_t value = *p;
	if (LocalHostEndian() == LittleEndian)
	{
		ReverseByteArray((uint8_t *)(&value), 2);
	}

	return value;
}

int16_t ModbusBitConverter_ToInt16(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset)
{
	int16_t const *p = (int16_t const *)(buffer + offset);
	int16_t value = *p;
	if (LocalHostEndian() == LittleEndian)
	{
		ReverseByteArray((uint8_t *)(&value), 2);
	}

	return value;
}

uint32_t ModbusBitConverter_ToUInt32(ModbusBitConverterUnit unit,
									 uint8_t const *buffer, int32_t offset)
{
	uint32_t const *p = (uint32_t const *)(buffer + offset);
	uint32_t value = *p;
	if (LocalHostEndian() == LittleEndian)
	{
		if (unit == ModbusBitConverterUnit_Whole)
		{
			ReverseByteArray((uint8_t *)(&value), 4);
			return value;
		}

		// 以记录为单位翻转
		ReverseByteArray((uint8_t *)(&value), 2);
		ReverseByteArray((uint8_t *)(&value + 2), 2);
		return value;
	}

	// 大端序
	if (unit == ModbusBitConverterUnit_Whole)
	{
		// 以整体为转换单位，因为接收就是大端序，所以不用翻转
		return value;
	}

	// 以记录为单位翻转

	// 先逐 2 字节翻转
	for (int i = 0; i < sizeof(uint32_t); i += 2)
	{
		ReverseByteArray((uint8_t *)(&value + i), 2);
	}

	// 最后整体翻转
	ReverseByteArray((uint8_t *)(&value), 4);
	return value;
}

#pragma endregion
