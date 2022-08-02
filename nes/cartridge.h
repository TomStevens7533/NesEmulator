#pragma once
#include <vector>
#include <string>
#include "Mapper_000.h"
//cartridges can be widly different depending on the fysical hardware on the cartridge(memory, mappers, saving, battery...)
//cart database https://nescartdb.com/
//file format https://wiki.nesdev.com/w/index.php/INES header information and etc...
struct HeaderInfo {
	char name[4];
	uint8_t prg_chunks; //size of PRG ROM in 16 KB units
	uint8_t chr_chunks; //Size of CHR ROM in 8 KB units (Value 0 means the board uses CHR RAM)
	uint8_t mapper1; //Mapper, mirroring, battery, trainer
	uint8_t mapper2; //Mapper, VS/Playchoice, NES 2.0
	uint8_t prg_ram_size; //PRG-RAM size (rarely used extension)
	uint8_t tvStstem1;  //(rarely used extension)
	uint8_t tvSystem2; //(rarely used extension)
	char padding[5]; //should ba all zeros but some rippers but their name into it
};


class Cartridge
{
public:
	Cartridge(const std::string& fileName);
	~Cartridge();

	//Is connected to system
	//Communicate with Main bus
	bool CpuWrite(uint16_t addr, uint8_t data);
	bool CpuRead(uint16_t addr,uint8_t& data);
	//Communicate with PPU bus
	bool PPUWrite(uint16_t addr, uint8_t data);
	bool PPURead(uint16_t addr, uint8_t& data);
private:
	//we dont know how large the memory is we will know it when we read the ROM file
	std::vector<uint8_t> _PRGMemory;
	std::vector<uint8_t> _CHARMemory;

	uint8_t _MapperID = 0;		//which mapper are we using?
	uint8_t _PRGBankAmount = 0;	//How man PRG memory banks are there?
	uint8_t _CharBankAmount = 0;//How many char memory banks are there?

	Mapper* _pMapper; //Current mapper in use


};

