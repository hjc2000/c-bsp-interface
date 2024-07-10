#include "ModbusCrc16.h"
#include <c-bsp-interface/memory/StackHeap.h>
#include <c-bsp-interface/stream/Stream.h>

typedef struct ModbusCrc16
{
	uint16_t _crc16_register;
	uint16_t _polynomial;
} ModbusCrc16;

ModbusCrc16 *ModbusCrc16_StackHeapAlloc()
{
	ModbusCrc16 *o = StackHeapObjAlloc(sizeof(ModbusCrc16));
	ModbusCrc16_ResetRegister(o);

	/* 默认的生成多项式是：
	 * 		x16+x15+x2+1
	 * 这个生成多项式转化成系数，从最低次的系数开始写，最低次是 x^0，系数是 1，
	 * 写在最左边，然后 x^1 的系数是 0，接着写在右边，x^2 的系数是 1，接着写在
	 * 右边，以此类推，得到：
	 * 		10100000000000011
	 * x^16 的系数是 1，但是最高次的系数是要被忽略的，因为最高次的系数一定是 1，
	 * 例如这里的最高次是 16 次，如果 16 次的系数不是 1，那最高次就变成 15 次
	 * 而不是 16 次了。
	 *
	 * 忽略最高次的系数后，得到
	 * 		1010000000000001
	 * 这个数称为生成数。
	 *
	 * 这个生成数和生成多项式是反着来的，最高位对应的是生成多项式最低次的系数。
	 * 转化为 16 进制就是 0xA001。
	 */
	o->_polynomial = 0xA001;

	return o;
}

void ModbusCrc16_ResetRegister(ModbusCrc16 *o)
{
	o->_crc16_register = UINT16_MAX;
}

void ModbusCrc16_Add(ModbusCrc16 *o, uint8_t data)
{
	o->_crc16_register ^= (uint16_t)(data);
	for (int i = 0; i < 8; i++)
	{
		uint16_t lsb = o->_crc16_register & 0x1;
		o->_crc16_register >>= 1;
		if (lsb)
		{
			o->_crc16_register ^= o->_polynomial;
		}
	}
}

void ModbusCrc16_AddArray(ModbusCrc16 *o, uint8_t *datas, uint32_t count)
{
	for (uint32_t i = 0; i < count; i++)
	{
		ModbusCrc16_Add(o, datas[i]);
	}
}

uint16_t ModbusCrc16_Register(ModbusCrc16 *o)
{
	return o->_crc16_register;
}

uint8_t ModbusCrc16_HighByte(ModbusCrc16 *o)
{
	return (uint8_t)(o->_crc16_register >> 8);
}

uint8_t ModbusCrc16_LowByte(ModbusCrc16 *o)
{
	return (uint8_t)(o->_crc16_register);
}

uint8_t ModbusCrc16_CompareRegister(ModbusCrc16 *o,
									uint8_t *crc16_register_buffer,
									Endian crc16_register_buffer_endian)
{
	uint8_t buffer_low_byte;
	uint8_t buffer_high_byte;

	if (crc16_register_buffer_endian == LittleEndian)
	{
		buffer_low_byte = crc16_register_buffer[0];
		buffer_high_byte = crc16_register_buffer[1];
	}
	else
	{
		buffer_low_byte = crc16_register_buffer[1];
		buffer_high_byte = crc16_register_buffer[0];
	}

	return buffer_low_byte == ModbusCrc16_LowByte(o) &&
		   buffer_high_byte == ModbusCrc16_HighByte(o);
}

void ModbusCrc16_WriteRegisterToStream(ModbusCrc16 *self, Stream *stream, Endian endian)
{
	uint8_t crc16_high_byte = ModbusCrc16_HighByte(self);
	uint8_t crc16_low_byte = ModbusCrc16_LowByte(self);
	if (endian == BigEndian)
	{
		stream->Write(stream->_self, &crc16_high_byte, 0, 1);
		stream->Write(stream->_self, &crc16_low_byte, 0, 1);
	}
	else
	{
		stream->Write(stream->_self, &crc16_low_byte, 0, 1);
		stream->Write(stream->_self, &crc16_high_byte, 0, 1);
	}
}
