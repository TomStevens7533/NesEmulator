#include "ppu.h"
#include "cartridge.h"

ppu::ppu()
{
	//add all nes allowed color information to pallete array
	//https://wiki.nesdev.org/w/index.php/PPU_palettes

	palScreen[0x00] = olc::Pixel(84, 84, 84);
	palScreen[0x01] = olc::Pixel(0, 30, 116);
	palScreen[0x02] = olc::Pixel(8, 16, 144);
	palScreen[0x03] = olc::Pixel(48, 0, 136);
	palScreen[0x04] = olc::Pixel(68, 0, 100);
	palScreen[0x05] = olc::Pixel(92, 0, 48);
	palScreen[0x06] = olc::Pixel(84, 4, 0);
	palScreen[0x07] = olc::Pixel(60, 24, 0);
	palScreen[0x08] = olc::Pixel(32, 42, 0);
	palScreen[0x09] = olc::Pixel(8, 58, 0);
	palScreen[0x0A] = olc::Pixel(0, 64, 0);
	palScreen[0x0B] = olc::Pixel(0, 60, 0);
	palScreen[0x0C] = olc::Pixel(0, 50, 60);
	palScreen[0x0D] = olc::Pixel(0, 0, 0);
	palScreen[0x0E] = olc::Pixel(0, 0, 0);
	palScreen[0x0F] = olc::Pixel(0, 0, 0);

	palScreen[0x10] = olc::Pixel(152, 150, 152);
	palScreen[0x11] = olc::Pixel(8, 76, 196);
	palScreen[0x12] = olc::Pixel(48, 50, 236);
	palScreen[0x13] = olc::Pixel(92, 30, 228);
	palScreen[0x14] = olc::Pixel(136, 20, 176);
	palScreen[0x15] = olc::Pixel(160, 20, 100);
	palScreen[0x16] = olc::Pixel(152, 34, 32);
	palScreen[0x17] = olc::Pixel(120, 60, 0);
	palScreen[0x18] = olc::Pixel(84, 90, 0);
	palScreen[0x19] = olc::Pixel(40, 114, 0);
	palScreen[0x1A] = olc::Pixel(8, 124, 0);
	palScreen[0x1B] = olc::Pixel(0, 118, 40);
	palScreen[0x1C] = olc::Pixel(0, 102, 120);
	palScreen[0x1D] = olc::Pixel(0, 0, 0);
	palScreen[0x1E] = olc::Pixel(0, 0, 0);
	palScreen[0x1F] = olc::Pixel(0, 0, 0);

	palScreen[0x20] = olc::Pixel(236, 238, 236);
	palScreen[0x21] = olc::Pixel(76, 154, 236);
	palScreen[0x22] = olc::Pixel(120, 124, 236);
	palScreen[0x23] = olc::Pixel(176, 98, 236);
	palScreen[0x24] = olc::Pixel(228, 84, 236);
	palScreen[0x25] = olc::Pixel(236, 88, 180);
	palScreen[0x26] = olc::Pixel(236, 106, 100);
	palScreen[0x27] = olc::Pixel(212, 136, 32);
	palScreen[0x28] = olc::Pixel(160, 170, 0);
	palScreen[0x29] = olc::Pixel(116, 196, 0);
	palScreen[0x2A] = olc::Pixel(76, 208, 32);
	palScreen[0x2B] = olc::Pixel(56, 204, 108);
	palScreen[0x2C] = olc::Pixel(56, 180, 204);
	palScreen[0x2D] = olc::Pixel(60, 60, 60);
	palScreen[0x2E] = olc::Pixel(0, 0, 0);
	palScreen[0x2F] = olc::Pixel(0, 0, 0);

	palScreen[0x30] = olc::Pixel(236, 238, 236);
	palScreen[0x31] = olc::Pixel(168, 204, 236);
	palScreen[0x32] = olc::Pixel(188, 188, 236);
	palScreen[0x33] = olc::Pixel(212, 178, 236);
	palScreen[0x34] = olc::Pixel(236, 174, 236);
	palScreen[0x35] = olc::Pixel(236, 174, 212);
	palScreen[0x36] = olc::Pixel(236, 180, 176);
	palScreen[0x37] = olc::Pixel(228, 196, 144);
	palScreen[0x38] = olc::Pixel(204, 210, 120);
	palScreen[0x39] = olc::Pixel(180, 222, 120);
	palScreen[0x3A] = olc::Pixel(168, 226, 144);
	palScreen[0x3B] = olc::Pixel(152, 226, 180);
	palScreen[0x3C] = olc::Pixel(160, 214, 228);
	palScreen[0x3D] = olc::Pixel(160, 162, 160);
	palScreen[0x3E] = olc::Pixel(0, 0, 0);
	palScreen[0x3F] = olc::Pixel(0, 0, 0);

}

ppu::~ppu()
{

}

void ppu::CpuWrite(uint16_t addr, uint8_t data)
{
	uint8_t dataCPU;

	switch (addr)
	{
	case 0x0000: //CONTROL
		break;
	case 0x0001: //MASK
		break;
	case 0x0002: //STATUS
		break;
	case 0x0003: //OAM ADRESS
		break;
	case 0x0004: //OAM DATA
		break;
	case 0x0005: //SCROLL
		break;
	case 0x0006: //PPU ADDRESS
		break;
	case 0x0007:  //PPU DATA
		break;
	}
}

uint8_t ppu::CpuRead(uint16_t addr, bool readOnly /*= false*/) //https://wiki.nesdev.com/w/index.php/PPU_registers#Summary
{
	uint8_t data =0;

	switch (addr)
	{
	case 0x0000: //CONTROL
		break;
	case 0x0001: //MASK
		break;
	case 0x0002: //STATUS
		break;
	case 0x0003: //OAM ADRESS
		break;
	case 0x0004: //OAM DATA
		break;
	case 0x0005: //SCROLL
		break;
	case 0x0006: //PPU ADDRESS
		break;
	case 0x0007:  //PPU DATA
		break;
	}

	return data;
}

void ppu::PPUWrite(uint16_t addr, uint8_t data)
{
	addr &= 0x3FFF;

	if (_currentCart->PPUWrite(addr, data)) {

	}
}

uint8_t ppu::PPURead(uint16_t addr, bool readOnly /*= false*/)
{
	uint8_t data = 0x00;
	addr &= 0x3FFF;

	if (_currentCart->PPUWrite(addr, data)) {

	}
	return data;
}

void ppu::SetCartridge( Cartridge* newCart)
{
	_currentCart = newCart;
}

void ppu::clock()
{ //clock cylcle still needs implementation
	//advance renderer never stop clockinng
	sprScreen.SetPixel(cycle - 1, scaneline, palScreen[(rand() % 0x30)]);

	cycle++;
	//scrolling across screen x and y direction
	if (cycle >= 341) {
		cycle = 0;
		scaneline++;
		if (scaneline >= 261) {
			scaneline = -1;
			frame_complete = true;
		}
	}
}

olc::Sprite& ppu::GetScreen()
{
	return sprScreen;
}

olc::Sprite& ppu::GetNameTable(uint8_t index)
{
	return sprNameTable[index];
}

olc::Sprite& ppu::GetPatternTable(uint8_t index)
{
	return sprPatternTable[index];
}

