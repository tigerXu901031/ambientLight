#ifndef __TASK_H__
#define __TASK_H__

#include "../drv/XC22xxREGS.H"
#include "../drv/clk.h"
#include "../drv/io.h"
#include "../srv/led.h"

extern void task10Hz();
extern void task800kHz();

#endif