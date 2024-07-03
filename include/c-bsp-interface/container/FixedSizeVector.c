#include "FixedSizeVector.h"
#include <c-bsp-interface/memory/StackHeap.h>
#include <string.h>

typedef struct FixedSizeVector
{
	int32_t _max_size;
	uint8_t *_buffer;
	int32_t _pos;
	int32_t _element_size;
} FixedSizeVector;

FixedSizeVector *FixedSizeVector_StackHeapAlloc(int32_t element_size, int32_t max_element_count)
{
	FixedSizeVector *o = StackHeapAlignAlloc(sizeof(FixedSizeVector), 4);
	o->_max_size = max_element_count * element_size;
	o->_buffer = StackHeapAlloc(o->_max_size);
	o->_pos = 0;
	o->_element_size = element_size;
	return o;
}

uint8_t *FixedSizeVector_Buffer(FixedSizeVector *o)
{
	return o->_buffer;
}

int32_t FixedSizeVector_Size(FixedSizeVector *o)
{
	return o->_pos;
}

void FixedSizeVector_Clear(FixedSizeVector *o)
{
	o->_pos = 0;
}

uint8_t FixedSizeVector_PushBack(FixedSizeVector *o, void *element)
{
	if ((o->_pos + o->_element_size) > o->_max_size)
	{
		return 0;
	}

	memcpy(o->_buffer + o->_pos, element, o->_element_size);
	o->_pos += o->_element_size;
	return 1;
}
