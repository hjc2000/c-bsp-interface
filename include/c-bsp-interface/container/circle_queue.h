#pragma once
#include <stddef.h>

#ifndef __element_type
	#define __element_type int
#endif

typedef struct bsp_circle_queue
{
	///
	/// @brief 元素个数。
	///
	///
	size_t _count;
	size_t _head;
	size_t _tail;
	__element_type _array[];

} bsp_circle_queue;

#undef __element_type
