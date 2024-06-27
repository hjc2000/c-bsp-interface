#pragma once
#include <c-bsp-interface/AsyncStream.h>
#include <c-bsp-interface/IDigitalLed.h>
#include <c-bsp-interface/IKey.h>

typedef struct ModbusServant
{
	AsyncStream *_stream;
	IDigitalLed *_red_led;
	IDigitalLed *_green_led;
	IKey *_key0;
	IKey *_key1;
} ModbusServant;

void ModbusServant_Start(ModbusServant *this);
