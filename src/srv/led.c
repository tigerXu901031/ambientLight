/* 
    WS2812C NRZ signal communication mode
    1. provid the ledSet(idx, rgbVal) function to the app
    2. convert the n * rgbVal into a time serise of pwm duty cycle
    3. 
*/
#include "led.h"

ledStrip_type ledStrip_Obj[ledStripIdx_max];

void ledInit()
{
    /* clear the led strip object */
}

/* invoked by APP in a slow task while the light mode has switched
   then refresh all the led at the same cycle
 */
void setSingleLed(ledStripIdx_type ledStripIdx, uint8 ledIdx, rgb_type rgbVal)
{
    ledStrip_Obj[ledStripIdx].led[ledIdx].red = rgbVal.red;
    ledStrip_Obj[ledStripIdx].led[ledIdx].green = rgbVal.green;
    ledStrip_Obj[ledStripIdx].led[ledIdx].blue = rgbVal.blue;
}

/* invoked by the PWM interrupt in (800kHz)1.25us cycle and set the next
   bit equivalent duty cycle, then move the current pointer 
 */
void ledSignalBitTx(ledStripIdx_type ledStripIdx)
{
    uint8 curBit = 0;

    /* locate to the current bit */
    if(ledStrip_Obj[ledStripIdx].curBitIdx < 8)
    {
        curBit = (ledStrip_Obj[ledStripIdx].led[ledStrip_Obj[ledStripIdx].curLedIdx].green >> ledStrip_Obj[ledStripIdx].curBitIdx) & 0x01;
    }
    else if((ledStrip_Obj[ledStripIdx].curBitIdx >= 8 )&& (ledStrip_Obj[ledStripIdx].curBitIdx < 16))
    {
        curBit = (ledStrip_Obj[ledStripIdx].led[ledStrip_Obj[ledStripIdx].curLedIdx].red >> (ledStrip_Obj[ledStripIdx].curBitIdx - 8)) & 0x01;
    }
    else if((ledStrip_Obj[ledStripIdx].curBitIdx >= 16) && (ledStrip_Obj[ledStripIdx].curBitIdx < 24))
    {
        curBit = (ledStrip_Obj[ledStripIdx].led[ledStrip_Obj[ledStripIdx].curLedIdx].blue >> (ledStrip_Obj[ledStripIdx].curBitIdx) - 16) & 0x01;
    }
    else{
        /* 24, 25 ,26, ... idel bit */
    }

    /* interpret to the duty cycle */
    if(curBit == 1)
    {
        /* LED_BIT_HIGH_DUTY */
        setPwmDutyCyc((uint8)ledStripIdx, LED_BIT_HIGH_DUTY);
    }
    else if(curBit == 0)
    {
        /* LED_BIT_LOW_DUTY */
        setPwmDutyCyc((uint8)ledStripIdx, LED_BIT_LOW_DUTY);
    }
    else{
        /* Something wrong */
    }

    /* move both the led pointer and bit pointer */
    if(ledStrip_Obj[ledStripIdx].curBitIdx < 28)
    {
        ledStrip_Obj[ledStripIdx].curBitIdx ++;
    }
    else{
        ledStrip_Obj[ledStripIdx].curBitIdx = 0;
        if(ledStrip_Obj[ledStripIdx].curLedIdx < LED_NUM)
        {
            ledStrip_Obj[ledStripIdx].curLedIdx ++;
        }
        else{
            ledStrip_Obj[ledStripIdx].curLedIdx = 0;
        }
    }
}