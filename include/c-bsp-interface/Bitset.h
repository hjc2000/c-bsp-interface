#pragma once
#include <stdint.h>

typedef struct Bitset
{
	uint8_t *_set;

	/**
	 * @brief _set 字段是一个多少个字节的数组
	 *
	 */
	uint32_t _size;
} Bitset;

void Bitset_CopyFrom(Bitset *this, Bitset *another);

void Bitset_Clear(Bitset *this);

/**
 * @brief 获取指定位的值。指定位为 1，返回 1. 指定位为 0，返回 0.
 *
 * @param this
 * @param bit_index
 * @return uint8_t
 */
uint8_t Bitset_GetBit(Bitset *this, uint32_t bit_index);

/**
 * @brief 将指定的位置位。（置成 1）
 *
 * @param this
 * @param bit_index
 */
void Bitset_SetBit(Bitset *this, uint32_t bit_index);

/**
 * @brief 将指定的位复位。（置成 0）
 *
 * @param this
 * @param bit_index
 */
void Bitset_ResetBit(Bitset *this, uint32_t bit_index);

void Bitset_SetBitValue(Bitset *this, uint32_t bit_index, uint8_t value);

/**
 * @brief 按位取反
 *
 * @param this
 */
void Bitset_Not(Bitset *this);

/**
 * @brief 将 this 与 another 的每个位相与。与的结果会覆盖 this。
 * 两个 Bitset 尺寸要一样，实际执行过程中以 this 的尺寸为准，将它当作双方的尺寸。
 *
 * @param this
 * @param another
 */
void Bitset_And(Bitset *this, Bitset *another);
