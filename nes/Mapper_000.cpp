#include "Mapper_000.h"

Mapper_000::Mapper_000(uint8_t prgBanks, uint8_t charBanks) : Mapper(prgBanks, charBanks)
{

}

Mapper_000::~Mapper_000()
{

}

bool Mapper_000::cpuMapRead(uint16_t addr, uint32_t& mapped_addr)
{
	//not satisfied by anything else on the nes so these adresses need to come from the cartridge
	if (addr >= 0x8000 && addr <= 0xFFFF) {
		//we change the location of were we are reading from our rom file depending on how many banks are supplied in the roms(_prgbankamount represent the amount of 16KB chunks are loaded in)
		mapped_addr = addr & (_PRGBankAmount > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool Mapper_000::cpuMapWrite(uint16_t addr, uint32_t& mapped_addr)
{
	if (addr >= 0x8000 && addr <= 0xFFFF) {
		return true;
	}
	return false;
}

bool Mapper_000::PPUuMapRead(uint16_t addr, uint32_t& mapped_addr)
{//including the patten tables
	if (addr >= 0x0000 && addr <= 0x1FFF) {
		mapped_addr = addr; //No bank switching at all for ppu
		return true;
	}
	return false;
}

bool Mapper_000::PPUMapWrite(uint16_t addr, uint32_t& mapped_addr)
{
	//this is charachter rom(read only memory) so we cant write anything
	return false;
}
