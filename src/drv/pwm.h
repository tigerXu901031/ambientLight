#ifndef __PWM_H__
#define __PWM_H__

#include "../srv/type.h"
#include "ccu60.h"

#define Pwm2CCUCh(portNum) CCU60_CHANNEL_##portNum
#define getCCUCh    Pwm2CCUCh(portNum)

#define PWM_ONE_PERIOD_CNT  100

extern void setPwmDutyCyc(uint8 pwmPort, uint8 dutyCyc);

#endif