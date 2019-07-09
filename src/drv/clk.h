#ifndef __CLK_H__
#define __CLK_H__

#include "XC22xxREGS.H"
#include "inc/INTRINS.H"
#include "../srv/type.h"

#define TIME_NS_PER_INSTRUCTION_CYCLE 50

extern void MAIN_vChangeFreq(void);
extern void MAIN_vUnlockProtecReg(void);
extern void MAIN_vLockProtecReg(void);
extern void delay(uint16 inOpCyc);
extern void delay300ns();

#endif