#include "../header/GBCPU.h"
#include "../header/Memory.h"
#include "../header/GenInit.h"

///CPU
GBCPU CPU;
uchar HLm;

void initCPU() {
	CPU.A = 0;
	CPU.B = 0;
	CPU.C = 0;
	CPU.E = 0;
	Flag = 0;
	CPU.H = 0;
	CPU.L = 0;
	CPU.PC = 0;
	CPU.SP = 0;

	CPU.CPUTicks = 0;
}

void OPSelect(){
	///A is the accumulator so its use is implicitly
	ushort adr; //used for 16-bit addresses
	uchar op;   //used for 8-bit values
	
	if (CPU.halt) 
	{
		CPU.CPUTicks += 4;
		return;
	}

	op = readMem(CPU.PC++);
	//UARTprintf("OPCODE: %X @ %X\n", op, CPU.PC-1);
	switch (op)
	{
		case 0x00:
			CPU.CPUTicks += 4;
			break;
		case 0x01:
			CPU.C = OP;
			CPU.B = OP;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x02:  
			adr = BC;
			writeMem(adr, CPU.A);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x03:
			INC2(&CPU.B, &CPU.C);
			break;
		case 0x04:
			INC(&CPU.B);
			break;
		case 0x05:
			DEC(&CPU.B);
			break;
		case 0x06:  
			op = OP;
			CPU.B = op;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x07:
			RLCA();
			break;
		case 0x08: 
			adr = adr16();
			writeMem(adr++, CPU.SP & 0xFF);
			writeMem(adr, CPU.SP >> 8);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x09:
			ADDHL(BC);
			break;
		case 0x0a:
			CPU.A = readMem(BC);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x0b:
			DEC2(&CPU.B,&CPU.C);
			break;
		case 0x0c:
			INC(&CPU.C);
			break;
		case 0x0d:
			DEC(&CPU.C);
			break;
		case 0x0e: 
			op = OP;
			CPU.C = op;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x0f:
			RRCA();
			break;
		case 0x10:
			CPU.CPUTicks += 4;
		case 0x11:  
			CPU.E = OP;
			CPU.D = OP;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x12:
			writeMem(DE, CPU.A);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x13:
			INC2(&CPU.D, &CPU.E);
			break;
		case 0x14:
			INC(&CPU.D);
			break;
		case 0x15:
			DEC(&CPU.D);
			break;
		case 0x16:  
			op = OP;
			CPU.D = op;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x17:
			RLA();
			break;
		case 0x18:  
			op = OP;
			CPU.PC += (signed char)op;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x19:
			ADDHL(DE);
			break;
		case 0x1a:
			CPU.A = readMem(DE);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x1b:
			DEC2(&CPU.D, &CPU.E);
			break;
		case 0x1c:
			INC(&CPU.E);
			break;
		case 0x1d:  
			DEC(&CPU.E);
			break;
		case 0x1e:  
			op = OP;
			CPU.E = op;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x1f: 
			RRA();
			break;
		case 0x20:  
			op = OP;
			if (FlagZ == 0)
			{
				CPU.CPUTicks += 4;
				CPU.PC += (signed char)op;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x21: 
			CPU.L = OP;
			CPU.H = OP;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x22:
			writeMem(HL, CPU.A);
			INC2(&CPU.H, &CPU.L);
			break;
		case 0x23:  
			INC2(&CPU.H, &CPU.L);
			break;
		case 0x24:  
			INC(&CPU.H);
			break;
		case 0x25: 
			DEC(&CPU.H);
			break;
		case 0x26: 
			op = OP;
			CPU.H = op;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x27:
			DAA();
			break;
		case 0x28: 
			op = OP;
			if (FlagZ == 1)
			{
				CPU.PC += (signed char)op;
				CPU.CPUTicks += 4;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x29:  
			ADDHL(HL);
			break;
		case 0x2a:
			CPU.A = readMem(HL);
			INC2(&CPU.H, &CPU.L);
			break;
		case 0x2b:  
			DEC2(&CPU.H, &CPU.L);
			break;
		case 0x2c:  
			INC(&CPU.L);
			break;
		case 0x2d:  
			DEC(&CPU.L);
			break;
		case 0x2e:  
			op = OP;
			CPU.L = op;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x2f:  
			CPL();
			break;
		case 0x30:  
			op = OP;
			if (FlagC == 0)
			{
				CPU.PC += (signed char)op;
				CPU.CPUTicks += 4;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x31:  
			adr = adr16();
			CPU.SP = adr;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x32:
			writeMem(HL, CPU.A);
			DEC2(&CPU.H, &CPU.L);
			break;
		case 0x33:
			CPU.SP++;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x34:
			INCHL();
			break;
		case 0x35:
			DECHL();
			break;
		case 0x36:
			op = OP;
			writeMem(HL, op);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x37:  
			SCF();
			break;
		case 0x38:  
			op = OP;
			if (FlagC == 1)
			{
				CPU.PC += (signed char)op;
				CPU.CPUTicks += 4;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x39:  
			ADDHL(CPU.SP);
			break;
		case 0x3a:
			CPU.A = readMem(HL);
			DEC2(&CPU.H, &CPU.L);
			break;
		case 0x3b:
			CPU.SP--;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x3c:  
			INC(&CPU.A);
			break;
		case 0x3d:  
			DEC(&CPU.A);
			break;
		case 0x3e:  
			op = OP;
			CPU.A = op;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x3f:  
			CCF();
			break;
		case 0x40:  
			CPU.B = CPU.B;
			CPU.CPUTicks += 4;
			break;
		case 0x41:  
			CPU.B = CPU.C;
			CPU.CPUTicks += 4;
			break;
		case 0x42:  
			CPU.B = CPU.D;
			CPU.CPUTicks += 4;
			break;
		case 0x43:  
			CPU.B = CPU.E;
			CPU.CPUTicks += 4;
			break;
		case 0x44:  
			CPU.B = CPU.H;
			CPU.CPUTicks += 4;
			break;
		case 0x45:  
			CPU.B = CPU.L;
			CPU.CPUTicks += 4;
			break;
		case 0x46:
			CPU.B = readMem(HL);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x47:  
			CPU.B = CPU.A;
			CPU.CPUTicks += 4;
			break;
		case 0x48: 
			CPU.C = CPU.B;
			CPU.CPUTicks += 4;
			break;
		case 0x49:  
			CPU.C = CPU.C;
			CPU.CPUTicks += 4;
			break;
		case 0x4a:  
			CPU.C = CPU.D;
			CPU.CPUTicks += 4;
			break;
		case 0x4b:  
			CPU.C = CPU.E;
			CPU.CPUTicks += 4;
			break;
		case 0x4c:  
			CPU.C = CPU.H;
			CPU.CPUTicks += 4;
			break;
		case 0x4d:  
			CPU.C = CPU.L;
			CPU.CPUTicks += 4;
			break;
		case 0x4e:
			CPU.C = readMem(HL);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x4f:  
			CPU.C = CPU.A;
			CPU.CPUTicks += 4;
			break;
		case 0x50: 
			CPU.D = CPU.B;
			CPU.CPUTicks += 4;
			break;
		case 0x51:  
			CPU.D = CPU.C;
			CPU.CPUTicks += 4;
			break;
		case 0x52: 
			CPU.D = CPU.D;
			CPU.CPUTicks += 4;
			break;
		case 0x53: 
			CPU.D = CPU.E;
			CPU.CPUTicks += 4;
			break;
		case 0x54: 
			CPU.D = CPU.H;
			CPU.CPUTicks += 4;
			break;
		case 0x55: 
			CPU.D = CPU.L;
			CPU.CPUTicks += 4;
			break;
		case 0x56:
			CPU.D = readMem(HL);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x57: 
			CPU.D = CPU.A;
			CPU.CPUTicks += 4;
			break;
		case 0x58: 
			CPU.E = CPU.B;
			CPU.CPUTicks += 4;
			break;
		case 0x59: 
			CPU.E = CPU.C;
			CPU.CPUTicks += 4;
			break;
		case 0x5a: 
			CPU.E = CPU.D;
			CPU.CPUTicks += 4;
			break;
		case 0x5b:  
			CPU.E = CPU.E;
			CPU.CPUTicks += 4;
			break;
		case 0x5c:  
			CPU.E = CPU.H;
			CPU.CPUTicks += 4;
			break;
		case 0x5d: 
			CPU.E = CPU.L;
			CPU.CPUTicks += 4;
			break;
		case 0x5e:
			CPU.E = readMem(HL);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x5f:  
			CPU.E = CPU.A;
			CPU.CPUTicks += 4;
			break;
		case 0x60: 
			CPU.H = CPU.B;
			CPU.CPUTicks += 4;
			break;
		case 0x61: 
			CPU.H = CPU.C;
			CPU.CPUTicks += 4;
			break;
		case 0x62: 
			CPU.H = CPU.D;
			CPU.CPUTicks += 4;
			break;
		case 0x63:  
			CPU.H = CPU.E;
			CPU.CPUTicks += 4;
			break;
		case 0x64: 
			CPU.H = CPU.H;
			CPU.CPUTicks += 4;
			break;
		case 0x65:  
			CPU.H = CPU.L;
			CPU.CPUTicks += 4;
			break;
		case 0x66:
			CPU.H = readMem(HL);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x67:  
			CPU.H = CPU.A;
			CPU.CPUTicks += 4;
			break;
		case 0x68:  
			CPU.L = CPU.B;
			CPU.CPUTicks += 4;
			break;
		case 0x69:  
			CPU.L = CPU.C;
			CPU.CPUTicks += 4;
			break;
		case 0x6a:  
			CPU.L = CPU.D;
			CPU.CPUTicks += 4;
			break;
		case 0x6b:  
			CPU.L = CPU.E;
			CPU.CPUTicks += 4;
			break;
		case 0x6c:  
			CPU.L = CPU.H;
			CPU.CPUTicks += 4;
			break;
		case 0x6d:  
			CPU.L = CPU.L;
			CPU.CPUTicks += 4;
			break;
		case 0x6e:
			CPU.L = readMem(HL);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x6f:  
			CPU.L = CPU.A;
			CPU.CPUTicks += 4;
			break;
		case 0x70:
			writeMem(HL, CPU.B);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x71:
			writeMem(HL, CPU.C);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x72:
			writeMem(HL, CPU.D);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x73:
			writeMem(HL, CPU.E);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x74:
			writeMem(HL, CPU.H);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x75:
			writeMem(HL, CPU.L);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x76:  
			halted(1);
			CPU.CPUTicks += 4;
			break;
		case 0x77:
			writeMem(HL, CPU.A);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x78:  
			CPU.A = CPU.B;
			CPU.CPUTicks += 4;
			break;
		case 0x79:  
			CPU.A = CPU.C;
			CPU.CPUTicks += 4;
			break;
		case 0x7a: 
			CPU.A = CPU.D;
			CPU.CPUTicks += 4;
			break;
		case 0x7b: 
			CPU.A = CPU.E;
			CPU.CPUTicks += 4;
			break;
		case 0x7c:  
			CPU.A = CPU.H;
			CPU.CPUTicks += 4;
			break;
		case 0x7d:  
			CPU.A = CPU.L;
			CPU.CPUTicks += 4;
			break;
		case 0x7e:
			CPU.A = readMem(HL);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0x7f:  
			CPU.A = CPU.A;
			CPU.CPUTicks += 4;
			break;
		case 0x80:  
			ADD(CPU.B);
			break;
		case 0x81: 
			ADD(CPU.C);
			break;
		case 0x82:  
			ADD(CPU.D);
			break;
		case 0x83:  
			ADD(CPU.E);
			break;
		case 0x84: 
			ADD(CPU.H);
			break;
		case 0x85: 
			ADD(CPU.L);
			break;
		case 0x86:
			ADD(readMem(HL));
			CPU.CPUTicks += 4;
			break;
		case 0x87: 
			ADD(CPU.A);
			break;
		case 0x88: 
			ADC(CPU.B);
			break;
		case 0x89:  
			ADC(CPU.C);
			break;
		case 0x8A: 
			ADC(CPU.D);
			break;
		case 0x8B:  
			ADC(CPU.E);
			break;
		case 0x8C:  
			ADC(CPU.H);
			break;
		case 0x8D: 
			ADC(CPU.L);
			break;
		case 0x8E:
			ADC(readMem(HL));
			CPU.CPUTicks += 4;
			break;
		case 0x8F:  
			ADC(CPU.A);
			break;
		case 0x90:  
			SUB(CPU.B);
			break;
		case 0x91:  
			SUB(CPU.C);
			break;
		case 0x92:  
			SUB(CPU.D);
			break;
		case 0x93:
			SUB(CPU.E);
			break;
		case 0x94: 
			SUB(CPU.H);
			break;
		case 0x95:
			SUB(CPU.L);
			break;
		case 0x96:
			SUB(readMem(HL));
			CPU.CPUTicks += 4;
			break;
		case 0x97:
			SUB(CPU.A);
			break;
		case 0x98:
			SBC(CPU.B);
			break;
		case 0x99: 
			SBC(CPU.C);
			break;
		case 0x9a:  
			SBC(CPU.D);
			break;
		case 0x9b: 
			SBC(CPU.E);
			break;
		case 0x9c: 
			SBC(CPU.H);
			break;
		case 0x9d: 
			SBC(CPU.L);
			break;
		case 0x9e:
			SBC(readMem(HL));
			CPU.CPUTicks += 4;
			break;
		case 0x9f: 
			SBC(CPU.A);
			break;
		case 0xa0: 
			AND(CPU.B);
			break;
		case 0xa1: 
			AND(CPU.C);
			break;
		case 0xa2: 
			AND(CPU.D);
			break;
		case 0xa3: 
			AND(CPU.E);
			break;
		case 0xa4: 
			AND(CPU.H);
			break;
		case 0xa5: 
			AND(CPU.L);
			break;
		case 0xa6:
			AND(readMem(HL));
			CPU.CPUTicks += 4;
			break;
		case 0xa7: 
			AND(CPU.A);
			break;
		case 0xa8:  
			XOR(CPU.B);
			break;
		case 0xa9: 
			XOR(CPU.C);
			break;
		case 0xaa: 
			XOR(CPU.D);
			break;
		case 0xab: 
			XOR(CPU.E);
			break;
		case 0xac: 
			XOR(CPU.H);
			break;
		case 0xad:  
			XOR(CPU.L);
			break;
		case 0xae:
			XOR(readMem(HL));
			CPU.CPUTicks += 4;
			break;
		case 0xaf: 
			XOR(CPU.A);
			break;
		case 0xb0: 
			OR(CPU.B);
			break;
		case 0xb1: 
			OR(CPU.C);
			break;
		case 0xb2:  
			OR(CPU.D);
			break;
		case 0xb3: 
			OR(CPU.E);
			break;
		case 0xb4: 
			OR(CPU.H);
			break;
		case 0xb5: 
			OR(CPU.L);
			break;
		case 0xb6:
			OR(readMem(HL));
			CPU.CPUTicks += 4;
			break;
		case 0xb7: 
			OR(CPU.A);
			break;
		case 0xb8:
			CP(CPU.B);
			break;
		case 0xb9:
			CP(CPU.C);
			break;
		case 0xba:
			CP(CPU.D);
			break;
		case 0xbb: 
			CP(CPU.E);
			break;
		case 0xbc: 
			CP(CPU.H);
			break;
		case 0xbd:
			CP(CPU.L);
			break;
		case 0xbe:
			CP(readMem(HL));
			CPU.CPUTicks += 4;
			break;
		case 0xbf:
			CP(CPU.A);
			break;
		case 0xc0: 
			if (FlagZ == 0)
				popPC();
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xc1: 
			CPU.C = readMem(CPU.SP++);
			CPU.B = readMem(CPU.SP++);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xc2: 
			adr = adr16();
			if (FlagZ == 0)
			{
				CPU.PC = adr;
				CPU.CPUTicks += 4;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xc3:
			adr = adr16();
			CPU.PC = adr;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xc4: 
			adr = adr16();
			if (FlagZ == 0)
			{
				pushPC();
				CPU.PC = adr;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xc5: 
			pushReg(BC);
			break;
		case 0xc6: 
			op = OP;
			ADD(op);
			CPU.CPUTicks += 4;
			break;
		case 0xc7: 
			pushPC();
			CPU.PC = 0;
			CPU.CPUTicks += 4;
			break;
		case 0xc8:  
			if (FlagZ == 1)
				popPC();
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xc9:
			popPC();
			CPU.CPUTicks += 4;
			break;
		case 0xca:  
			adr = adr16();
			if (FlagZ == 1) 
			{
				CPU.PC = adr;
				CPU.CPUTicks += 4;
				
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xcb: 
			CPU.CPUTicks += 4;
			extendedOPSelect();
			break;
		case 0xcc:
			adr = adr16();
			if (FlagZ == 1)
			{
				pushPC();
				CPU.PC = adr;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xcd:
			adr = adr16();
			pushPC();
			CPU.PC = adr;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xce: 
			op = OP;
			ADC(op);
			CPU.CPUTicks += 4;
			break;
		case 0xcf:
			pushPC();
			CPU.PC = 0x08;
			CPU.CPUTicks += 4;
			break;
		case 0xd0: 
			if (FlagC == 0)
				popPC();
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xd1: 
			CPU.E = readMem(CPU.SP++);
			CPU.D = readMem(CPU.SP++);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xd2: 
			adr = adr16();
			if (FlagC == 0)
			{
				CPU.PC = adr;
				CPU.CPUTicks += 4;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xd4: 
			adr = adr16();
			if (FlagC == 0)
			{
				pushPC();
				CPU.PC = adr;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xd5:  
			pushReg(DE);
			break;
		case 0xd6:  
			op = OP;
			SUB(op);
			CPU.CPUTicks += 4;
			break;
		case 0xd7:  
			pushPC();
			CPU.PC = 0x10;
			CPU.CPUTicks += 4;
			break;
		case 0xd8: 
			if (FlagC == 1)
				popPC();
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xd9:  
			popPC();
			CPU.IME = 1;
			CPU.CPUTicks += 4;
			OPSelect();
			break;
		case 0xda:  
			adr = adr16();
			if (FlagC == 1) 
			{
				CPU.PC = adr;
				CPU.CPUTicks += 4;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xdc:  
			adr = adr16();
			if (FlagC == 1)
			{
				pushPC();
				CPU.PC = adr;
			}
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xde:  
			op = OP;
			SBC(op);
			CPU.CPUTicks += 4;
			break;
		case 0xdf: 
			pushPC();
			CPU.PC = 0x18;
			CPU.CPUTicks += 4;
			break;
		case 0xe0: 
			adr = (0xFF00 | OP);
			writeMem(adr, CPU.A);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xe1:
			CPU.L = readMem(CPU.SP++);
			CPU.H = readMem(CPU.SP++);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xe2: 
			adr = (0xFF00 | CPU.C);
			writeMem(adr, CPU.A);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xe5: 
			pushReg(HL);
			break;
		case 0xe6: 
			op = OP;
			AND(op);
			CPU.CPUTicks += 4;
			break;
		case 0xe7: 
			pushPC();
			CPU.PC = 0x20;
			CPU.CPUTicks += 4;
			break;
		case 0xe8:
			op = OP;
			ADDSP(op);
			break;
		case 0xe9:
			CPU.PC = HL;
			CPU.CPUTicks += 4;
			break;
		case 0xea: 
			adr = adr16();
			writeMem(adr, CPU.A);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xee:  
			op = OP;
			XOR(op);
			CPU.CPUTicks += 4;
			break;
		case 0xef: 
			pushPC();
			CPU.PC = 0x28;
			CPU.CPUTicks += 4;
			break;
		case 0xf0: 
			adr = (0xFF00 | OP);
			CPU.A = readMem(adr);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xf1:
			CPU.Flags = 0xF0 & readMem(CPU.SP++);		
			CPU.A = readMem(CPU.SP++);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xf2: 
			adr = (0xFF00 | CPU.C);
			CPU.A = readMem(adr);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xf3: 
			CPU.IME = 0;
			CPU.CPUTicks += 4;
			break;
		case 0xf5: 
			pushReg(AF);
			break;
		case 0xf6: 
			op = OP;
			OR(op);
			CPU.CPUTicks += 4;
			break;
		case 0xf7: 
			pushPC();
			CPU.PC = 0x30;
			CPU.CPUTicks += 4;
			break;
		case 0xf8:
			op = OP;
			LDHLSP(op);
			break;
		case 0xf9:
			CPU.SP = HL;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xfa:
			adr = adr16();
			CPU.A = readMem(adr);
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			CPU.CPUTicks += 4;
			break;
		case 0xfb:
			CPU.IME = 1;
			CPU.CPUTicks += 4;
			OPSelect(); //run next op before interrupt occurs
			break;
		case 0xfe: 
			op = OP;
			CP(op);
			CPU.CPUTicks += 4;
			break;
		case 0xff:
			pushPC();
			CPU.PC = 0x38;
			CPU.CPUTicks += 4;
			break;
		default:
			break;
	}
}

void extendedOPSelect() {
	uchar op;	//used for 8-bit values

	op = readMem(CPU.PC++);
	//UARTprintf("OPCODE: %X @ %X\n", op, CPU.PC-1);
	switch (op)
	{
		case 0x00:
			RLC(&CPU.B);
			break;
		case 0x01:
			RLC(&CPU.C);
			break;
		case 0x02:
			RLC(&CPU.D);
			break;
		case 0x03:
			RLC(&CPU.E);
			break;
		case 0x04:
			RLC(&CPU.H);
			break;
		case 0x05:
			RLC(&CPU.L);
			break;
		case 0x06:
			HLm = readMem(HL);
			RLC(&HLm);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x07:
			RLC(&CPU.A);
			break;
		case 0x08:
			RRC(&CPU.B);
			break;
		case 0x09:
			RRC(&CPU.C);
			break;
		case 0x0a:
			RRC(&CPU.D);
			break;
		case 0x0b:
			RRC(&CPU.E);
			break;
		case 0x0c:
			RRC(&CPU.H);
			break;
		case 0x0d:
			RRC(&CPU.L);
			break;
		case 0x0e:
			HLm = readMem(HL);
			RRC(&HLm);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x0f:
			RRC(&CPU.A);
			break;
		case 0x10:
			RL(&CPU.B);
			break;
		case 0x11:  
			RL(&CPU.C);
			break;
		case 0x12:
			RL(&CPU.D);
			break;
		case 0x13:
			RL(&CPU.E);
			break;
		case 0x14:
			RL(&CPU.H);
			break;
		case 0x15:
			RL(&CPU.L);
			break;
		case 0x16:
			HLm = readMem(HL);
			RL(&HLm);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x17:
			RL(&CPU.A);
			break;
		case 0x18:
			RR(&CPU.B);
			break;
		case 0x19:
			RR(&CPU.C);
			break;
		case 0x1a:  
			RR(&CPU.D);
			break;
		case 0x1b:
			RR(&CPU.E);
			break;
		case 0x1c:
			RR(&CPU.H);
			break;
		case 0x1d:
			RR(&CPU.L);
			break;
		case 0x1e:
			HLm = readMem(HL);
			RR(&HLm);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x1f:
			RR(&CPU.A);
			break;
		case 0x20:
			SLA(&CPU.B);
			break;
		case 0x21:
			SLA(&CPU.C);
			break;
		case 0x22:
			SLA(&CPU.D);
			break;
		case 0x23:
			SLA(&CPU.E);
			break;
		case 0x24:
			SLA(&CPU.H);
			break;
		case 0x25:
			SLA(&CPU.L);
			break;
		case 0x26:
			HLm = readMem(HL);
			SLA(&HLm);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x27:
			SLA(&CPU.A);
			break;
		case 0x28:
			SRA(&CPU.B);
			break;
		case 0x29:
			SRA(&CPU.C);
			break;
		case 0x2a:
			SRA(&CPU.D);
			break;
		case 0x2b:
			SRA(&CPU.E);
			break;
		case 0x2c:
			SRA(&CPU.H);
			break;
		case 0x2d:
			SRA(&CPU.L);
			break;
		case 0x2e:
			HLm = readMem(HL);
			SRA(&HLm);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x2f:
			SRA(&CPU.A);
			break;
		case 0x30:
			SWAP(&CPU.B);
			break;
		case 0x31:
			SWAP(&CPU.C);
			break;
		case 0x32:
			SWAP(&CPU.D);
			break;
		case 0x33:
			SWAP(&CPU.E);
			break;
		case 0x34:
			SWAP(&CPU.H);
			break;
		case 0x35:
			SWAP(&CPU.L);
			break;
		case 0x36:
			HLm = readMem(HL);
			SWAP(&HLm);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x37:
			SWAP(&CPU.A);
			break;
		case 0x38:
			SRL(&CPU.B);
			break;
		case 0x39:
			SRL(&CPU.C);
			break;
		case 0x3a:
			SRL(&CPU.D);
			break;
		case 0x3b:
			SRL(&CPU.E);
			break;
		case 0x3c:
			SRL(&CPU.H);
			break;
		case 0x3d:
			SRL(&CPU.L);
			break;
		case 0x3e:
			HLm = readMem(HL);
			SRL(&HLm);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x3f:
			SRL(&CPU.A);
			break;
		case 0x40:
			BIT(CPU.B, 0);
			break;
		case 0x41:
			BIT(CPU.C, 0);
			break;
		case 0x42:  
			BIT(CPU.D, 0);
			break;
		case 0x43:
			BIT(CPU.E, 0);
			break;
		case 0x44:
			BIT(CPU.H, 0);
			break;
		case 0x45:
			BIT(CPU.L, 0);
			break;
		case 0x46:
			HLm = readMem(HL);
			BIT(HLm,0);
			writeMem(HL, HLm);
			CPU.CPUTicks += 4;
			break;
		case 0x47:  
			BIT(CPU.A, 0);
			break;
		case 0x48:
			BIT(CPU.B, 1);
			break;
		case 0x49:
			BIT(CPU.C, 1);
			break;
		case 0x4a:
			BIT(CPU.D, 1);
			break;
		case 0x4b:
			BIT(CPU.E, 1);
			break;
		case 0x4c:
			BIT(CPU.H, 1);
			break;
		case 0x4d:
			BIT(CPU.L, 1);
			break;
		case 0x4e:
			HLm = readMem(HL);
			BIT(HLm, 1);
			writeMem(HL, HLm);
			CPU.CPUTicks += 4;
			break;
		case 0x4f:
			BIT(CPU.A, 1);
			break;
		case 0x50:
			BIT(CPU.B, 2);
			break;
		case 0x51:
			BIT(CPU.C, 2);
			break;
		case 0x52:
			BIT(CPU.D, 2);
			break;
		case 0x53:
			BIT(CPU.E, 2);
			break;
		case 0x54:
			BIT(CPU.H, 2);
			break;
		case 0x55:
			BIT(CPU.L, 2);
			break;
		case 0x56:
			HLm = readMem(HL);
			BIT(HLm, 2);
			writeMem(HL, HLm);
			CPU.CPUTicks += 4;
			break;
		case 0x57:
			BIT(CPU.A, 2);
			break;
		case 0x58:
			BIT(CPU.B, 3);
			break;
		case 0x59:
			BIT(CPU.C, 3);
			break;
		case 0x5a:
			BIT(CPU.D, 3);
			break;
		case 0x5b:
			BIT(CPU.E, 3);
			break;
		case 0x5c:
			BIT(CPU.H, 3);
			break;
		case 0x5d:
			BIT(CPU.L, 3);
			break;
		case 0x5e:
			HLm = readMem(HL);
			BIT(HLm, 3);
			writeMem(HL, HLm);
			CPU.CPUTicks += 4;
			break;
		case 0x5f:
			BIT(CPU.A, 3);
			break;
		case 0x60:
			BIT(CPU.B, 4);
			break;
		case 0x61:
			BIT(CPU.C, 4);
			break;
		case 0x62:
			BIT(CPU.D, 4);
			break;
		case 0x63:
			BIT(CPU.E, 4);
			break;
		case 0x64:
			BIT(CPU.H, 4);
			break;
		case 0x65:
			BIT(CPU.L, 4);
			break;
		case 0x66:
			HLm = readMem(HL);
			BIT(HLm, 4);
			writeMem(HL, HLm);
			CPU.CPUTicks += 4;
			break;
		case 0x67:
			BIT(CPU.A, 4);
			break;
		case 0x68:
			BIT(CPU.B, 5);
			break;
		case 0x69:
			BIT(CPU.C, 5);
			break;
		case 0x6a:
			BIT(CPU.D, 5);
			break;
		case 0x6b:
			BIT(CPU.E, 5);
			break;
		case 0x6c:
			BIT(CPU.H, 5);
			break;
		case 0x6d:
			BIT(CPU.L, 5);
			break;
		case 0x6e:
			HLm = readMem(HL);
			BIT(HLm, 5);
			writeMem(HL, HLm);
			CPU.CPUTicks += 4;
			break;
		case 0x6f:
			BIT(CPU.A, 5);
			break;
		case 0x70:
			BIT(CPU.B, 6);
			break;
		case 0x71:
			BIT(CPU.C, 6);
			break;
		case 0x72:
			BIT(CPU.D, 6);
			break;
		case 0x73:
			BIT(CPU.E, 6);
			break;
		case 0x74:
			BIT(CPU.H, 6);
			break;
		case 0x75:
			BIT(CPU.L, 6);
			break;
		case 0x76:
			HLm = readMem(HL);
			BIT(HLm, 6);
			writeMem(HL, HLm);
			CPU.CPUTicks += 4;
			break;
		case 0x77:
			BIT(CPU.A, 6);
			break;
		case 0x78:
			BIT(CPU.B, 7);
			break;
		case 0x79:
			BIT(CPU.C, 7);
			break;
		case 0x7a:
			BIT(CPU.D, 7);
			break;
		case 0x7b:
			BIT(CPU.E, 7);
			break;
		case 0x7c:  
			BIT(CPU.H, 7);
			break;
		case 0x7d:
			BIT(CPU.L, 7);
			break;
		case 0x7e:
			HLm = readMem(HL);
			BIT(HLm, 7);
			writeMem(HL, HLm);
			CPU.CPUTicks += 4;
			break;
		case 0x7f:
			BIT(CPU.A, 7);
			break;
		case 0x80:
			RES(&CPU.B, 0);
			break;
		case 0x81:
			RES(&CPU.C, 0);
			break;
		case 0x82:
			RES(&CPU.D, 0);
			break;
		case 0x83:
			RES(&CPU.E, 0);
			break;
		case 0x84:
			RES(&CPU.H, 0);
			break;
		case 0x85:
			RES(&CPU.L, 0);
			break;
		case 0x86:
			HLm = readMem(HL);
			RES(&HLm,0);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x87:	
			RES(&CPU.A, 0);
			break;
		case 0x88:
			RES(&CPU.B, 1);
			break;
		case 0x89:
			RES(&CPU.C, 1);
			break;
		case 0x8a:
			RES(&CPU.D, 1);
			break;
		case 0x8b:
			RES(&CPU.E, 1);
			break;
		case 0x8c:
			RES(&CPU.H, 1);
			break;
		case 0x8d:
			RES(&CPU.L, 1);
			break;
		case 0x8e:
			HLm = readMem(HL);
			RES(&HLm, 1);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x8f:
			RES(&CPU.A, 1);
			break;
		case 0x90:
			RES(&CPU.B, 2);
			break;
		case 0x91:
			RES(&CPU.C, 2);
			break;
		case 0x92:
			RES(&CPU.D, 2);
			break;
		case 0x93:
			RES(&CPU.E, 2);
			break;
		case 0x94:
			RES(&CPU.H, 2);
			break;
		case 0x95:
			RES(&CPU.L, 2);
			break;
		case 0x96:
			HLm = readMem(HL);
			RES(&HLm, 2);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x97:
			RES(&CPU.A, 2);
			break;
		case 0x98:
			RES(&CPU.B, 3);
			break;
		case 0x99:
			RES(&CPU.C, 3);
			break;
		case 0x9A:
			RES(&CPU.D, 3);
			break;
		case 0x9B:
			RES(&CPU.E, 3);
			break;
		case 0x9C:
			RES(&CPU.H, 3);
			break;
		case 0x9D:
			RES(&CPU.L, 3);
			break;
		case 0x9E:
			HLm = readMem(HL);
			RES(&HLm, 3);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0x9F:
			RES(&CPU.A, 3);
			break;
		case 0xa0:
			RES(&CPU.B, 4);
			break;
		case 0xa1:
			RES(&CPU.C, 4);
			break;
		case 0xa2:
			RES(&CPU.D, 4);
			break;
		case 0xa3:
			RES(&CPU.E, 4);
			break;
		case 0xa4:
			RES(&CPU.H, 4);
			break;
		case 0xa5:
			RES(&CPU.L, 4);
			break;
		case 0xa6:
			HLm = readMem(HL);
			RES(&HLm, 4);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xa7:
			RES(&CPU.A, 4);
			break;
		case 0xa8:
			RES(&CPU.B, 5);
			break;
		case 0xa9:
			RES(&CPU.C, 5);
			break;
		case 0xaa:
			RES(&CPU.D, 5);
			break;
		case 0xab:
			RES(&CPU.E, 5);
			break;
		case 0xac:
			RES(&CPU.H, 5);
			break;
		case 0xad:
			RES(&CPU.L, 5);
			break;
		case 0xae:
			HLm = readMem(HL);
			RES(&HLm, 5);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xaf:
			RES(&CPU.A, 5);
			break;
		case 0xb0:
			RES(&CPU.B, 6);
			break;
		case 0xb1:
			RES(&CPU.C, 6);
			break;
		case 0xb2:
			RES(&CPU.D, 6);
			break;
		case 0xb3:
			RES(&CPU.E, 6);
			break;
		case 0xb4:
			RES(&CPU.H, 6);
			break;
		case 0xb5:
			RES(&CPU.L, 6);
			break;
		case 0xb6:
			HLm = readMem(HL);
			RES(&HLm, 6);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xb7:
			RES(&CPU.A, 6);
			break;
		case 0xb8:
			RES(&CPU.B, 7);
			break;
		case 0xb9:
			RES(&CPU.C, 7);
			break;
		case 0xba:
			RES(&CPU.D, 7);
			break;
		case 0xbb:
			RES(&CPU.E, 7);
			break;
		case 0xbc:
			RES(&CPU.H, 7);
			break;
		case 0xbd:
			RES(&CPU.L, 7);
			break;
		case 0xbe:
			HLm = readMem(HL);
			RES(&HLm, 7);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xbf:
			RES(&CPU.A, 7);
			break;
		case 0xc0:
			SET(&CPU.B, 0);
			break;
		case 0xc1:
			SET(&CPU.C, 0);
			break;
		case 0xc2:
			SET(&CPU.D, 0);
			break;
		case 0xc3:
			SET(&CPU.E, 0);
			break;
		case 0xc4:
			SET(&CPU.H, 0);
			break;
		case 0xc5:
			SET(&CPU.L, 0);
			break;
		case 0xc6:
			HLm = readMem(HL);
			SET(&HLm, 0);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xc7:
			SET(&CPU.A, 0);
			break;
		case 0xc8:
			SET(&CPU.B, 1);
			break;
		case 0xc9:
			SET(&CPU.C, 1);
			break;
		case 0xca:
			SET(&CPU.D, 1);
			break;
		case 0xcb:
			SET(&CPU.E, 1);
			break;
		case 0xcc:
			SET(&CPU.H, 1);
			break;
		case 0xcd:
			SET(&CPU.L, 1);
			break;
		case 0xce:
			HLm = readMem(HL);
			SET(&HLm, 1);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xcf:	
			SET(&CPU.A, 1);
			break;
		case 0xd0:
			SET(&CPU.B, 2);
			break;
		case 0xd1:
			SET(&CPU.C, 2);
			break;
		case 0xd2:
			SET(&CPU.D, 2);
			break;
		case 0xd3:
			SET(&CPU.E, 2);
			break;
		case 0xd4:
			SET(&CPU.H, 2);
			break;
		case 0xd5:
			SET(&CPU.L, 2);
			break;
		case 0xd6:
			HLm = readMem(HL);
			SET(&HLm, 2);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xd7:
			SET(&CPU.A, 2);
			break;
		case 0xd8:
			SET(&CPU.B, 3);
			break;
		case 0xd9:
			SET(&CPU.C, 3);
			break;
		case 0xda:
			SET(&CPU.D, 3);
			break;
		case 0xdb:
			SET(&CPU.E, 3);
			break;
		case 0xdc:
			SET(&CPU.H, 3);
			break;
		case 0xdd:
			SET(&CPU.L, 3);
			break;
		case 0xde:
			HLm = readMem(HL);
			SET(&HLm, 3);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xdf:
			SET(&CPU.A, 3);
			break;
		case 0xe0:
			SET(&CPU.B, 4);
			break;
		case 0xe1:
			SET(&CPU.C, 4);
			break;
		case 0xe2:
			SET(&CPU.D, 4);
			break;
		case 0xe3:
			SET(&CPU.E, 4);
			break;
		case 0xe4:
			SET(&CPU.H, 4);
			break;
		case 0xe5:
			SET(&CPU.L, 4);
			break;
		case 0xe6:
			HLm = readMem(HL);
			SET(&HLm, 4);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xe7:
			SET(&CPU.A, 4);
			break;
		case 0xe8:
			SET(&CPU.B, 5);
			break;
		case 0xe9:
			SET(&CPU.C, 5);
			break;
		case 0xea:
			SET(&CPU.D, 5);
			break;
		case 0xeb:
			SET(&CPU.E, 5);
			break;
		case 0xec:
			SET(&CPU.H, 5);
			break;
		case 0xed:
			SET(&CPU.L, 5);
			break;
		case 0xee:
			HLm = readMem(HL);
			SET(&HLm, 5);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xef:
			SET(&CPU.A, 5);
			break;
		case 0xf0:
			SET(&CPU.B, 6);
			break;
		case 0xf1:
			SET(&CPU.C, 6);
			break;
		case 0xf2:
			SET(&CPU.D, 6);
			break;
		case 0xf3:
			SET(&CPU.E, 6);
			break;
		case 0xf4:
			SET(&CPU.H, 6);
			break;
		case 0xf5:
			SET(&CPU.L, 6);
			break;
		case 0xf6:
			HLm = readMem(HL);
			SET(&HLm, 6);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xf7:
			SET(&CPU.A, 6);
			break;
		case 0xf8:
			SET(&CPU.B, 7);
			break;
		case 0xf9:
			SET(&CPU.C, 7);
			break;
		case 0xfa:
			SET(&CPU.D, 7);
			break;
		case 0xfb:
			SET(&CPU.E, 7);
			break;
		case 0xfc:
			SET(&CPU.H, 7);
			break;
		case 0xfd:
			SET(&CPU.L, 7);
			break;
		case 0xfe:
			HLm = readMem(HL);
			SET(&HLm, 7);
			writeMem(HL, HLm);
			CPU.CPUTicks += 8;
			break;
		case 0xff:
			SET(&CPU.A, 7);
			break;
		default:
			break;
	}
}

ushort getPC() {
	return CPU.PC;
}

ushort getSP() {
	return CPU.SP;
}

void setPC(ushort A) {
	CPU.PC = A;
}

uchar getIME() {
	return CPU.IME;
}

void setIME(uchar A) {
	CPU.IME = A;
}

ulong getCPUTicks(){
	return CPU.CPUTicks;
}

void halted(uchar a) {
	CPU.halt = a & 0x1;
}

uchar DIHalt() {
	return(CPU.halt && (CPU.IME == 0));
}

ushort getReg(uchar A) {
	switch (A) {
	default:return AF;
	case 1:return BC;
	case 2:return DE;
	case 3:return HL;
	}
}

ushort adr16() {
	ushort adrl = OP;
	ushort adrh = OP;
	return adrh << 8 | adrl;
}

void pushPC() {
	//decrement SP then place data
	writeMem(--CPU.SP, (CPU.PC >> 8) & 0xFF);//write upper
	writeMem(--CPU.SP, CPU.PC & 0xFF);//write lower
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void popPC() {
	//write then increment SP
	CPU.PC = readMem(CPU.SP++);
	CPU.PC |= readMem(CPU.SP++) << 8;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void pushReg(ushort A) {
	//decrement SP then place data
	writeMem(--CPU.SP, (A >> 8) & 0xFF);//write upper
	writeMem(--CPU.SP, A & 0xFF);//write lower
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void AND(uchar B) {
	Flag = 0x20;
	CPU.A &= B;
	if (CPU.A == 0)       //Zero Flag
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void OR(uchar B) {
	CPU.A |= B;
	if (CPU.A == 0)       //Zero Flag
		Flag = 0x80;
	else
		Flag = 0x0;
	CPU.CPUTicks += 4;
}

void XOR(uchar B) {
	CPU.A ^= B;
	if (CPU.A == 0)       //Zero Flag
		Flag = 0x80;
	else
		Flag = 0x0;
	CPU.CPUTicks += 4;
}

void CPL() {
	CPU.A = ~CPU.A;
	Flag |= 0x60;
	CPU.CPUTicks += 4;
}

void SCF() {
	Flag &= 0x80;//keep Z
	Flag |= 0x10;//set c
	CPU.CPUTicks += 4;
}

void CCF() {
	Flag = (FlagZ << 7) | (((FlagC ^ 0x1) << 4) & 0xF0);//keep z, comp c, clear rest
	CPU.CPUTicks += 4;
}

void ADD(uchar B) {
	ushort C = CPU.A + B;
	Flag = 0;	
	if (C > 0xFF)//carry flag
		Flag |= 0x10;

	if ((CPU.A & 0x0F) + (B & 0x0F) > 0x0F)//half carry
		Flag |= 0x20;

	CPU.A += B;
	if (CPU.A == 0)       //Zero Flag
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void SUB(uchar B) {
	Flag = 0x40;//Set Sub flag

	//Half Carry Subtraction
	if ((CPU.A & 0xF) < (B & 0xF))
		Flag |= 0x20;

	//borrow flag
	if (CPU.A < B)
		Flag |= 0x10;

	CPU.A -= B;
	if (CPU.A == 0)       //Zero Flag
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void ADC(uchar B) {
	uchar D = FlagC;
	ushort C = CPU.A + B + D;
	Flag = 0;
	if (C > 0xFF)//carry flag
		Flag |= 0x10;

	if (((CPU.A & 0x0F) + (B & 0x0F) + D) > 0x0F)//half carry
		Flag |= 0x20;

	CPU.A += B + D;
	if (CPU.A == 0)       //Zero Flag
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void SBC(uchar B) {
	uchar C = FlagC;
	Flag = 0x40;//Set Sub flag

	//Half Carry Subtraction
	if ((CPU.A & 0xF) < ((B & 0xF) + C))
		Flag |= 0x20;

	//borrow flag
	if (CPU.A < (B + C))
		Flag |= 0x10;

	CPU.A -= B + C;
	if (CPU.A == 0)       //Zero Flag
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void ADDHL(ushort B) {
	
	ulong C = HL + B;
	if (C > 0xFFFF)//carry flag
		Flag |= 0x10;
	else
		Flag &= ~0x10;

	if (((HL & 0x0FFF) + (B & 0x0FFF)) > 0x0FFF)//half carry
		Flag |= 0x20;
	else
		Flag &= ~0x20;

	Flag &= ~0x40; //clear sub flag

	CPU.H = (C >> 8) & 0xFF;
	CPU.L = C & 0xFF;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void INC(uchar * A) {
	Flag &= ~0x40; //clear sub flag

	if ((*A & 0x0F) + 1 > 0x0F)//half carry
		Flag |= 0x20;
	else
		Flag &= ~0x20;

	*A += 1;

	if (*A == 0)       //Zero Flag
		Flag |= 0x80;
	else
		Flag &= ~0x80;
	CPU.CPUTicks += 4;
}

void DEC(uchar * A) {
	Flag |= 0x40;//Set Sub flag

	if ((*A & 0x0F) == 0)//half carry
		Flag |= 0x20;
	else
		Flag &= ~0x20;

	*A -= 1;
	if (*A == 0)       //Zero Flag
		Flag |= 0x80;
	else
		Flag &= ~0x80;
	CPU.CPUTicks += 4;
}

void INC2(uchar * A, uchar * B) {
	//no flags updated
	ushort C;
	C = (*A << 8) | *B;
	C += 1;
	*A = (C >> 8) & 0xFF;
	*B = C & 0xFF;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void DEC2(uchar * A, uchar * B) {
	//no flags updated
	ushort C;
	C = (*A << 8) | *B;
	C -= 1;
	*A = (C >> 8) & 0xFF;
	*B = C & 0xFF;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void INCHL() {
	uchar A = readMem(HL);
	Flag &= ~0x40; //clear sub flag
	

	if ((A & 0x0F) + 1 > 0x0F)//half carry
		Flag |= 0x20;
	else
		Flag &= ~0x20;

	A += 1;

	if (A == 0)       //Zero Flag
		Flag |= 0x80;
	else
		Flag &= ~0x80;
	writeMem(HL, A);
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void DECHL() {
	uchar A = readMem(HL);
	Flag |= 0x40;//Set Sub flag
	
	if ((A & 0x0F) == 0)//half carry
		Flag |= 0x20;
	else
		Flag &= ~0x20;

	A -= 1;
	if (A == 0)       //Zero Flag
		Flag |= 0x80;
	else
		Flag &= ~0x80;
	writeMem(HL, A);
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void CP(uchar B) {
	Flag = 0x40;//Set Sub flag

	//Half Carry Subtraction
	if ((CPU.A & 0xF) < (B & 0xF))
		Flag |= 0x20;

	//borrow flag
	if (CPU.A < B)
		Flag |= 0x10;

	if (CPU.A == B)       //Zero Flag
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void DAA() {
	if (FlagN)
	{
		if (FlagC) 
			CPU.A -= 0x60;
		if (FlagH) 
			CPU.A -= 0x06;
	}
	else
	{
		if (FlagC || (CPU.A & 0xFF) > 0x99)
		{		
			CPU.A += 0x60;
			Flag |= 0x10;
		}
		if (FlagH || (CPU.A & 0x0F) > 0x09)
		{ 
			CPU.A += 0x06; 
		}
	}

	if (CPU.A == 0)
		Flag |= 0x80;
	else
		Flag &= ~0x80;
	
	Flag &= ~0x20;

	CPU.CPUTicks += 4;
}

void ADDSP(uchar B){
	ushort sum = CPU.SP + ((B > 0x7F) ? (B | 0xFF00) : B);//sign extension
	Flag = 0;
	
	if (((CPU.SP & 0xFF) + B) > 0xFF)
		Flag |= 0x10;
	if (((CPU.SP & 0x0F) + (B & 0x0F)) > 0x0F)
		Flag |= 0x20;
	CPU.SP = sum;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

void LDHLSP(uchar B){
	
	ushort sum = CPU.SP + ((B > 0x7F) ? (B | 0xFF00) : B);//sign extension
	Flag = 0;
	if (((CPU.SP & 0xFF) + B) > 0xFF)
		Flag |= 0x10;
	if (((CPU.SP & 0x0F) + (B & 0x0F)) > 0x0F)
		Flag |= 0x20;

	CPU.H = (sum >> 8) & 0xFF;
	CPU.L = sum & 0xFF;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
	CPU.CPUTicks += 4;
}

///------------------------------------------------
//EXtended OpCodes

void RL(uchar *A) {
	uchar temp = FlagC;
	Flag = (*A >> 7) << 4;
	*A = *A << 1;
	*A |= temp;
	if (*A == 0)
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void RLC(uchar *A) {
	uchar temp = (*A >> 7);
	Flag = temp << 4;
	*A = *A << 1;
	*A |= temp;
	if (*A == 0)
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void RLA() {
	uchar temp = FlagC;
	Flag = ((CPU.A >> 7) << 4) & 0x10;
	CPU.A = CPU.A << 1;
	CPU.A |= temp;
	CPU.CPUTicks += 4;
}

void RLCA() {
	uchar temp = (CPU.A >> 7);
	Flag = temp << 4;
	CPU.A = CPU.A << 1;
	CPU.A |= temp;
	CPU.CPUTicks += 4;
}

void RR(uchar *A) {
	uchar temp = FlagC;
	Flag = (*A & 0x1) << 4;
	*A = *A >> 1;
	*A |= (temp << 7);
	if (*A == 0)
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void RRC(uchar *A) {
	uchar temp = (*A & 0x1);
	Flag = temp << 4;
	*A = *A >> 1;
	*A |= (temp << 7);
	if (*A == 0)
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void RRA() {
	uchar temp = FlagC;
	Flag = (CPU.A & 0x1) << 4;
	CPU.A = CPU.A >> 1;
	CPU.A |= (temp << 7);
	CPU.CPUTicks += 4;
}

void RRCA() {
	uchar temp = (CPU.A & 0x1);
	Flag = temp << 4;
	CPU.A = CPU.A >> 1;
	CPU.A |= (temp << 7);
	CPU.CPUTicks += 4;
}

void SLA(uchar * A){
	Flag = (*A >> 7) << 4;
	*A = *A << 1;
	if (*A == 0)
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void SRA(uchar * A){
	uchar temp = (*A & 0x80);//old msb
	Flag = (*A & 0x1) << 4;
	*A = *A >> 1;
	*A |= temp;
	if (*A == 0)
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void SRL(uchar * A){
	Flag = (*A & 0x1) << 4;
	*A = *A >> 1;
	if (*A == 0)
		Flag |= 0x80;
	CPU.CPUTicks += 4;
}

void BIT(uchar A, uchar B) {
	Flag |= 0x20;
	Flag &= ~0x40;
	if (((A >> B) & 0x1) == 0)
		Flag |= 0x80;
	else
		Flag &= ~0x80;
	CPU.CPUTicks += 4;
}

void SWAP(uchar * A){
	uchar h = *A & 0XF0;
	uchar l = *A & 0X0F;
	*A = (h >> 4) | (l << 4);
	if (*A == 0)
		Flag = 0x80;
	else
		Flag = 0;
	CPU.CPUTicks += 4;
}

void RES(uchar *A,uchar B){
	*A &= ~(0x1 << B);
	CPU.CPUTicks += 4;
}

void SET(uchar *A,uchar B){
	*A |= (0x1 << B);
	CPU.CPUTicks += 4;
}
