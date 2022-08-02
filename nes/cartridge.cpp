#include "cartridge.h"
#include <fstream>
Cartridge::Cartridge(const std::string& fileName)
{
	HeaderInfo info;

	std::ifstream ifs;
	ifs.open(fileName, std::ifstream::binary);
	if (ifs.is_open()) {

		//reading header
		ifs.read((char*)&info, sizeof(HeaderInfo));
		//trainer data
		if (info.mapper1 & 0x04) //if present seek trainer data 512 bytes 0 if not in header
			ifs.seekg(512, std::ios_base::cur); //ignore it currently
		
		//mapper ID
		_MapperID = ((info.mapper2 >> 4) << 4) | (info.mapper1 >> 4);

		//differnt types of INES files
		uint8_t fileType = 1;
		switch (fileType)
		{
		case 0:
			break;
		case 1:
			//Read in PRG memory depending on amount of chunks
			_PRGBankAmount = info.prg_chunks;
			_PRGMemory.resize(_PRGBankAmount * 16384); //16kb each bank
			ifs.read((char*)_PRGMemory.data(), _PRGMemory.size());

			//read in char memory depending on chunks
			_CharBankAmount = info.chr_chunks;
			_CHARMemory.resize(_CharBankAmount * 8192); //8kb each bank
			ifs.read((char*)_CHARMemory.data(), _CHARMemory.size());
			break;
		case 2:
			break;
		}

		//load correct mapper based on mapper ID
		switch (_MapperID)
		{
		default:
			_pMapper = new Mapper_000(_PRGBankAmount, _CharBankAmount);
		}

		ifs.close();
		
	}
}

Cartridge::~Cartridge()
{

}

bool Cartridge::CpuWrite(uint16_t addr, uint8_t data)
{
	return false;
}

bool Cartridge::CpuRead(uint16_t addr, uint8_t& data)
{
	uint32_t mapped_addr = 0;
	if (_pMapper->cpuMapRead(addr, mapped_addr)) {
		data = _PRGMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::PPUWrite(uint16_t addr, uint8_t data)
{
	return false;

}

bool Cartridge::PPURead(uint16_t addr, uint8_t& data)
{
	return false;

}

