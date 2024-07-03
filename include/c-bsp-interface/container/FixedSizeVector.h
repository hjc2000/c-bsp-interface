#pragma once
#include <stdint.h>

/// @brief 固定大小，不会增长的向量
typedef struct FixedSizeVector FixedSizeVector;

/// @brief 在栈堆上构造 FixedSizeVector。
/// @param element_size 放到向量中的每个元素的大小
/// @param max_element_count 最大能容纳的元素个数
/// @return
FixedSizeVector *FixedSizeVector_StackHeapAlloc(int32_t element_size, int32_t max_element_count);

/// @brief 获取 FixedSizeVector 底层的缓冲区。
/// @param o
/// @return
uint8_t *FixedSizeVector_Buffer(FixedSizeVector *o);

/// @brief 获取 FixedSizeVector 总的有效的数据的大小。单位：字节。
/// @param o
/// @return
int32_t FixedSizeVector_Size(FixedSizeVector *o);

/// @brief 清空所有数据
/// @param o
void FixedSizeVector_Clear(FixedSizeVector *o);

/// @brief 在 FixedSizeVector 末尾添加一个元素。
/// @param o
/// @param element 要被添加的元素的指针。会将指针指向的内存复制到向量中。
/// @return 添加成功返回 true，失败返回 false
uint8_t FixedSizeVector_PushBack(FixedSizeVector *o, void *element);
