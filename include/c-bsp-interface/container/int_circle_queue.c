#include "int_circle_queue.h"
#include "c-bsp-interface/type.h"

static void bsp_int_circle_queue_add_start(bsp_int_circle_queue *self)
{
	self->_start++;
	self->_start %= self->_max_count;
}

static void bsp_int_circle_queue_add_end(bsp_int_circle_queue *self)
{
	self->_end++;
	self->_end %= self->_max_count;
}

bsp_int_circle_queue *bsp_int_circle_queue_placement_new(uint64_t *memory_block, size_t max_count)
{
	bsp_int_circle_queue *ret = (bsp_int_circle_queue *)(memory_block);
	ret->_max_count = max_count;
	ret->_start = 0;
	ret->_end = 0;
	ret->_is_full = bsp_false;
	return ret;
}

bsp_bool bsp_int_circle_queue_is_empty(bsp_int_circle_queue *self)
{
	if (self->_start == self->_end && !self->_is_full)
	{
		return bsp_true;
	}

	return bsp_false;
}

size_t bsp_int_circle_queue_count(bsp_int_circle_queue *self)
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

bsp_bool bsp_int_circle_queue_enqueue(bsp_int_circle_queue *self, int const *element)
{
	if (self->_is_full)
	{
		return bsp_false;
	}

	self->_array[self->_end] = *element;
	bsp_int_circle_queue_add_end(self);
	if (self->_start == self->_end)
	{
		self->_is_full = bsp_true;
	}

	return bsp_true;
}

bsp_bool bsp_int_circle_queue_dequeue(bsp_int_circle_queue *self, int *out)
{
	if (bsp_int_circle_queue_is_empty(self))
	{
		return bsp_false;
	}

	*out = self->_array[self->_start];
	bsp_int_circle_queue_add_start(self);
	return bsp_true;
}
