#pragma once
#include <stdint.h>

typedef struct Stack Stack;

/// @brief 在栈堆上构造 Stack。
/// @param max_size 栈的最大大小。
/// @return
Stack *Stack_StackHeapAlloc(int32_t max_size);

/// @brief 清空栈。
/// @param
void Stack_Clear(Stack *this);

/// @brief 入栈指定大小的数据
/// @param data 要入栈的数据的指针。
/// @param size 要入栈的字节数。
/// @return 成功返回 true，失败返回 false。
uint8_t Stack_Push(Stack *this, void *data, int32_t size);

/// @brief 出栈指定大小的数据。
/// @param out 出栈的数据会被复制到该指针指向的内存。
/// @param size 要出栈的字节数。
/// @return 成功返回 true，失败返回 false。
uint8_t Stack_Pop(Stack *this, void *out, int32_t size);

/// @brief 获取栈的底层缓冲区。
/// @param
/// @return
uint8_t *Stack_Buffer(Stack *this);

/// @brief 栈的最大字节数。即内部缓冲区的大小。
/// @param
/// @return
int32_t Stack_MaxSize(Stack *this);

/// @brief sp 指向的是栈顶的空格子。
/// @param
/// @return
int32_t Stack_Sp(Stack *this);
