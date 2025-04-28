#include "bsp_endian_t.h"
#include <stdint.h>

bsp_endian_t LocalHostEndian()
{
	int32_t a = 1;
	int8_t *p = (int8_t *)(&a);
	if (*p)
	{
		return LittleEndian;
	}

	return BigEndian;
}
