#pragma once
#include <stdint.h>

typedef struct Bitset Bitset;

/// @brief 在 StackHeap 上分配 Bitset 的内存并对他的字段进行初始化。
/// @param bit_count 需要储存多少个位
/// @return
Bitset *Bitset_StackHeapAlloc(int32_t bit_count);

/// @brief 将 another 的 _set 中的位复制过来，放到 this 的 _set 中。
/// @note 如果两个 _set 大小不匹配，会按照最小的那个来操作。
///
/// @param
/// @param another
void Bitset_CopyFrom(Bitset *this, Bitset *another);

/// @brief 将每一位清 0.
/// @param
void Bitset_Clear(Bitset *this);

/// @brief 获取指定位的值。
/// @param
/// @param bit_index
/// @return 指定位为 1，返回 1. 指定位为 0，返回 0.
uint8_t Bitset_GetBit(Bitset *this, uint32_t bit_index);

/// @brief 将指定的位置位。（置成 1）
/// @param
/// @param bit_index
void Bitset_SetBit(Bitset *this, uint32_t bit_index);

/// @brief 将指定的位复位。（置成 0）
/// @param
/// @param bit_index
void Bitset_ResetBit(Bitset *this, uint32_t bit_index);

/// @brief 设置指定位的值。
/// @param
/// @param bit_index
/// @param value
void Bitset_SetBitValue(Bitset *this, uint32_t bit_index, uint8_t value);

/// @brief 按位取反
/// @param
void Bitset_Not(Bitset *this);

/// @brief 将 this 与 another 的每个位相与。与的结果会覆盖 this。
/// @note 两个 Bitset 尺寸要一样，实际执行过程中以 this 的尺寸为准，将它当作双方的尺寸。
///
/// @param
/// @param another
void Bitset_And(Bitset *this, Bitset *another);
