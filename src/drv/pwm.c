#include "pwm.h"

void setPwmDutyCyc(uint8 pwmPort, uint8 dutyCyc)
{
    uint16 dutyVal = 0;

    /* get the duty cycle value in percent and convert
       into counter value and assigned to the CCU counter */
    CCU60_vLoadChannelShadowRegister(getCCUCh, dutyVal);
    // CCU60_vLoadChannelShadowRegister(CCU60_CHANNEL_0, dutyVal);

    switch(pwmPort)
    {
        case 0:
            CCU60_vLoadChannelShadowRegister_CCU60_CHANNEL_1(dutyVal);
            break;
        case 1:
            CCU60_vLoadChannelShadowRegister_CCU60_CHANNEL_2(dutyVal);
            break;
        case 2:
            CCU60_vLoadChannelShadowRegister_CCU60_CHANNEL_3(dutyVal);
            break;
    }
}

