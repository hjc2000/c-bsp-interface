#include "ModbusBitConverter.h"
#include <c-bsp-interface/bsp__endian_enum.h>
#include <c-bsp-interface/Reverse.h>
#include <string.h>

#pragma region 转数字

uint8_t ModbusBitConverter_ToUInt8(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset)
{
	uint8_t const *p = (uint8_t const *)(buffer + offset);
	uint8_t value = *p;
	return value;
}

uint8_t ModbusBitConverter_ToInt8(ModbusBitConverterUnit unit,
								  uint8_t const *buffer, int32_t offset)
{
	return ModbusBitConverter_ToUInt8(unit, buffer, offset);
}

uint16_t ModbusBitConverter_ToUInt16(ModbusBitConverterUnit unit,
									 uint8_t const *buffer, int32_t offset)
{
	uint16_t const *p = (uint16_t const *)(buffer + offset);
	uint16_t value = *p;
	if (LocalHostEndian() == bsp__endian_enum__little_endian)
	{
		ReverseByteArray((uint8_t *)(&value), 2);
	}

	return value;
}

int16_t ModbusBitConverter_ToInt16(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset)
{
	return ModbusBitConverter_ToUInt16(unit, buffer, offset);
}

uint32_t ModbusBitConverter_ToUInt32(ModbusBitConverterUnit unit,
									 uint8_t const *buffer, int32_t offset)
{
	uint32_t const *p = (uint32_t const *)(buffer + offset);
	uint32_t value = *p;

	// 以整体为转换单位
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == bsp__endian_enum__big_endian)
		{
			return value;
		}

		ReverseByteArray((uint8_t *)(&value), 4);
		return value;
	}

	// 以记录为转换单位
	// 逐 2 字节翻转
	ReverseByteArrayPerElement((uint8_t *)(&value), 2, 2);
	if (LocalHostEndian() == bsp__endian_enum__little_endian)
	{
		return value;
	}

	// 如果本机是大端序，还要整体翻转一次
	ReverseByteArray((uint8_t *)(&value), 4);
	return value;
}

int32_t ModbusBitConverter_ToInt32(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset)
{
	return ModbusBitConverter_ToUInt32(unit, buffer, offset);
}

uint64_t ModbusBitConverter_ToUInt64(ModbusBitConverterUnit unit,
									 uint8_t const *buffer, int32_t offset)
{
	uint64_t const *p = (uint64_t const *)(buffer + offset);
	uint64_t value = *p;

	// 以整体为转换单位
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == bsp__endian_enum__big_endian)
		{
			return value;
		}

		ReverseByteArray((uint8_t *)(&value), 8);
		return value;
	}

	// 以记录为转换单位
	// 逐 2 字节翻转
	ReverseByteArrayPerElement((uint8_t *)(&value), 2, 4);
	if (LocalHostEndian() == bsp__endian_enum__little_endian)
	{
		return value;
	}

	// 如果本机是大端序，还要整体翻转一次
	ReverseByteArray((uint8_t *)(&value), 8);
	return value;
}

int64_t ModbusBitConverter_ToInt64(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset)
{
	return ModbusBitConverter_ToUInt64(unit, buffer, offset);
}

float ModbusBitConverter_ToFloat(ModbusBitConverterUnit unit,
								 uint8_t const *buffer, int32_t offset)
{
	float const *p = (float const *)(buffer + offset);
	float value = *p;

	// 以整体为转换单位
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == bsp__endian_enum__big_endian)
		{
			return value;
		}

		ReverseByteArray((uint8_t *)(&value), 4);
		return value;
	}

	// 以记录为转换单位
	// 逐 2 字节翻转
	ReverseByteArrayPerElement((uint8_t *)(&value), 2, 2);
	if (LocalHostEndian() == bsp__endian_enum__little_endian)
	{
		return value;
	}

	// 如果本机是大端序，还要整体翻转一次
	ReverseByteArray((uint8_t *)(&value), 4);
	return value;
}

double ModbusBitConverter_ToDouble(ModbusBitConverterUnit unit,
								   uint8_t const *buffer, int32_t offset)
{
	double const *p = (double const *)(buffer + offset);
	double value = *p;

	// 以整体为转换单位
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == bsp__endian_enum__big_endian)
		{
			return value;
		}

		ReverseByteArray((uint8_t *)(&value), 8);
		return value;
	}

	// 以记录为转换单位
	// 逐 2 字节翻转
	ReverseByteArrayPerElement((uint8_t *)(&value), 2, 4);
	if (LocalHostEndian() == bsp__endian_enum__little_endian)
	{
		return value;
	}

	// 如果本机是大端序，还要整体翻转一次
	ReverseByteArray((uint8_t *)(&value), 8);
	return value;
}

#pragma endregion

#pragma region 转字节数组

void ModbusBitConverter_GetBytesFromUInt8(ModbusBitConverterUnit unit,
										  uint8_t value, uint8_t *out_buffer, int32_t offset)
{
	/* 这里是 uint8_t 所以直接使用赋值。2 个字节以及上的数据类型不能这么做，因为可能会有对齐问题。
	 * 对没有对齐的内存地址的整型操作可能会引发硬件错误
	 */
	*(out_buffer + offset) = value;
}

void ModbusBitConverter_GetBytesFromUInt16(ModbusBitConverterUnit unit,
										   uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *value_buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, value_buffer, 2);
	if (LocalHostEndian() == bsp__endian_enum__little_endian)
	{
		ReverseByteArray(out_buffer + offset, 2);
	}
}

void ModbusBitConverter_GetBytesFromInt16(ModbusBitConverterUnit unit,
										  int16_t value, uint8_t *out_buffer, int32_t offset)
{
	ModbusBitConverter_GetBytesFromUInt16(unit, value, out_buffer, offset);
}

void ModbusBitConverter_GetBytesFromUInt32(ModbusBitConverterUnit unit,
										   uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *value_buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, value_buffer, 4);
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == bsp__endian_enum__little_endian)
		{
			// 本机是小端序，翻转后返回
			ReverseByteArray(out_buffer + offset, 4);
			return;
		}

		// 本机是大端序，不用翻转，直接返回
		return;
	}

	// 逐个记录进行转换
	if (LocalHostEndian() == bsp__endian_enum__big_endian)
	{
		/* 本机是大端序，因为低 16 位要在第 1 个记录，所以先整体翻转，随后再逐个记录再次翻转，
		 * 使每个记录变成大端序
		 */
		ReverseByteArray(out_buffer + offset, 4);
	}

	// 本机是小端序不用先经过整体翻转

	// 逐个记录进行翻转，也就是逐 2 字节进行翻转
	ReverseByteArrayPerElement(out_buffer + offset, 2, 2);
}

void ModbusBitConverter_GetBytesFromInt32(ModbusBitConverterUnit unit,
										  int32_t value, uint8_t *out_buffer, int32_t offset)
{
	ModbusBitConverter_GetBytesFromUInt32(unit, value, out_buffer, offset);
}

void ModbusBitConverter_GetBytesFromUInt64(ModbusBitConverterUnit unit,
										   uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *value_buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, value_buffer, 8);
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == bsp__endian_enum__little_endian)
		{
			// 本机是小端序，翻转后返回
			ReverseByteArray(out_buffer + offset, 8);
			return;
		}

		// 本机是大端序，不用翻转，直接返回
		return;
	}

	// 逐个记录进行转换
	if (LocalHostEndian() == bsp__endian_enum__big_endian)
	{
		/* 本机是大端序，因为低 16 位要在第 1 个记录，所以先整体翻转，随后再逐个记录再次翻转，
		 * 使每个记录变成大端序
		 */
		ReverseByteArray(out_buffer + offset, 8);
	}

	// 本机是小端序不用先经过整体翻转

	// 逐个记录进行翻转，也就是逐 2 字节进行翻转
	ReverseByteArrayPerElement(out_buffer + offset, 2, 4);
}

void ModbusBitConverter_GetBytesFromInt64(ModbusBitConverterUnit unit,
										  int64_t value, uint8_t *out_buffer, int32_t offset)
{
	ModbusBitConverter_GetBytesFromUInt64(unit, value, out_buffer, offset);
}

void ModbusBitConverter_GetBytesFromFloat(ModbusBitConverterUnit unit,
										  float value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *value_buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, value_buffer, 4);
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == bsp__endian_enum__little_endian)
		{
			// 本机是小端序，翻转后返回
			ReverseByteArray(out_buffer + offset, 4);
			return;
		}

		// 本机是大端序，不用翻转，直接返回
		return;
	}

	// 逐个记录进行转换
	if (LocalHostEndian() == bsp__endian_enum__big_endian)
	{
		/* 本机是大端序，因为低 16 位要在第 1 个记录，所以先整体翻转，随后再逐个记录再次翻转，
		 * 使每个记录变成大端序
		 */
		ReverseByteArray(out_buffer + offset, 4);
	}

	// 本机是小端序不用先经过整体翻转

	// 逐个记录进行翻转，也就是逐 2 字节进行翻转
	ReverseByteArrayPerElement(out_buffer + offset, 2, 2);
}

void ModbusBitConverter_GetBytesFromDouble(ModbusBitConverterUnit unit,
										   double value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *value_buffer = (uint8_t *)(&value);
	memcpy(out_buffer + offset, value_buffer, 8);
	if (unit == ModbusBitConverterUnit_Whole)
	{
		if (LocalHostEndian() == bsp__endian_enum__little_endian)
		{
			// 本机是小端序，翻转后返回
			ReverseByteArray(out_buffer + offset, 8);
			return;
		}

		// 本机是大端序，不用翻转，直接返回
		return;
	}

	// 逐个记录进行转换
	if (LocalHostEndian() == bsp__endian_enum__big_endian)
	{
		/* 本机是大端序，因为低 16 位要在第 1 个记录，所以先整体翻转，随后再逐个记录再次翻转，
		 * 使每个记录变成大端序
		 */
		ReverseByteArray(out_buffer + offset, 8);
	}

	// 本机是小端序不用先经过整体翻转

	// 逐个记录进行翻转，也就是逐 2 字节进行翻转
	ReverseByteArrayPerElement(out_buffer + offset, 2, 4);
}

#pragma endregion
