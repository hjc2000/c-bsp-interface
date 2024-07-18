#include "IFlash.h"

size_t IFlash_GetAbsoluteAddress(IFlash *self, int32_t bank_id, size_t addr)
{
	if (addr >= self->GetBankSize(self->_self, bank_id))
	{
		return 0;
	}

	return self->GetBankBaseAddress(self->_self, bank_id) + addr;
}

uint8_t IFlash_ReadUInt8(IFlash *self, int32_t bank_id, size_t addr)
{
	uint8_t ret;
	self->ReadBufferAsync(self->_self, bank_id, addr, (uint8_t *)(&ret), sizeof(ret));
	return ret;
}

uint16_t IFlash_ReadUInt16(IFlash *self, int32_t bank_id, size_t addr)
{
	uint16_t ret;
	self->ReadBufferAsync(self->_self, bank_id, addr, (uint8_t *)(&ret), sizeof(ret));
	return ret;
}

uint32_t IFlash_ReadUInt32(IFlash *self, int32_t bank_id, size_t addr)
{
	uint32_t ret;
	self->ReadBufferAsync(self->_self, bank_id, addr, (uint8_t *)(&ret), sizeof(ret));
	return ret;
}

uint64_t IFlash_ReadUInt64(IFlash *self, int32_t bank_id, size_t addr)
{
	uint64_t ret;
	self->ReadBufferAsync(self->_self, bank_id, addr, (uint8_t *)(&ret), sizeof(ret));
	return ret;
}
