#pragma once
// 在翻译单元中定义 int 后包含本头文件，即可像 C++ 模板实例化那样示例化出
// 不同数据类型的循环队列。

#include "c-bsp-interface/type.h"
#include <stddef.h>
#include <stdint.h>

typedef struct bsp_int_circle_queue
{
	size_t _max_count;
	size_t _start;
	size_t _end;
	bsp_bool _is_full;

	int _array[];

} bsp_int_circle_queue;

///
/// @brief 想要存放 N 个元素，需要准备多少个字节的内存块。
///
///
#define bsp_int_circle_queue_required_memory_block_size(N) (sizeof(bsp_int_circle_queue) + N * sizeof(int))

///
/// @brief 想要存放 N 个元素，需要准备具有多少个元素的 uint64_t 数组。
///
///
#define bsp_int_circle_queue_required_uint64_array_count(N) (bsp_int_circle_queue_required_memory_block_size(N) / 8 + 1)

///
/// @brief 在 memory_block 上构造 bsp_int_circle_queue.
///
/// @param memory_block uint64_t 的数组。
/// 	@note 使用 uint64_t 数组是为了保证内存对齐。
///
/// 	@note 使用 bsp_int_circle_queue_required_uint64_array_count 来计算需要一个具有
/// 	多少个元素的 uint64_t 数组。
///
/// @param max_count 最大可以存放的元素个数。
///
/// @return
///
bsp_int_circle_queue *bsp_int_circle_queue_placement_new(uint64_t *memory_block, size_t max_count);

bsp_bool bsp_int_circle_queue_is_empty(bsp_int_circle_queue *self);

size_t bsp_int_circle_queue_count(bsp_int_circle_queue *self);

bsp_bool bsp_int_circle_queue_enqueue(bsp_int_circle_queue *self, int const *element);

bsp_bool bsp_int_circle_queue_dequeue(bsp_int_circle_queue *self, int *out);
