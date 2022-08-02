#pragma once
//set regular types to explicit types
#include <cstdint>
#include "olc6502.h"
#include <array>
#include "ppu.h"

class Cartridge;
class Bus
{
public:
	Bus();
	~Bus();
public:
	//Devices on bus
	olc6502 cpu;
	ppu PictureProccessingUnit;

	std::array<uint8_t, 2048> ram;

public:
	//Bus functions
	void CpuWrite(uint16_t addr, uint8_t data);
	uint8_t CpuRead(uint16_t addr, bool readOnly = false);

	void insertCartridge(Cartridge* newCart);
	void reset();
	void clock();
private:
	Cartridge* _currentCart;
	uint32_t _systemClockCounter;
};

