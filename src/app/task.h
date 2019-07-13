#ifndef __TASK_H__
#define __TASK_H__

#define LED_PROJECT     1

#include "../drv/XC22xxREGS.H"
#include "../drv/clk.h"
#include "../drv/io.h"
#include "../drv/can.h"
#include "../srv/led.h"
#if LED_PROJECT == 1
#include "ledCtrlPrj1.h"
#elif LED_PROJECT == 2
#include "ledCtrl.h"
#endif



extern void taskSlow();
extern void taskFast();

#endif