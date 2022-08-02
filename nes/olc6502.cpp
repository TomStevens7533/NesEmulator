#include "olc6502.h"
#include <stdint.h>
#include "Bus.h"

olc6502::olc6502()
{
	using a = olc6502;

	//16x16 entries 256 instructions
	//initializer list of initializer lists 
	lookup =
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
}

olc6502::~olc6502()
{

}

void olc6502::connectBus(Bus* n)
{
	m_Bus = n;
}
//transfer stack pointer to x register
uint8_t olc6502::TSX()
{
	x = stkp;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}
//transfer x register to accumulator
uint8_t olc6502::TXA()
{
	a = x;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}
//transfer x register to stackpointer
uint8_t olc6502::TXS()
{
	stkp = x;
	return 0;
}
//transfer y register to accumulator
uint8_t olc6502::TYA()
{
	a = y;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t olc6502::XXX()
{
	return 0;
}

void olc6502::clock()
{
	//the clock is not accurate to the real 6502 clock
	//we do everything at once
	//normally function take multiple cycles to complete

	if (cycles == 0)
	{
		opcode = read(pc);
		pc++;

		cycles = lookup[opcode].cycles;

		//function calls can return extra cycles 

		uint8_t add_cycles1 = (this->*lookup[opcode].addrmode)(); //calls addressing function in function pointer 
		uint8_t add_cycles2 = (this->*lookup[opcode].operate)(); //calls opcode function in function pointer 

		cycles += (add_cycles1 & add_cycles2);	//only add extra cycles if adressing mode and opcode require it

	}
	else {
		cycles--;
	}
}


void olc6502::write(uint16_t addr, uint8_t data)
{
	m_Bus->CpuWrite(addr, data);
}

uint8_t olc6502::read(uint16_t addr, bool readOnly /*= false*/)
{
	return m_Bus->CpuRead(addr, readOnly);
}

//flag get and set
uint8_t olc6502::GetFlag(FLAGS6502 f)
{
	return ((statusRegister & f) > 0) ? 1 : 0;
}

void olc6502::SetFlag(FLAGS6502 f, bool v)
{
	if(v)
		statusRegister |= f; //or assingment
	else
		statusRegister &= ~f; //and assingment not
}
//reset and interupt function
//reset to know state
void olc6502::reset()
{
	a = 0;
	x = 0;
	y = 0;
	stkp = 0xFD;
	statusRegister = 0x00 | U;

	// //hard coded memory adress when reset is called the 8502 knows it needs to look into this hard coded adress
	addr_abs = 0xFFFC; //Data at this location can be set by the programmer when compiling their program
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) | 0;

	//set internal variables to 0
	addr_abs = 0x000;
	addr_rel = 0x000;
	fetched = 0x00;


	cycles = 8; //interrupts take time 
}



void olc6502::irq()
{
	//gets ignored if interrupt bit is NOT set
	if (GetFlag(I) == 0)
	{
		//interrupt dont reset the progam we run a specific piece of code to service our program
		//we dont want to destroy the entire program state
		//first thing we write is the current program counter(16 bits) so it takes two write operations
		write(0x0100 + stkp, (pc >> 8) & 0x00FF);
		stkp--;
		write(0x0100 + stkp, pc & 0x00FF);
		stkp--;
		//we also write the status register
		//some flags are set to indicate an interrupt has occured 
		SetFlag(B, 0);
		SetFlag(U, 1);
		SetFlag(I, 1);
		write(0x0100 + stkp, statusRegister);
		stkp--;

		//set the program counter to a know location set by the programmer to handle the fact the interrupt has occured (the code that services our program)
		addr_abs = 0xFFFE; //hard coded adress is read to get the value of the new program counter
		uint16_t lo = read(addr_abs + 0);
		uint16_t hi = read(addr_abs + 1);
		pc = (hi << 8) | lo;

		cycles = 7; //interrupt takes time


	}
}
//non maskable interrupt
void olc6502::nmi()
{
	//is totally the same as a normal interrupt but nothing can stop it from occuring
	// 
	//interrupt dont reset the progam we run a specific piece of code to service our program
	//we dont want to destroy the entire program state
	//first thing we write is the current program counter(16 bits) so it takes two write operations
	write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp, pc & 0x00FF);
	stkp--;
	//we also write the status register
	//some flags are set to indicate an interrupt has occured 
	SetFlag(B, 0);
	SetFlag(U, 1);
	SetFlag(I, 1);
	write(0x0100 + stkp, statusRegister);
	stkp--;

	//set the program counter to a know location set by the programmer to handle the fact the interrupt has occured (the code that services our program)
	addr_abs = 0xFFFE; //hard coded adress is read to get the value of the new program counter
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;

	cycles = 7; //interrupt takes time
}

//Adressing modes
//this changes the addr_abs and addr_rel and are fundamentally the only things we really care about 
//that points to the location in the adressable space where the data the opcode is going to compute resides
//http://wiki.nesdev.com/w/index.php/CPU_addressing_modes

uint8_t olc6502::IMP()
{
	//implied
	//no additional data is required
	//we will target the accumulator
	fetched = a;
	return 0;
}

uint8_t olc6502::IMM()
{
	//immediate
	addr_abs = pc++;
	return 0;
}

uint8_t olc6502::ZP0()
{
	//zero page adressing
	//pages are conceptial way of organizing memory
	//16 bits for memory adress 0xFF55
	//high byte can be seen as the page 0XFF
	//Low byte can be seen as the offset of that page 0XFF55
	//Total memory can be seen as 256 pages with 256 bytes(offset) each
	addr_abs = (read(pc));
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t olc6502::ZPX()
{
	//zero page indexing with x offset
	//pc adress supplied with the instruction
	addr_abs = read(pc) + x;
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t olc6502::ZPY()
{
	//zero page indexing with y offset
	//pc adress supplied with the instruction
	addr_abs = read(pc) + y;
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t olc6502::ABS()
{
	//absolute full 16 adress is loaded in and used
	
	//read return 8bit
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t olc6502::ABX()
{
	//absolute with x offset
	//read return 8bit
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	//if absolute address with x idicates to a new page
	//tell system we may need another clock cycle if we change page
	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;

	return 0;
}

uint8_t olc6502::ABY()
{
	
	//read return 8bit
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	//if absolute address with x idicates to a new page
	//tell system we may need another clock cycle if we change page
	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;

	return 0;
}

uint8_t olc6502::IND()
{
	//Indirect adressing mode 
	//16 bit adress is read to get the actual 16 bit adress 
	//this instruction is unusual cause it has a bug in the hardware that we have the emulate ourselves
	//if the low byte is 0xFF then to read the hight byte we need to to cross a page boundary but this doesnt work in the 8502 chip instead it wraps back around in the page giving an ivalid adress 

	//assemble 16 bit adress
	uint16_t ptr_lo = read(pc);
	pc++;
	uint16_t ptr_hi = read(pc);
	pc++;

	//create *pointer*
	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo == 0x00FF) // Simulate page boundary hardware bug other bugs can be found at http://nesdev.com/6502bugs.txt
	{
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
	}
	else // Behave normally
	{
		//Read 16bit data located at pointer assign it to new address(addr_abs)
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
	}

	return 0;

}

uint8_t olc6502::IZX()
{
	//Address mode indirect X
	// The supplied 8-bit address is offset by X Register to index
	// a location in page 0x00. The actual 16-bit address is read from this location

	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);


	//read actual adress
	addr_abs = (hi << 8) | lo;

	return 0;
	
}

uint8_t olc6502::IZY()
{
	//Address mode indirect Y  works different from IZX
	// The supplied 8-bit address is offset by Y Register to index
	// a location in page 0x00. The actual 16-bit address is read from this location

	uint16_t t = read(pc); //we read a single byte which is an offset in the zeropage
	pc++;

	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo; //add shift hi to hi location and add low to complete actual adress
	addr_abs += y; //we offset the actual adress with the contents in the y registers


	//we may cross a page boundary with the acutual adress with y offset if this happens indicate that extra clock cycle is needed
	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1; //page crossing has occured indicate extra clock cycle
	else
		return 0;
}
uint8_t olc6502::REL()
{
	//Relative adressing mode
	//only implies to branching instructions can only jump to a location in the vicinity cannot jump any further away than 127 memory locations
	//the adress must reside within -128 to +127 of the branch instruction so we need to check for signed numbers
	//because its relative and not absolute we store it in a seperate varaible
	addr_rel = read(pc);
	pc++;

	//signed numbers have their first bit(7) set to 1
	if (addr_rel & 0x80) //check for signed bit
		addr_rel |= 0xFF00; //if true set all high bits to 1 to make sure the binary aritmethic works out 
	return 0;

}


uint8_t olc6502::fetch()
{
	//check if current addressing mode 
	//fetch data for all adressing modes except for implied adressing mode(it fetches nothing)
	if (!(lookup[opcode].addrmode == &olc6502::IMP))
		fetched = read(addr_abs);
	return fetched;
}

//instructions
uint8_t olc6502::AND()
{
	fetch();  //first fetch data
	a = a & fetched; //do operation
	//setting statusRegisters
	SetFlag(Z, a == 0x00); //set zero flag if all bits are zero
	SetFlag(N, a & 0x800); //if last bit is set to 1 set negative flag
	return 1; //AND instruction needs 1 more cycle
}

//branch with carry
uint8_t olc6502::BCS()
{
	if (GetFlag(C) == 1) //if carry flag is set
	{
		cycles++; //add extra cycle
		addr_abs = pc + addr_rel; //absolute adress is program counter + address offset

		if ((addr_abs & 0xFF00) != (pc & 0xFF00)) //if the branch needs to cross page boundary extra cycle is needed
			cycles++; //so branch can add 2 additional cycles

		pc = addr_abs;
	}
	return 0;
}
//branch if carry clear
uint8_t olc6502::BCC()
{
	if (GetFlag(C) == 0) //if carry flag is not set
	{
		cycles++; //add extra cycle
		addr_abs = pc + addr_rel; //absolute adress is program counter + address offset

		if ((addr_abs & 0xFF00) != (pc & 0xFF00)) //if the branch needs to cross page boundary extra cycle is needed
			cycles++; //so branch can add 2 additional cycles

		pc = addr_abs;
	}
	return 0;
}
//aritmethic shift left
uint8_t olc6502::ASL()
{
	fetch();
	uint16_t temp = (fetched << 1);
	//set apporoptiate flags
	SetFlag(C, (temp & 0xFF00) > 0);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	//if implied shift accumulator
	if (lookup[opcode].addrmode == &olc6502::IMP)
		a = temp & 0x00FF;
	else
		//write shifted data to memory
		write(addr_abs, temp & 0x00FF);
	return 0;
}
//aritmethic shift right
uint8_t olc6502::LSR()
{
	fetch();
	uint16_t temp = (fetched >> 1);
	//set apporoptiate flags
	SetFlag(C, (temp & 0xFF00) > 0);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	//if implied shift accumulator
	if (lookup[opcode].addrmode == &olc6502::IMP)
		a = temp & 0x00FF;
	else
		//write shifted data to memory
		write(addr_abs, temp & 0x00FF);
	return 0;
}


//branch if equal
uint8_t olc6502::BEQ()
{
	if (GetFlag(Z) == 1) //if zero flag is set
	{
		cycles++; //add extra cycle
		addr_abs = pc + addr_rel; //absolute adress is program counter + address offset

		if ((addr_abs & 0xFF00) != (pc & 0xFF00)) //if the branch needs to cross page boundary extra cycle is needed
			cycles++; //so branch can add 2 additional cycles

		pc = addr_abs;
	}
	return 0;
}

//branch if not equal
uint8_t olc6502::BNE()
{
	if (GetFlag(Z) == 0) //if zero flag is not set
	{
		cycles++; //add extra cycle
		addr_abs = pc + addr_rel; //absolute adress is program counter + address offset

		if ((addr_abs & 0xFF00) != (pc & 0xFF00)) //if the branch needs to cross page boundary extra cycle is needed
			cycles++; //so branch can add 2 additional cycles

		pc = addr_abs;
	}
	return 0;
}
//branch if positive
uint8_t olc6502::BPL()
{
	if (GetFlag(N) == 0) //if negative flag is  set
	{
		cycles++; //add extra cycle
		addr_abs = pc + addr_rel; //absolute adress is program counter + address offset

		if ((addr_abs & 0xFF00) != (pc & 0xFF00)) //if the branch needs to cross page boundary extra cycle is needed
			cycles++; //so branch can add 2 additional cycles

		pc = addr_abs;
	}
	return 0;
}
//branch if overflow
uint8_t olc6502::BVC()
{
	if (GetFlag(V) == 1) //if negative flag is  set
	{
		cycles++; //add extra cycle
		addr_abs = pc + addr_rel; //absolute adress is program counter + address offset

		if ((addr_abs & 0xFF00) != (pc & 0xFF00)) //if the branch needs to cross page boundary extra cycle is needed
			cycles++; //so branch can add 2 additional cycles

		pc = addr_abs;
	}
	return 0;
}
//branch if not overflow
uint8_t olc6502::BVS()
{
	if (GetFlag(V) == 0) //if negative flag is  set
	{
		cycles++; //add extra cycle
		addr_abs = pc + addr_rel; //absolute adress is program counter + address offset

		if ((addr_abs & 0xFF00) != (pc & 0xFF00)) //if the branch needs to cross page boundary extra cycle is needed
			cycles++; //so branch can add 2 additional cycles

		pc = addr_abs;
	}
	return 0;
}
//branch if negative
uint8_t olc6502::BMI()
{
	if (GetFlag(N) == 1) //if negative flag is  set
	{
		cycles++; //add extra cycle
		addr_abs = pc + addr_rel; //absolute adress is program counter + address offset

		if ((addr_abs & 0xFF00) != (pc & 0xFF00)) //if the branch needs to cross page boundary extra cycle is needed
			cycles++; //so branch can add 2 additional cycles

		pc = addr_abs;
	}
	return 0;
}

//tests specfic bits in the conten of the adress specified and sets flag accoudingly(Z,N,V)
uint8_t olc6502::BIT()
{
	fetch();
	uint8_t temp = fetched & a;
	SetFlag(N, fetched == 0x00);
	SetFlag(N, fetched & (1 << 4));
	SetFlag(V, fetched & (1 << 3));
	return 0;
}

//clear carry flag
uint8_t olc6502::CLC()
{
	SetFlag(C, false); 
	return 0;
}
//clear interrupt flag
uint8_t olc6502::CLI()
{
	SetFlag(I, false);
	return 0;
}
//clear overflow flag
uint8_t olc6502::CLV()
{
	SetFlag(V, false);
	return 0;
}

uint8_t olc6502::CMP()
{
	fetch();
	uint8_t temp = a - fetched;
	SetFlag(C, a >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000); //(temp & 0x00FF) remove HI byte check if equal to zero
	SetFlag(N, temp & 0x0080);
	return 1;
}

uint8_t olc6502::CPX()
{
	fetch();
	uint8_t temp = x - fetched;
	SetFlag(C, x >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000); //(temp & 0x00FF) remove HI byte check if equal to zero
	SetFlag(N, temp & 0x0080);
	return 1;
}

uint8_t olc6502::CPY()
{
	fetch();
	uint8_t temp = y - fetched;
	SetFlag(C, y >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000); //(temp & 0x00FF) remove HI byte check if equal to zero
	SetFlag(N, temp & 0x0080);
	return 1;
}
//decrease (Z,N)
uint8_t olc6502::DEC()
{
	fetch();
	uint8_t temp = fetched - 1;
	write(addr_abs, temp);
	SetFlag(N, temp & 0x0080); //temp & 0x0080 return 0 if temp positive and a postive number when temp negative
	SetFlag(Z, temp == 0x00);
	return 0;
}
//decrement X
uint8_t olc6502::DEX()
{
	x = x - 1;
	SetFlag(N, x & 0x0080);
	SetFlag(Z, x == 0x00);
	return 0;
}
//decrement y
uint8_t olc6502::DEY()
{
	y = y - 1;
	SetFlag(N, y & 0x0080);
	SetFlag(Z, y == 0x00);
	return 0;
}
//exclusive or
uint8_t olc6502::EOR()
{
	fetch();
	a = a ^ fetched;
	SetFlag(N, a & 0x0080);
	SetFlag(Z, a == 0x00);
	return 1;
}
//increment
uint8_t olc6502::INC()
{
	fetch();
	uint8_t temp = fetched + 1;
	write(addr_abs, temp);
	SetFlag(N, temp & 0x0080);
	SetFlag(Z, temp == 0x00);
	return 0;
}
//increment x
uint8_t olc6502::INX()
{
	x = x + 1;
	SetFlag(N, x & 0x0080);
	SetFlag(Z, x == 0x00);
	return 0;
}
//increment y
uint8_t olc6502::INY()
{
	y = y + 1;
	SetFlag(N, y & 0x0080);
	SetFlag(Z, y == 0x00);
	return 0;
}
//JMP
uint8_t olc6502::JMP()
{
	//set program counter to specified adress
	pc = addr_abs;
	return 0;
}

uint8_t olc6502::JSR()
{
	pc--;

	//write pc stackpointer
	write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	pc = addr_abs;
	return 0;
}
//return from subroutine
uint8_t olc6502::RTS()
{
	stkp++;
	uint16_t temp = read(0x0100 + stkp) >> 8;
	stkp++;
	temp += read(0x0100 + stkp);

	pc = fetched;
	return 0;
}

//Load accumulator
uint8_t olc6502::LDA()
{
	fetch();
	a = fetched;
	SetFlag(N, a & 0x0080);
	SetFlag(Z, a == 0x00);
	return 1; //1 cycle needed
}
//load x register
uint8_t olc6502::LDX()
{
	fetch();
	x = fetched;
	SetFlag(N, x & 0x0080);
	SetFlag(Z, x == 0x00);
	return 1; //1 cycle needed
}
//load y register
uint8_t olc6502::LDY()
{
	fetch();
	y = fetched;
	SetFlag(N, y & 0x0080);
	SetFlag(Z, y == 0x00);
	return 1; //1 cycle needed
}

//breakpoint
uint8_t olc6502::BRK()
{
	//increase program counter //mayne need to increase two times 
	pc++;
	
	//set interrupt flag
	SetFlag(I, 1);

	//interrupt event but with break flag set
	//write pc stackpointer
	write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	//write cpu status to stackpoinre
	SetFlag(B, 1);
	write(0x0100 + stkp, statusRegister);
	stkp--;
	//remove Break flag
	SetFlag(B, 0);

	
	//read program counter back in
	addr_abs = 0xFFFE;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;



	//Reads pc from IRQ/BRK vector in memory
	SetFlag(B, 1);

	//return 7
	return 7;
}


//clear decimal flag
uint8_t olc6502::CLD()
{
	SetFlag(D, false);
	return 0;
}
//addition
//need to be aware of overflow if overflow occurs set overflow flag
// 0 is positive 1 is negative (we look at the significant bit) 	 (carry bit is set to 0 in this example)
//Accumulator | Memory |	 Result      | overflow flag	|  A^R	 |  ~(A^M) 	 |
//	0		  | 0	   |		0		 |		0		   	|	0	 |		1	 |
//	0		  | 0	   |		1		 |		/1/			|	/1/	 |		/1/	 |		can result in overflow if A & M are positive
//	0		  | 1	   |		0		 |		0			|	0	 |		0	 |
//	0		  | 1	   |		1		 |		0			|	1	 |		0	 |
//	1		  | 0	   |		0		 |		0			|	1	 |		0	 |
//	1		  | 0	   |		1		 |		0			|	0	 |		0	 |
//	1		  | 1	   |		0		 |		/1/			|	/1/	 |		/1/	 |		can result in overflow if A & M are negative
//	1		  | 1	   |		1		 |		0			|	0	 |		1	 |
//overflow can only occur in two occasions if the result is different than what A and M holds
//we can determine when overflow can occur with the exclusive OR //V = (A^R) & ~(A^M)
uint8_t olc6502::ADC()
{
	fetch();
	uint16_t temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)GetFlag(C); //perform addition in 16bit domain (cast 8bits to 16 bits)
	SetFlag(C, temp > 255); //set carry bit if most signidicant bit is set
	SetFlag(Z, (temp & 0x00FF) == 0); //set zero flag if zero
	SetFlag(N, temp & 0x80); //set negative flag if the significant bit of the low byte is Set
	SetFlag(V, (((uint16_t)a ^ (uint16_t)temp) & ~((uint16_t)a ^ (uint16_t)fetched)) & 0x0080); //look for overflow in the most significant bit in the low byte
	a = temp & 0x00FF; //store result back into the accumulator
	return 1; //ADC can also require an extra clock cycle

}
//substraction (looks allot like addition but we just need to invert M)  //A = A + -M + 1 +C; (we invert M using two's complement)
uint8_t olc6502::SBC()
{
	fetch();//fetch data;
	uint16_t value = ((uint16_t)fetched) ^ 0x00FF - 1; //Invert bottom 8 bits with exclusive OR operator and - 1 due to two complement

	//exactly the same as the addition
	uint16_t temp = (uint16_t)a + value + (uint16_t)GetFlag(C); //perform substraction in 16bit domain (cast 8bits to 16 bits)
	SetFlag(C, temp > 255); //set carry bit if most signidicant bit is set
	SetFlag(Z, (temp & 0x00FF) == 0); //set zero flag if zero
	SetFlag(N, temp & 0x80); //set negative flag if the significant bit of the low byte is Set
	SetFlag(V, (((uint16_t)a ^ (uint16_t)temp) & ~((uint16_t)a ^ (uint16_t)fetched)) & 0x0080); //look for overflow in the most significant bit in the low byte
	a = temp & 0x00FF; //store result back into the accumulator
	return 1; //ADC can also require an extra clock cycle
}



//set carry flag to true
uint8_t olc6502::SEC()
{
	SetFlag(C, true);
	return 0;
}
//set decimat flag to true
uint8_t olc6502::SED()
{
	SetFlag(D, true);
	return 0;
}
//set intterrupt flag to true
uint8_t olc6502::SEI()
{
	SetFlag(I, true);
	return 0;
}
//store acummulator 
uint8_t olc6502::STA()
{
	write(addr_abs, a);
	return 0;
}
//store x| M = X
uint8_t olc6502::STX()
{
	write(addr_abs, x);
	return 0;
}
//store  y | M = Y
uint8_t olc6502::STY()
{
	write(addr_abs, y);
	return 0;
}
//transfet x to a
uint8_t olc6502::TAX()
{

	x = a;
	SetFlag(Z, x == 0x00); //if content of x is 0
	SetFlag(N, x & 0x80); //if seventh bit is on
	return 0;
}
//transfer y to a
uint8_t olc6502::TAY()
{
	y = a;
	SetFlag(Z, y == 0x00); //if content of x is 0
	SetFlag(N, y & 0x80); //if seventh bit is on
	return 0;
}

//Add item to stack
uint8_t olc6502::PHA()
{
	write(0x0100 + stkp, a); //write to base location(hardware baked hard coded location 0x100) with stackpointer offset
	stkp--;
	return 0;
}

//or operation withc accumulator and memory
uint8_t olc6502::ORA()
{
	fetch();
	a = a | fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

//No Operation
uint8_t olc6502::NOP()
{  //are not made equal based on https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes 
	//for now return 0;
	return 0;
}

//pop accumulator from stack
uint8_t olc6502::PLA()
{
	stkp++;
	a = read(0x0100 + stkp);
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}
//pul processor status from stack
uint8_t olc6502::PLP()
{
	stkp++;
	a = read(0x0100 + stkp);
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}
//rotate left shift either the accumulator or adressed memory to right;
uint8_t olc6502::ROL()
{
	fetch();
	uint8_t temp = (fetched << 1) | GetFlag(C);
	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	//depending on adressing mode write to memory or accumulator
	if (lookup[opcode].addrmode == &olc6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}
//rotate right 
uint8_t olc6502::ROR()
{
	fetch();
	uint8_t temp = (fetched >> 1) | GetFlag(C);
	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	//depending on adressing mode write to memory or accumulator
	if (lookup[opcode].addrmode == &olc6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}
//pushes processor status to stack
uint8_t olc6502::PHP()
{
	write(0x100 + addr_abs, statusRegister | B | U);
	SetFlag(B, 0);
	SetFlag(U, 0);
	stkp--;
	return 0;
}

uint8_t olc6502::RTI()
{
	//when the program has finished servicing an interrupt
	//it will need to return from it
	//and this will restore the state of the processor to how it was before the interrupt has occured

	//read status register from stack
	stkp++;
	statusRegister = read(0x0100 + stkp);
	statusRegister &= ~B;
	statusRegister &= ~U;

	//read previous program counter
	//Restore 16 bit program counter
	stkp++;
	pc = (uint16_t)read(0x0100 + stkp); 
	stkp++;
	pc |= (uint16_t)read(0x0100 + stkp) << 8;
	return 0;


}
//helper functions
bool olc6502::complete()
{
	return cycles == 0;
}


// This is the disassembly function. Its workings are not required for emulation.
// It is merely a convenience function to turn the binary instruction code into
// human readable form. Its included as part of the emulator because it can take
// advantage of many of the CPUs internal operations to do this.
std::map<uint16_t, std::string> olc6502::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	// A convenient utility to convert variables into
	// hex strings because "modern C++"'s method with 
	// streams is atrocious
	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	// Starting at the specified address we read an instruction
	// byte, which in turn yields information from the lookup table
	// as to how many additional bytes we need to read and what the
	// addressing mode is. I need this info to assemble human readable
	// syntax, which is different depending upon the addressing mode

	// As the instruction is decoded, a std::string is assembled
	// with the readable output
	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		// Prefix line with instruction address
		std::string sInst = "$" + hex(addr, 4) + ": ";

		// Read instruction, and get its readable name
		uint8_t opcode = m_Bus->CpuRead(addr, true); addr++;
		sInst += lookup[opcode].name + " ";

		// Get oprands from desired locations, and form the
		// instruction based upon its addressing mode. These
		// routines mimmick the actual fetch routine of the
		// 6502 in order to get accurate data as part of the
		// instruction
		if (lookup[opcode].addrmode == &olc6502::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookup[opcode].addrmode == &olc6502::IMM)
		{
			value = m_Bus->CpuRead(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookup[opcode].addrmode == &olc6502::ZP0)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookup[opcode].addrmode == &olc6502::ZPX)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookup[opcode].addrmode == &olc6502::ZPY)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookup[opcode].addrmode == &olc6502::IZX)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookup[opcode].addrmode == &olc6502::IZY)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookup[opcode].addrmode == &olc6502::ABS)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = m_Bus->CpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookup[opcode].addrmode == &olc6502::ABX)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = m_Bus->CpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookup[opcode].addrmode == &olc6502::ABY)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = m_Bus->CpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookup[opcode].addrmode == &olc6502::IND)
		{
			lo = m_Bus->CpuRead(addr, true); addr++;
			hi = m_Bus->CpuRead(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookup[opcode].addrmode == &olc6502::REL)
		{
			value = m_Bus->CpuRead(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + (int8_t)value, 4) + "] {REL}";
		}

		// Add the formed string to a std::map, using the instruction's
		// address as the key. This makes it convenient to look for later
		// as the instructions are variable in length, so a straight up
		// incremental index is not sufficient.
		mapLines[line_addr] = sInst;
	}

	return mapLines;
}
