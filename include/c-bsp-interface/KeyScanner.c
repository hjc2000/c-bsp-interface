#include "KeyScanner.h"

static void GetCurrentKeyPressedState(KeyScanner *this)
{
	// 遍历每个按键
	for (uint32_t i = 0; i < this->_key_count; i++)
	{
		Bitset *bitset = &this->_key_pressed_state_bitset;
		IKey *key = this->_keys[i];
		Bitset_SetBitValue(bitset, i, key->KeyIsDown());
	}

	this->DelayMilliseconds(20);

	for (uint32_t i = 0; i < this->_key_count; i++)
	{
		uint8_t value = this->_keys[i]->KeyIsDown() && Bitset_GetBit(&this->_key_pressed_state_bitset, i);
		Bitset_SetBitValue(&this->_key_pressed_state_bitset, i, value);
	}
}

void KeyScanner_Scan(KeyScanner *this)
{
	GetCurrentKeyPressedState(this);

	Bitset_CopyFrom(&this->_key_down_event_bitset, &this->_last_key_pressed_state_bitset);
	Bitset_Not(&this->_key_down_event_bitset);
	Bitset_And(&this->_key_down_event_bitset, &this->_key_pressed_state_bitset);

	Bitset_CopyFrom(&this->_key_up_event_bitset, &this->_key_pressed_state_bitset);
	Bitset_Not(&this->_key_up_event_bitset);
	Bitset_And(&this->_key_up_event_bitset, &this->_last_key_pressed_state_bitset);

	Bitset_CopyFrom(&this->_last_key_pressed_state_bitset, &this->_key_pressed_state_bitset);
}

uint8_t KeyScanner_KeyIsPressed(KeyScanner *this, uint32_t key_index)
{
	return Bitset_GetBit(&this->_key_pressed_state_bitset, key_index);
}

uint8_t KeyScanner_HasKeyDownEvent(KeyScanner *this, uint32_t key_index)
{
	return Bitset_GetBit(&this->_key_down_event_bitset, key_index);
}

uint8_t KeyScanner_HasKeyUpEvent(KeyScanner *this, uint32_t key_index)
{
	return Bitset_GetBit(&this->_key_up_event_bitset, key_index);
}
