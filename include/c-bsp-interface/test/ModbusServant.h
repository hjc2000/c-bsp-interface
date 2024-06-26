#pragma once
#include <c-bsp-interface/AsyncStream.h>
#include <c-bsp-interface/IDigitalLed.h>
#include <c-bsp-interface/IKey.h>
#include <c-bsp-interface/KeyScanner.h>

typedef struct ModbusServant
{
	AsyncStream *_stream;
	IDigitalLed *_red_led;
	IDigitalLed *_green_led;
	KeyScanner *_key_scanner;
} ModbusServant;

void ModbusServant_Start(ModbusServant *this);
