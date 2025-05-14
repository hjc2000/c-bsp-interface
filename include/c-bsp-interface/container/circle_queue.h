#pragma once
// 在翻译单元中定义 __element_type 后包含本头文件，即可像 C++ 模板实例化那样示例化出
// 不同数据类型的循环队列。

#include "c-bsp-interface/type.h"
#include <stddef.h>
#include <stdint.h>

#ifndef __element_type
	#define __element_type int
#endif

typedef struct bsp_circle_queue
{
	size_t _max_count;
	size_t _start;
	size_t _end;
	bsp_bool _is_full;

	__element_type _array[];

} bsp_circle_queue;

///
/// @brief 想要存放 N 个元素，需要准备多少个字节的内存块。
///
///
#define bsp_circle_queue_required_memory_block_size(N) (sizeof(bsp_circle_queue) + N * sizeof(__element_type))

///
/// @brief 想要存放 N 个元素，需要准备具有多少个元素的 uint64_t 数组。
///
///
#define bsp_circle_queue_required_uint64_array_count(N) (bsp_circle_queue_required_memory_block_size(N) / 8 + 1)

/* #region 私有 */

static void bsp_circle_queue_add_start(bsp_circle_queue *self)
{
	self->_start++;
	self->_start %= self->_max_count;
}

static void bsp_circle_queue_sub_start(bsp_circle_queue *self)
{
	if (self->_start == 0)
	{
		self->_start = self->_max_count - 1;
	}
	else
	{
		self->_start--;
	}
}

static void bsp_circle_queue_add_end(bsp_circle_queue *self)
{
	self->_end++;
	self->_end %= self->_max_count;
}

static void bsp_circle_queue_sub_end(bsp_circle_queue *self)
{
	if (self->_end == 0)
	{
		self->_end = self->_max_count - 1;
	}
	else
	{
		self->_end--;
	}
}

/* #endregion */

///
/// @brief 在 memory_block 上构造 bsp_circle_queue.
///
/// @param memory_block uint64_t 的数组。
/// 	@note 使用 uint64_t 数组是为了保证内存对齐。
///
/// 	@note 使用 bsp_circle_queue_required_uint64_array_count 来计算需要一个具有
/// 	多少个元素的 uint64_t 数组。
///
/// @param max_count 最大可以存放的元素个数。
///
/// @return
///
static bsp_circle_queue *bsp_circle_queue_placement_new(uint64_t *memory_block, size_t max_count)
{
	bsp_circle_queue *ret = (bsp_circle_queue *)(memory_block);
	ret->_max_count = max_count;
	ret->_start = 0;
	ret->_end = 0;
	ret->_is_full = 0;
	return ret;
}

static bsp_bool bsp_circle_queue_is_empty(bsp_circle_queue *self)
{
	if (self->_start == self->_end && !self->_is_full)
	{
		return bsp_true;
	}

	return bsp_false;
}

static size_t bsp_circle_queue_count(bsp_circle_queue *self)
{
	if (self->_is_full)
	{
		return self->_max_count;
	}

	if (self->_end < self->_start)
	{
		// 发生了环绕。
		return self->_max_count - (self->_start - self->_end);
	}

	return self->_end - self->_start;
}

static bsp_bool bsp_circle_queue_enqueue(bsp_circle_queue *self, __element_type const *element)
{
	if (self->_is_full)
	{
		return 0;
	}

	self->_array[self->_end] = *element;
	bsp_circle_queue_add_end(self);
	if (self->_start == self->_end)
	{
		self->_is_full = bsp_true;
	}
}

static bsp_bool bsp_circle_queue_dequeue(bsp_circle_queue *self, __element_type *out)
{
	if (bsp_circle_queue_is_empty(self))
	{
		return bsp_false;
	}

	*out = self->_array[self->_start];
	bsp_circle_queue_sub_start(self);
	return bsp_true;
}
