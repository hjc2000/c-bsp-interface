#include "ModbusBitConverter.h"
#include <c-bsp-interface/memory/StackHeap.h>

typedef struct ModbusBitConverter
{
	AutoBitConverter *_auto_bit_converter;
} ModbusBitConverter;

ModbusBitConverter *ModbusBitConverter_StackHeapAlloc()
{
	ModbusBitConverter *this = StackHeapAlignAlloc(sizeof(ModbusBitConverter), 4);

	// modbus 一律使用大端序
	this->_auto_bit_converter = AutoBitConverter_StackHeapAlloc(BigEndian);
	return this;
}
