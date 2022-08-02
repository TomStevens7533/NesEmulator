#pragma once
#include "Mapper.h"
//https://wiki.nesdev.com/w/index.php?title=NROM
class Mapper_000 :
    public Mapper
{
public:
	Mapper_000(uint8_t prgBanks, uint8_t charBanks);
	~Mapper_000();

	virtual bool cpuMapRead(uint16_t addr, uint32_t& mapped_addr) override;
	virtual bool cpuMapWrite(uint16_t addr, uint32_t& mapped_addr) override;

	virtual bool PPUuMapRead(uint16_t addr, uint32_t& mapped_addr) override;
	virtual bool PPUMapWrite(uint16_t addr, uint32_t& mapped_addr) override;
};

