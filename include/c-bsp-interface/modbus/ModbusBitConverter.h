#pragma once
#include <c-bsp-interface/AutoBitConverter.h>

typedef struct ModbusBitConverter ModbusBitConverter;

ModbusBitConverter *ModbusBitConverter_StackHeapAlloc();
