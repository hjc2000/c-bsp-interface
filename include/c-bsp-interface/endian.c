#include "endian.h"
#include <stdint.h>

bsp_endian bsp_local_host_endian()
{
	uint32_t a = 1;
	uint8_t *p = (uint8_t *)(&a);
	if (p[0])
	{
		return bsp_endian_little_endian;
	}

	return bsp_endian_big_endian;
}
