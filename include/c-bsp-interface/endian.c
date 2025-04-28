#include "endian.h"
#include <stdint.h>

bsp__endian bsp__local_host_endian()
{
	int32_t a = 1;
	int8_t *p = (int8_t *)(&a);
	if (*p)
	{
		return bsp__endian__little_endian;
	}

	return bsp__endian__big_endian;
}
