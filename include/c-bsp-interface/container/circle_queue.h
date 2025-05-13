#pragma once
#include "c-bsp-interface/type.h"
#include <stddef.h>

#ifndef __element_type
	#define __element_type int
#endif

typedef struct bsp_circle_queue
{
	///
	/// @brief 总大小。
	///
	/// @note 预先分配一个字节数组，将数组头指针强制转换为本结构体的指针，然后初始化，
	/// 相当于 C++ 的 placement new. 本字段用来记录这个字节数组的总大小。
	///
	///
	size_t _total_size;

	///
	/// @brief 元素个数。
	///
	///
	size_t _count;

	size_t _head;
	size_t _tail;
	bsp_bool _is_full;

	__element_type _array[];

} bsp_circle_queue;

#undef __element_type
