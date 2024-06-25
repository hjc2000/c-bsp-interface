#include "Reverse.h"

void ReverseByteArray(uint8_t *array, uint32_t size)
{
	for (uint32_t i = 0; i < size / 2; i++)
	{
		// 交换数组中的元素
		uint8_t temp = array[i];
		array[i] = array[size - 1 - i];
		array[size - 1 - i] = temp;
	}
}
