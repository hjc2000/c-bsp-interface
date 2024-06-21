#pragma once
#include <stdint.h>

typedef struct IKey
{
	uint8_t (*KeyIsDown)();
} IKey;
