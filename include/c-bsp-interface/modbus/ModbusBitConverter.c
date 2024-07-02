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

	// 以整体为转换单位
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == BigEndian)
		{
			return value;
		}

		ReverseByteArray((uint8_t *)(&value), 4);
		return value;
	}

	// 以记录为转换单位
	// 逐 2 字节翻转
	ReverseByteArrayPerElement((uint8_t *)(&value), 2, 2);
	if (LocalHostEndian() == LittleEndian)
	{
		return value;
	}

	// 如果本机是大端序，还要整体翻转一次
	ReverseByteArray((uint8_t *)(&value), 4);
	return value;
}

#pragma endregion
