#ifndef __TASK_H__
#define __TASK_H__

#include "ledCtrl.h"
#include "../drv/XC22xxREGS.H"
#include "../drv/clk.h"
#include "../drv/io.h"
#include "../drv/can.h"
#include "../srv/led.h"

extern void taskSlow();
extern void taskFast();

#endif