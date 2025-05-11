#include "reverse.h"

void bsp_reverse_byte_array(uint8_t *array, int32_t size)
{
	if (size <= 1)
	{
		return;
	}

	for (int32_t i = 0; i < size / 2; i++)
	{
		// 交换数组中的元素
		uint8_t temp = array[i];
		array[i] = array[size - 1 - i];
		array[size - 1 - i] = temp;
	}
}

void bsp_reverse_byte_array_per_element(uint8_t *array, int32_t element_size, int32_t element_count)
{
	if (element_size <= 1)
	{
		// 每个单元的尺寸小于等于 0 是非法的
		// 每个单元的尺寸等于 1 时翻转没有意义。
		return;
	}

	if (element_count <= 0)
	{
		return;
	}

	for (int32_t i = 0; i < element_count; i++)
	{
		bsp_reverse_byte_array(array + element_size * i, element_size);
	}
}
