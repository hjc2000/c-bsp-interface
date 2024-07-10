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

static void GetCurrentKeyPressedState(KeyScanner *o)
{
	// 遍历每个按键
	for (int32_t i = 0; i < o->_key_count; i++)
	{
		Bitset *bitset = o->_key_pressed_state_bitset;
		IKey *key = o->_keys[i];
		Bitset_SetBitValue(bitset, i, key->KeyIsDown());
	}

	o->DelayMilliseconds(20);

	for (int32_t i = 0; i < o->_key_count; i++)
	{
		uint8_t value = o->_keys[i]->KeyIsDown() &&
						Bitset_GetBit(o->_key_pressed_state_bitset, i);

		Bitset_SetBitValue(o->_key_pressed_state_bitset, i, value);
	}
}

KeyScanner *KeyScanner_StackHeapAlloc(int32_t key_count,
									  void (*delay_milliseconds)(uint32_t ms))
{
	if (key_count <= 0)
	{
		return 0;
	}

	KeyScanner *o = (KeyScanner *)StackHeapObjAlloc(sizeof(KeyScanner));

	// 能够装下 key_count 个指针的指针数组
	o->_keys = StackHeapObjAlloc(sizeof(IKey *) * key_count);
	o->_key_count = key_count;

	o->_key_pressed_state_bitset = Bitset_StackHeapAlloc(key_count);
	o->_key_down_event_bitset = Bitset_StackHeapAlloc(key_count);
	o->_key_up_event_bitset = Bitset_StackHeapAlloc(key_count);
	o->_last_key_pressed_state_bitset = Bitset_StackHeapAlloc(key_count);

	o->DelayMilliseconds = delay_milliseconds;
	return o;
}

void KeyScanner_SetKey(KeyScanner *o, int32_t index, IKey *key)
{
	if (index < 0 || index >= o->_key_count)
	{
		return;
	}

	o->_keys[index] = key;
}

void KeyScanner_Scan(KeyScanner *o)
{
	GetCurrentKeyPressedState(o);

	Bitset_CopyFrom(o->_key_down_event_bitset,
					o->_last_key_pressed_state_bitset);

	Bitset_Not(o->_key_down_event_bitset);

	Bitset_And(o->_key_down_event_bitset,
			   o->_key_pressed_state_bitset);

	Bitset_CopyFrom(o->_key_up_event_bitset,
					o->_key_pressed_state_bitset);

	Bitset_Not(o->_key_up_event_bitset);

	Bitset_And(o->_key_up_event_bitset,
			   o->_last_key_pressed_state_bitset);

	Bitset_CopyFrom(o->_last_key_pressed_state_bitset,
					o->_key_pressed_state_bitset);
}

uint8_t KeyScanner_KeyIsPressed(KeyScanner *o, int32_t key_index)
{
	return Bitset_GetBit(o->_key_pressed_state_bitset, key_index);
}

uint8_t KeyScanner_HasKeyDownEvent(KeyScanner *o, int32_t key_index)
{
	return Bitset_GetBit(o->_key_down_event_bitset, key_index);
}

uint8_t KeyScanner_HasKeyUpEvent(KeyScanner *o, int32_t key_index)
{
	return Bitset_GetBit(o->_key_up_event_bitset, key_index);
}
