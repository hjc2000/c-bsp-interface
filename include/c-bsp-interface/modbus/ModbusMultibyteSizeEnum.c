#include "ModbusMultibyteSizeEnum.h"

int ModbusMultibyteSizeEnum_To_ByteCount(ModbusMultibyteSizeEnum value)
{
	switch (value)
	{
	case ModbusMultibyteSizeEnum_Byte:
	{
		return 1;
	}
	case ModbusMultibyteSizeEnum_2Byte:
	{
		return 2;
	}
	case ModbusMultibyteSizeEnum_4Byte:
	{
		return 4;
	}
	case ModbusMultibyteSizeEnum_8Byte:
	{
		return 8;
	}
	}

	return 1;
}
