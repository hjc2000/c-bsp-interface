#include "Stack.h"
#include <c-bsp-interface/memory/StackHeap.h>
#include <string.h>

typedef struct Stack
{
	uint8_t *_buffer;
	int32_t _max_size;
	int32_t _sp;
} Stack;

Stack *Stack_StackHeapAlloc(int32_t max_size)
{
	Stack *this = StackHeapAlignAlloc(sizeof(Stack), 4);
	this->_buffer = StackHeapAlloc(max_size);
	this->_max_size = max_size;
	this->_sp = 0;
	return 0;
}

void Stack_Clear(Stack *this)
{
	this->_sp = 0;
}

uint8_t Stack_Push(Stack *this, void *data, int32_t size)
{
	if (this->_sp + size > this->_max_size)
	{
		return 0;
	}

	memcpy(this->_buffer + this->_sp, data, size);
	this->_sp += size;
	return 1;
}

uint8_t Stack_Pop(Stack *this, void *out, int32_t size)
{
	if (this->_sp - size < 0)
	{
		return 0;
	}

	this->_sp -= size;
	memcpy(out, this->_buffer + this->_sp, size);
	return 1;
}

uint8_t *Stack_Buffer(Stack *this)
{
	return this->_buffer;
}

int32_t Stack_MaxSize(Stack *this)
{
	return this->_max_size;
}

int32_t Stack_Sp(Stack *this)
{
	return this->_sp;
}
