#pragma once
#include <stdint.h>

typedef struct Bitset
{
	/// <summary>
	///		用来存放每个位的数组。
	/// </summary>
	uint8_t *_set;

	/// <summary>
	///		_set 字段是一个多少个字节的数组
	/// </summary>
	uint32_t _size;
} Bitset;

/// <summary>
///		将 another 的 _set 中的位复制过来，放到 this 的 _set 中。
///		* 如果两个 _set 大小不匹配，会按照最小的那个来操作。
/// </summary>
/// <param name=""></param>
/// <param name="another"></param>
void Bitset_CopyFrom(Bitset *this, Bitset *another);

/// <summary>
///		将每一位清 0.
/// </summary>
/// <param name=""></param>
void Bitset_Clear(Bitset *this);

/// <summary>
///		获取指定位的值。
/// </summary>
/// <param name=""></param>
/// <param name="bit_index"></param>
/// <returns>指定位为 1，返回 1. 指定位为 0，返回 0.</returns>
uint8_t Bitset_GetBit(Bitset *this, uint32_t bit_index);

/// <summary>
///		将指定的位置位。（置成 1）
/// </summary>
/// <param name=""></param>
/// <param name="bit_index"></param>
void Bitset_SetBit(Bitset *this, uint32_t bit_index);

/// <summary>
///		将指定的位复位。（置成 0）
/// </summary>
/// <param name=""></param>
/// <param name="bit_index"></param>
void Bitset_ResetBit(Bitset *this, uint32_t bit_index);

/// <summary>
///		设置指定位的值。
/// </summary>
/// <param name=""></param>
/// <param name="bit_index"></param>
/// <param name="value"></param>
void Bitset_SetBitValue(Bitset *this, uint32_t bit_index, uint8_t value);

/// <summary>
///		按位取反
/// </summary>
/// <param name=""></param>
void Bitset_Not(Bitset *this);

/// <summary>
///		将 this 与 another 的每个位相与。与的结果会覆盖 this。
///		两个 Bitset 尺寸要一样，实际执行过程中以 this 的尺寸为准，将它当作双方的尺寸。
/// </summary>
/// <param name=""></param>
/// <param name="another"></param>
void Bitset_And(Bitset *this, Bitset *another);
