#pragma once
#include <stdint.h>
//https://wiki.nesdev.com/w/index.php/Mapper
class Mapper
{
public:
	Mapper(uint8_t prgBanks, uint8_t charBanks);
	~Mapper();

public:
	virtual bool cpuMapRead(uint16_t addr, uint32_t& mapped_addr) = 0;
	virtual bool cpuMapWrite(uint16_t addr, uint32_t& mapped_addr) = 0;

	virtual bool PPUuMapRead(uint16_t addr, uint32_t& mapped_addr) = 0;
	virtual bool PPUMapWrite(uint16_t addr, uint32_t& mapped_addr) = 0;

protected:
	uint8_t _PRGBankAmount;
	uint8_t _CHRBankAmount;
};
