#include "pwm.h"

void setPwmDutyCyc(uint8 pwmPort, uint8 dutyCyc)
{
    uint16 dutyVal = 0;
    /* get the duty cycle value in percent and convert
       into counter value and assigned to the CCU counter */
    

    CCU60_vLoadChannelShadowRegister(Pwm2CCUCh(pwmPort) ,dutyVal);
}

