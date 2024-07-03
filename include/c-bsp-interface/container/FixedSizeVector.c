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
	FixedSizeVector *this = StackHeapAlignAlloc(sizeof(FixedSizeVector), 4);
	this->_max_size = max_element_count * element_size;
	this->_buffer = StackHeapAlloc(this->_max_size);
	this->_pos = 0;
	this->_element_size = element_size;
	return this;
}

uint8_t *FixedSizeVector_Buffer(FixedSizeVector *this)
{
	return this->_buffer;
}

int32_t FixedSizeVector_Size(FixedSizeVector *this)
{
	return this->_pos;
}

void FixedSizeVector_Clear(FixedSizeVector *this)
{
	this->_pos = 0;
}

uint8_t FixedSizeVector_PushBack(FixedSizeVector *this, void *element)
{
	if ((this->_pos + this->_element_size) > this->_max_size)
	{
		return 0;
	}

	memcpy(this->_buffer + this->_pos, element, this->_element_size);
	this->_pos += this->_element_size;
	return 1;
}
