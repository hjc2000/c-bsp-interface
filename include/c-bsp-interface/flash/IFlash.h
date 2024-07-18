#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct IFlash
{
	void *_self;

	void (*Lock)(void *self);
	void (*Unlock)(void *self);

	/// @brief 获取此 flash 的 bank 数量。
	/// @param self
	/// @return
	int32_t (*BankCount)(void *self);

	/// @brief 获取指定 bank 的基地址。
	/// @param self
	/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
	/// @return
	size_t (*GetBankBaseAddress)(void *self, int32_t bank_id);

	/// @brief 获取指定 bank 的大小。单位：字节。
	/// @param self
	/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
	/// @return
	size_t (*GetBankSize)(void *self, int32_t bank_id);

	/// @brief flash 的最小编程单位。单位：字节。
	/// @param self
	/// @note 最小单位是一次编程必须写入这么多字节，即使要写入的数据没有这么多，在一次
	/// 写入后，整个单位大小的区域都无法再次写入了，除非擦除整个扇区。
	/// @return 返回此 flash 编程的最小单位。
	int32_t (*MinProgrammingUnit)(void *self);

	/// @brief 擦除一整个 bank。
	/// @param self
	/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
	void (*EraseBank)(void *self, int32_t bank_id);

	/// @brief 擦除指定 bank 中从 start_sector_index 开始的 sector_count 个扇区。
	/// @param self
	/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
	/// @param start_sector_index 要擦除的扇区的起始索引。
	/// @param sector_count 要擦除的扇区的数量。
	void (*EraseSector)(void *self, int32_t bank_id, int32_t start_sector_index, int32_t sector_count);

	/// @brief 将 flash 的数据读取到缓冲区中
	/// @param self
	/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
	/// @param addr
	/// @param buffer
	/// @param count
	void (*ReadBuffer)(void *self, int32_t bank_id, size_t addr, uint8_t *buffer, int32_t count);

	/// @brief 编程
	/// @param self
	/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
	///
	/// @param addr 要写入的数据相对于此 bank 的起始地址的地址。
	/// @note 此地址必须能被 MinProgrammingUnit 整除。
	///
	/// @param buffer 要写入到 flash 的数据所在的缓冲区。
	/// @warning buffer 的字节数必须 >= MinProgrammingUnit，否则将发生内存访问越界。
	///
	/// @exception 不同平台对 buffer 有对齐要求。例如 stm32 的 HAL 要求 buffer 要 4 字节
	/// 对齐。这里使用 uint8_t const * ，接口的实现者自己计算 buffer 能否被对齐字节数整除，
	/// 不能整除抛出异常。
	void (*Program)(void *self, int32_t bank_id, size_t addr, uint8_t const *buffer);
} IFlash;

/// @brief 将相对于指定 bank 的起始地址的地址转化为绝对地址。
/// @param self
/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
/// @param addr 相对于此 bank 起始地址的地址。
/// @return 绝对地址。可以被强制转换为指针。
size_t IFlash_GetAbsoluteAddress(IFlash *self, int32_t bank_id, size_t addr);

/// @brief 读取指定 bank 的指定地址的 1 字节数据。
/// @param self
/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
/// @param addr 相对于此 bank 的起始地址的地址。
/// @return
uint8_t IFlash_ReadUInt8(IFlash *self, int32_t bank_id, size_t addr);

/// @brief 读取指定 bank 的指定地址的 2 字节数据。
/// @param self
/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
/// @param addr 相对于此 bank 的起始地址的地址。
/// @return
uint16_t IFlash_ReadUInt16(IFlash *self, int32_t bank_id, size_t addr);

/// @brief 读取指定 bank 的指定地址的 4 字节数据。
/// @param self
/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
/// @param addr 相对于此 bank 的起始地址的地址。
/// @return
uint32_t IFlash_ReadUInt32(IFlash *self, int32_t bank_id, size_t addr);

/// @brief 读取指定 bank 的指定地址的 8 字节数据。
/// @param self
/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
/// @param addr 相对于此 bank 的起始地址的地址。
/// @return
uint64_t IFlash_ReadUInt64(IFlash *self, int32_t bank_id, size_t addr);
