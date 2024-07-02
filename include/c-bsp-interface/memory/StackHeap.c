#include "StackHeap.h"

static uint8_t _buffer[STACK_HEAP_SIZE];
static uint32_t _sp = 0;
static uint8_t _overflow = 0;
static void (*_overflow_handler)() = 0;

static void AlignSp(int32_t align)
{
	if (align < 0)
	{
		return;
	}

	uint32_t current_addr = (uint32_t)_buffer + _sp;

	// 当前地址比上一个对齐的地址多出了多少个字节
	uint32_t mod = current_addr % align;

	// 当前地址离下一个对其的地址还差 align - mod
	_sp += align - mod;
}

void *StackHeapAlloc(int32_t size)
{
	if (size < 0)
	{
		return 0;
	}

	if (_sp + size <= STACK_HEAP_SIZE)
	{
		void *ret = _buffer + _sp;
		_sp += size;
		return ret;
	}

	_overflow = 1;
	if (_overflow_handler)
	{
		_overflow_handler();
	}

	return 0;
}

void *StackHeapAlignAlloc(int32_t size, int32_t align)
{
	if (size < 0)
	{
		return 0;
	}

	AlignSp(align);
	return StackHeapAlloc(size);
}

uint8_t StackHeapOverflow()
{
	return _overflow;
}

void SetStackHeapOverflowHandler(void (*func)())
{
	_overflow_handler = func;
}

uint32_t StackHeapSp()
{
	return _sp;
}
