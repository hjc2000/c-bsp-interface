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
	Stack *o = StackHeapAlignAlloc(sizeof(Stack), 4);
	o->_buffer = StackHeapAlloc(max_size);
	o->_max_size = max_size;
	o->_sp = 0;
	return 0;
}

void Stack_Clear(Stack *o)
{
	o->_sp = 0;
}

uint8_t Stack_Push(Stack *o, void *data, int32_t size)
{
	if (o->_sp + size > o->_max_size)
	{
		return 0;
	}

	memcpy(o->_buffer + o->_sp, data, size);
	o->_sp += size;
	return 1;
}

uint8_t Stack_Pop(Stack *o, void *out, int32_t size)
{
	if (o->_sp - size < 0)
	{
		return 0;
	}

	o->_sp -= size;
	memcpy(out, o->_buffer + o->_sp, size);
	return 1;
}

uint8_t *Stack_Buffer(Stack *o)
{
	return o->_buffer;
}

int32_t Stack_MaxSize(Stack *o)
{
	return o->_max_size;
}

int32_t Stack_Sp(Stack *o)
{
	return o->_sp;
}
