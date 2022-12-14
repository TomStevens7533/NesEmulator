#pragma once
#include <string>
#include <vector>
#include <map>

class Bus;
class olc6502
{
public:
	olc6502();
	~olc6502();

	void connectBus(Bus* n);


	//Addressing Modes
	uint8_t IMP();	uint8_t IMM();
	uint8_t ZP0();	uint8_t ZPX();
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();
	uint8_t ABY();	uint8_t IND();
	uint8_t IZX();	uint8_t IZY();

	//opcodes
	uint8_t ADC(); uint8_t AND(); uint8_t ASL();uint8_t BCC();
	uint8_t BCS(); uint8_t BEQ(); uint8_t BIT();uint8_t BMI();
	uint8_t BNE(); uint8_t BPL(); uint8_t BRK();uint8_t BVC();
	uint8_t BVS(); uint8_t CLC(); uint8_t CLD();uint8_t CLI();
	uint8_t CLV(); uint8_t CMP(); uint8_t CPX();uint8_t CPY();
	uint8_t DEC(); uint8_t DEX(); uint8_t DEY();uint8_t EOR();
	uint8_t INC(); uint8_t INX(); uint8_t INY();uint8_t JMP();
	uint8_t JSR(); uint8_t LDA(); uint8_t LDX();uint8_t LDY();
	uint8_t LSR(); uint8_t NOP(); uint8_t ORA();uint8_t PHA();
	uint8_t PHP(); uint8_t PLA(); uint8_t PLP();uint8_t ROL();
	uint8_t ROR(); uint8_t RTI(); uint8_t RTS();uint8_t SBC();
	uint8_t SEC(); uint8_t SED(); uint8_t SEI();uint8_t STA();
	uint8_t STX(); uint8_t STY(); uint8_t TAX();uint8_t TAY();
	uint8_t TSX(); uint8_t TXA(); uint8_t TXS();uint8_t TYA();

	//catch all illegal opcodes
	uint8_t XXX();

	void clock(); //indicate we want one cycle to occur
	void reset(); //reset
	void irq();	 //interupt
	void nmi();	//nonmaskable interupt


	bool complete();

	bool IsComplete;

	uint8_t fetch();		//fetch data from appropriate source
	uint8_t fetched = 0x00; //stores fetched data
	
	uint16_t addr_abs = 0x0000; //depending on adressing mode store memory address
	uint16_t addr_rel = 0x00;	//relative address jump can only jump so fat
	uint8_t opcode = 0x00;		//store current opcode
	uint8_t cycles = 0;			//cycles left for the duration of the instuction



public:
	//Flags
	enum FLAGS6502
	{
		C = (1 << 0),  //carry bit
		Z = (1 << 1),  //zero
		I = (1 << 2),  //disable interrupts not implemented
		D = (1 << 3),  //Decial mode 
		B = (1 << 4),  //break
		U = (1 << 5),  //unused 
		V = (1 << 6),  //overflow
		N = (1 << 7),  //negative
	};

	std::map<uint16_t, std::string> disassemble(uint16_t nStart, uint16_t nStop);

	//Registers
	uint8_t a = 0x00;		//Accumulator regiters
	uint8_t x = 0x00;		//X Registers
	uint8_t y = 0x00;		//Y Registers
	uint8_t stkp = 0x00;	//stack pointer(points to loc on bus)
	uint16_t pc = 0x00;		//program counter
	uint8_t statusRegister = 0x00;  //status registers ()

private:

	Bus* m_Bus = nullptr;
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool readOnly = false);

	struct INSTRUCTION
	{
		std::string name; //stores name (mostly used for dissasembly)
		uint8_t(olc6502::*operate)() = nullptr;  //function pointer to opcode function(called operate takes 0 arguments return uint8_t)
		uint8_t(olc6502::*addrmode)() = nullptr;  //function pointer to opcode adressing mode(called operate takes 0 arguments return uint8_t)
		uint8_t cycles = 0;

	};
	//lookup table for opcodes
	std::vector<INSTRUCTION> lookup;

	uint8_t GetFlag(FLAGS6502 f);
	void SetFlag(FLAGS6502 f, bool v);
	
};

