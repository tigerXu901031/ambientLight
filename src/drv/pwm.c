#include "pwm.h"

uint16 ccuCntArr[10];

void setPwmDutyCyc(uint8 pwmPort, uint8 dutyCyc)
{
    uint16 dutyVal = 0;

    /* get the duty cycle value in percent and convert
       into counter value and assigned to the CCU counter */
    // CCU60_vLoadChannelShadowRegister(getCCUCh, dutyVal);
    // CCU60_vLoadChannelShadowRegister(CCU60_CHANNEL_0, dutyVal);
    ccuCntArr[0] = CCU60_T12;
    dutyVal = PWM_PERIOD_CNT * dutyCyc / 100;
    ccuCntArr[5] = CCU60_T12;
    ccuCntArr[6] = CCU60_T12;
    ccuCntArr[7] = CCU60_T12;
    ccuCntArr[8] = CCU60_T12;
    ccuCntArr[9] = CCU60_T12;
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
    CCU60_vEnableShadowTransfer_CCU60_TIMER_12();
    CCU60_vEnableShadowTransfer_CCU60_TIMER_13();
    ccuCntArr[1] = CCU60_T12;
    ccuCntArr[2] = CCU60_T12PR;
    ccuCntArr[3] = CCU60_CC61R;
    ccuCntArr[4] = CCU60_CC61SR;
}

