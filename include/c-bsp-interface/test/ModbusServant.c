#include "ModbusServant.h"
#include <c-bsp-interface/ModbusCrc16.h>

static ModbusServant *_servant;

void ModbusServant_Start(ModbusServant *this)
{
	_servant = this;
}
