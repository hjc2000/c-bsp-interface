#include "ModbusServant.h"
#include <c-bsp-interface/KeyScanner.h>

static ModbusServant *_servant;
static KeyScanner _key_scanner;

static void InitKeyScanner()
{
	{
		static IKey *keys[2];
		keys[0] = _servant->_key0;
		keys[1] = _servant->_key1;
		_key_scanner._keys = keys;
	}
}

void ModbusServant_Start(ModbusServant *this)
{
	_servant = this;
	InitKeyScanner();
}