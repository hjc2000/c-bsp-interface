#include "ModbusServant.h"
#include <c-bsp-interface/KeyScanner.h>

static ModbusServant *_servant;
static KeyScanner _key_scanner;

static void InitKeyScanner()
{
#pragma region 初始化 4 个 Bitset
	{
		static uint8_t set[2];
		_key_scanner._last_key_pressed_state_bitset._set = set;
		_key_scanner._last_key_pressed_state_bitset._size = 2;
	}
	{
		static uint8_t set[2];
		_key_scanner._key_pressed_state_bitset._set = set;
		_key_scanner._key_pressed_state_bitset._size = 2;
	}
	{
		static uint8_t set[2];
		_key_scanner._key_down_event_bitset._set = set;
		_key_scanner._key_down_event_bitset._size = 2;
	}
	{
		static uint8_t set[2];
		_key_scanner._key_up_event_bitset._set = set;
		_key_scanner._key_up_event_bitset._size = 2;
	}
#pragma endregion

	{
		static IKey *keys[2];
		keys[0] = _servant->_key0;
		keys[1] = _servant->_key1;
		_key_scanner._keys = keys;
	}

	_key_scanner._key_count = 2;
	_key_scanner.DelayMilliseconds = _servant->DelayMilliseconds;
}

void ModbusServant_Start(ModbusServant *this)
{
	_servant = this;
	InitKeyScanner();
}