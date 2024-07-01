#include "KeyScanner.h"
#include <c-bsp-interface/Bitset.h>
#include <c-bsp-interface/memory/StackHeap.h>

typedef struct KeyScanner
{
	Bitset *_last_key_pressed_state_bitset;
	Bitset *_key_pressed_state_bitset;
	Bitset *_key_down_event_bitset;
	Bitset *_key_up_event_bitset;

	/// @brief 将按键实例的指针放到数组中，赋值给本字段
	IKey **_keys;

	/// @brief 按键个数
	int32_t _key_count;

	/// @brief 延时函数。用来消抖。
	void (*DelayMilliseconds)(uint32_t ms);
} KeyScanner;

static void GetCurrentKeyPressedState(KeyScanner *this)
{
	// 遍历每个按键
	for (int32_t i = 0; i < this->_key_count; i++)
	{
		Bitset *bitset = this->_key_pressed_state_bitset;
		IKey *key = this->_keys[i];
		Bitset_SetBitValue(bitset, i, key->KeyIsDown());
	}

	this->DelayMilliseconds(20);

	for (int32_t i = 0; i < this->_key_count; i++)
	{
		uint8_t value = this->_keys[i]->KeyIsDown() &&
						Bitset_GetBit(this->_key_pressed_state_bitset, i);

		Bitset_SetBitValue(this->_key_pressed_state_bitset, i, value);
	}
}

KeyScanner *KeyScanner_StackHeapAlloc(int32_t key_count,
									  void (*delay_milliseconds)(uint32_t ms))
{
	if (key_count <= 0)
	{
		return 0;
	}

	KeyScanner *this = (KeyScanner *)StackHeapAlignAlloc(sizeof(KeyScanner),
														 sizeof(KeyScanner *));

	// 能够装下 key_count 个指针的指针数组
	this->_keys = StackHeapAlignAlloc(sizeof(IKey *) * key_count, 4);
	this->_key_count = key_count;

	this->_key_pressed_state_bitset = Bitset_StackHeapAlloc(key_count);
	this->_key_down_event_bitset = Bitset_StackHeapAlloc(key_count);
	this->_key_up_event_bitset = Bitset_StackHeapAlloc(key_count);
	this->_last_key_pressed_state_bitset = Bitset_StackHeapAlloc(key_count);

	this->DelayMilliseconds = delay_milliseconds;
	return this;
}

void KeyScanner_SetKey(KeyScanner *this, int32_t index, IKey *key)
{
	if (index < 0 || index >= this->_key_count)
	{
		return;
	}

	this->_keys[index] = key;
}

void KeyScanner_Scan(KeyScanner *this)
{
	GetCurrentKeyPressedState(this);

	Bitset_CopyFrom(this->_key_down_event_bitset,
					this->_last_key_pressed_state_bitset);

	Bitset_Not(this->_key_down_event_bitset);

	Bitset_And(this->_key_down_event_bitset,
			   this->_key_pressed_state_bitset);

	Bitset_CopyFrom(this->_key_up_event_bitset,
					this->_key_pressed_state_bitset);

	Bitset_Not(this->_key_up_event_bitset);

	Bitset_And(this->_key_up_event_bitset,
			   this->_last_key_pressed_state_bitset);

	Bitset_CopyFrom(this->_last_key_pressed_state_bitset,
					this->_key_pressed_state_bitset);
}

uint8_t KeyScanner_KeyIsPressed(KeyScanner *this, int32_t key_index)
{
	return Bitset_GetBit(this->_key_pressed_state_bitset, key_index);
}

uint8_t KeyScanner_HasKeyDownEvent(KeyScanner *this, int32_t key_index)
{
	return Bitset_GetBit(this->_key_down_event_bitset, key_index);
}

uint8_t KeyScanner_HasKeyUpEvent(KeyScanner *this, int32_t key_index)
{
	return Bitset_GetBit(this->_key_up_event_bitset, key_index);
}
