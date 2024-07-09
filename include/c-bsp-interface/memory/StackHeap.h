#pragma once
#include <stdint.h>

// 栈堆的总大小
#define STACK_HEAP_SIZE 1024 * 4

/// @brief 在栈堆上分配一段内存。
/// @note 栈堆就是将一个静态数组作为内存空间，维护一个栈的数据结构，调用本函数请求进行空间
/// 分配后，会返回当前栈顶指针，然后将栈顶指针递增 size。这相当于一个只能分配，无法释放的堆。
/// @note 对于程序初始化阶段特别有用。初始化需要运行时决定大小，而且一旦分配就永远不需要释放，
/// 这就很适合使用栈堆。
/// @note 本函数分配的内存是 1 字节对齐的。
///
/// @param size
/// @return
void *StackHeapAlloc(int32_t size);

/// @brief 按照指定的对齐方式分配内存
/// @param size 内存大小。单位：字节。
/// @param align 分配的这段内存要对齐到的字节数。
/// @return
void *StackHeapAlignAlloc(int32_t size, int32_t align);

/// @brief 检查栈堆是否发生过溢出
/// @return 栈堆发生过溢出就会返回 true，否则返回 false
uint8_t StackHeapOverflow();

/// @brief 设置栈堆溢出后的处理函数
/// @param func
void SetStackHeapOverflowHandler(void (*func)());

/// @brief 当前栈顶指针的位置。
/// @note 这个栈顶指针并不是一个真的指针。他只是从 0 开始的，对缓冲区头指针的偏移量。
/// @return
uint32_t StackHeapSp();
