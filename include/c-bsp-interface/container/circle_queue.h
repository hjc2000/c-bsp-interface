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
	///
	/// @brief 总大小。
	///
	/// @note 预先分配一个字节数组，将数组头指针强制转换为本结构体的指针，然后初始化，
	/// 相当于 C++ 的 placement new. 本字段用来记录这个字节数组的总大小。
	///
	///
	size_t _total_size;

	size_t _head;
	size_t _tail;
	bsp_bool _is_full;

	__element_type _array[];

} bsp_circle_queue;

///
/// @brief 在 memory_block 上构造 bsp_circle_queue.
///
/// @param memory_block uint64_t 的数组。
/// 	@note 使用 uint64_t 数组是为了保证内存对齐。
///
/// @param total_size memory_block 的总字节数。
///
/// @return
///
static bsp_circle_queue *bsp_circle_queue_placement_new(uint64_t *memory_block, size_t total_size)
{
	bsp_circle_queue *ret = (bsp_circle_queue *)(memory_block);
	ret->_total_size = total_size;
	ret->_head = 0;
	ret->_tail = 0;
	ret->_is_full = 0;
	return ret;
}

#undef __element_type
