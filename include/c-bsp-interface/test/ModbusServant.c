#include "ModbusServant.h"
#include <c-bsp-interface/modbus/ModbusCrc16.h>

void ModbusServant_Init(ModbusServant *this,
						uint8_t servant_address,
						IDigitalLed *red_led,
						IDigitalLed *green_led,
						IKey *key0,
						IKey *key1)
{
	this->_servant_address = servant_address;
	this->_red_led = red_led;
	this->_green_led = green_led;
	this->_key0 = key0;
	this->_key1 = key1;
}

void ModbusServant_FeedBuffer(ModbusServant *this,
							  uint8_t *buffer, int32_t offset, int32_t count)
{
}
