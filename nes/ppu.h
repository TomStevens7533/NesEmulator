#pragma once
#include <stdint.h>
#include "olcPixelGameEngine.h"

class Cartridge;
class ppu
{
public:
	ppu();
	~ppu();


	//Communicate with Main bus
	void CpuWrite(uint16_t addr, uint8_t data);
	uint8_t CpuRead(uint16_t addr, bool readOnly = false);
	//Communicate with PPU bus
	void PPUWrite(uint16_t addr, uint8_t data);
	uint8_t PPURead(uint16_t addr, bool readOnly = false);

	void SetCartridge(Cartridge* newCart);
	void clock();

private:
	Cartridge* _currentCart;
	uint8_t _tblName[2][1024]; // nametable 2 kilobytes(1 full nametable is 1 kilobyte nes is capable of 2 full nametables)
	//eacht byte in the nametable controls one 8x8 pixel charachter cell, nametable has (30 rows and 32 tiles) = 960 bytes the rest is used by each nametables attribute table.
	//but all rows and collums(1 entry 8x8 pixel cell) makes a full screen(256x240)
	//NES can adress 4 nametables so mirroring  https://wiki.nesdev.com/w/index.php/PPU_nametables
	uint8_t _tblPalette[32]; //color informations

private:
	//used for debug
	olc::Pixel palScreen[0x40]; //colors nes is capable of displaying | nes palletes
	olc::Sprite sprScreen = { 256, 240 }; //full screen output
	olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256,240) }; //depication of the nametables
	olc::Sprite sprPatternTable[2] = { olc::Sprite(128,128), olc::Sprite(128, 128) }; //depication fo the pattertables
public:
	//debugging uitilies
	olc::Sprite& GetScreen();
	olc::Sprite& GetNameTable(uint8_t index);
	olc::Sprite& GetPatternTable(uint8_t index);
	bool frame_complete = false; //when frame is complete

private:
	int16_t scaneline = 0; //which row of the screen
	int16_t cycle; //which collumn of the screen


};
