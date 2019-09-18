#ifndef cpuh
#define cpuh
#include "defs.h"
typedef struct{
	uchar A;
	uchar B;
	uchar C;
	uchar D;
	uchar E;
	uchar H;
	uchar L;
	uchar Flags;
	ushort SP;
	ushort PC;
	uchar IME;
	uchar halt;
	volatile ulong CPUTicks;
}GBCPU;

ushort getPC(void);
ushort getSP(void);
void setPC(ushort A);
uchar getIME(void);
void setIME(uchar A);
ulong getCPUTicks(void);
void halted(uchar A);
uchar DIHalt(void);
ushort getReg(uchar A);


void OPSelect(void);
void extendedOPSelect(void);

void initCPU(void);///reset CPU and map Memory

ushort adr16(void);///get 16 address from code next op codes
void pushPC(void);
void popPC(void);
void pushReg(ushort A);
//Logic Operations
void AND(uchar B);
void OR(uchar B);
void XOR(uchar B);
void CPL(void);
void SCF(void);
void CCF(void);
//Arithmetic Operations
void ADD(uchar B);
void SUB(uchar B);
void ADC(uchar B);
void SBC(uchar B);
void ADDHL(ushort B);
void INC(uchar * A);
void DEC(uchar * A);
void INC2(uchar * A, uchar * B);
void DEC2(uchar * A, uchar * B);
void INCHL(void);
void DECHL(void);
void CP(uchar B);
//Rotate Left
void RL(uchar * A);
void RLC(uchar * A);
void RLA(void);
void RLCA(void);
void RR(uchar * A);
void RRC(uchar * A);
void RRA(void);
void RRCA(void);
//Shifts
void SLA(uchar * A);
void SRA(uchar * A);
void SRL(uchar * A);
//Bit testing/re-setting/swapping
void BIT(uchar A, uchar B);
void SWAP(uchar * A);
void RES(uchar *A, uchar B);
void SET(uchar *A, uchar B);
void DAA(void);
//other
void ADDSP(uchar B);
void LDHLSP(uchar B);

#endif
