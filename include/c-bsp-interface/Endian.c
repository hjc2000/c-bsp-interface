#include "Endian.h"
#include <stdint.h>

Endian LocalHostEndian()
{
	int32_t a = 1;
	int8_t *p = (int8_t *)(&a);
	if (*p)
	{
		return LittleEndian;
	}

	return BigEndian;
}