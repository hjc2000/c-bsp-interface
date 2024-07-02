#include "Bitset.h"
#include <c-bsp-interface/memory/StackHeap.h>
#include <string.h>

typedef struct Bitset
{
	/// @brief 用来存放每个位的数组。
	uint8_t *_set;

	/// @brief _set 字段是一个多少个字节的数组
	uint32_t _size;
} Bitset;

static uint32_t min(uint32_t value1, uint32_t value2)
{
	if (value1 < value2)
	{
		return value1;
	}

	return value2;
}

Bitset *Bitset_StackHeapAlloc(int32_t bit_count)
{
	if (bit_count <= 0)
	{
		return 0;
	}

	Bitset *bitset = (Bitset *)StackHeapAlignAlloc(sizeof(Bitset), 4);
	int32_t buffer_size = bit_count / 8;
	if (bit_count % 8 != 0)
	{
		buffer_size += 1;
	}

	bitset->_set = StackHeapAlloc(buffer_size);
	bitset->_size = buffer_size;
	return bitset;
}

void Bitset_CopyFrom(Bitset *this, Bitset *another)
{
	memcpy(this->_set, another->_set, min(this->_size, another->_size));
}

void Bitset_Clear(Bitset *this)
{
	memset(this->_set, 0, this->_size);
}

uint8_t Bitset_GetBit(Bitset *this, uint32_t bit_index)
{
	uint8_t mask = 1 << (bit_index % 8);
	uint8_t masked_value = this->_set[bit_index / 8] & mask;
	return masked_value ? 1 : 0;
}

void Bitset_SetBit(Bitset *this, uint32_t bit_index)
{
	uint8_t mask = 1 << (bit_index % 8);
	this->_set[bit_index / 8] |= mask;
}

void Bitset_ResetBit(Bitset *this, uint32_t bit_index)
{
	uint8_t mask = 1 << (bit_index % 8);
	this->_set[bit_index / 8] &= ~mask;
}

void Bitset_SetBitValue(Bitset *this, uint32_t bit_index, uint8_t value)
{
	if (value)
	{
		Bitset_SetBit(this, bit_index);
	}
	else
	{
		Bitset_ResetBit(this, bit_index);
	}
}

void Bitset_Not(Bitset *this)
{
	for (uint32_t i = 0; i < this->_size; i++)
	{
		this->_set[i] = ~this->_set[i];
	}
}

void Bitset_And(Bitset *this, Bitset *another)
{
	for (uint32_t i = 0; i < min(this->_size, another->_size); i++)
	{
		this->_set[i] &= another->_set[i];
	}
}
