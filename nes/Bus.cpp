#include "Bus.h"
#include "cartridge.h"

Bus::Bus()
{
	//clear ram content on startup
	for (auto& loc : ram) loc = 0x00;

	//connect cpu to bus
	cpu.connectBus(this);
}

Bus::~Bus()
{

}

void Bus::CpuWrite(uint16_t addr, uint8_t data)
{
	if (_currentCart->CpuWrite(addr, data)) {
		//when bus is written to the cpu the cartridge gets to decide if its forthe cartridge or not if not ppu or ram does not get updated
		//TODO we can change this to normal address bounds
	}
	//check if addr falls into device range
	else if(addr >= 0x0000 && addr <= 0xFFFF) //RAM range
		ram[addr & 0x7FF] = data; //also mirroring binary MODULO to determine RAM quadrant
	else if (addr >= 0x2000 && addr <= 0x3FFF) { //PPU write also uses mirroring  8 bits
		PictureProccessingUnit.PPUWrite(addr & 0x007, data); //https://wiki.nesdev.com/w/index.php/PPU_registers
	}
}

uint8_t Bus::CpuRead(uint16_t addr, bool readOnly /*= false*/)
{
	uint8_t data = 0x00;

	if (_currentCart->CpuRead(addr, data)) {
		//when bus is written to the cpu the cartridge gets to decide if its forthe cartridge or not if not ppu or ram does not get updated
		//TODO we can change this to normal address bounds
	}
	//check if addr falls into device range
	if (addr >= 0x0000 && addr <= 0x1FFF) { //see if adress is in 8k adressable RAM memory
		//do mirroring (physically only 2K RAM on hardware but 8k is adressable so 4 adresses lead to the same data)
			return ram[addr & 0x7FF]; //Get memory from the different quarants depending using binary MODULO(%)  because there is only 2K of REAL MEMORY
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF) { //PPU READ also uses mirroring is mirrored in every 8 bits
		return PictureProccessingUnit.PPURead(addr & 0x007, readOnly); //https://wiki.nesdev.com/w/index.php/PPU_registers
	}
	else	
		return data;


	//implement mirroring
}

void Bus::insertCartridge(Cartridge* newCart)
{
	_currentCart = newCart; //connect bus to cartridge
	PictureProccessingUnit.SetCartridge(newCart); //connect ppu to cartridge so it access 

}

void Bus::reset()
{
	cpu.reset();
	_systemClockCounter = 0;
}

void Bus::clock()
{
	PictureProccessingUnit.clock();
	//cpu clock runs 3 times slower than ppu clock

	if(_systemClockCounter % 3 == 0)
		cpu.clock();

	_systemClockCounter++;
}

