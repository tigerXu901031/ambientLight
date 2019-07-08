/* 
    WS2812C NRZ signal communication mode
    1. provid the ledSet(idx, rgbVal) function to the app
    2. convert the n * rgbVal into a time serise of pwm duty cycle
    3. 
*/
#include "led.h"

ledStrip_type ledStrip_Obj[ledStripIdx_max];
uint8 ledDutyCycleArrary[ledStripIdx_max][LED_NUM * BITS_FOR_EACH_LED];

static void setLedBit0()
{
    IO_P10_4 = 1;
    delay(TIME_FOR_BIT1_LOW_NS / TIME_NS_PER_INSTRUCTION_CYCLE);
    IO_P10_4 = 0;
    delay(TIME_FOR_BIT1_HIGH_NS / TIME_NS_PER_INSTRUCTION_CYCLE);
}

static void setLedBit1()
{
    IO_P10_4 = 1;
    delay(TIME_FOR_BIT1_HIGH_NS / TIME_NS_PER_INSTRUCTION_CYCLE);
    IO_P10_4 = 0;
    delay(TIME_FOR_BIT1_LOW_NS / TIME_NS_PER_INSTRUCTION_CYCLE);
}

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
void ledRgbEncode(ledStripIdx_type ledStripIdx)
{
    uint8 curBitEncode = 0;
    uint8 encodeVal = 0;
    uint8 i = 0, j = 0;
    uint16 k = 0;
    for(i = 0; i < LED_NUM; i ++)
    {
        /* 24 bit for rgb value and 6 bit for idle time */
        for(j = 0; j < BITS_FOR_EACH_LED; j ++)
        {
            /* resolve into single bit */
            if(j < 8)
            {
                curBitEncode = (ledStrip_Obj[ledStripIdx].led[ledStrip_Obj[ledStripIdx].curLedIdx].green >> (7 - j)) & 0x01;
            }
            else if((j >= 8 )&& (j < 16))
            {
                curBitEncode = (ledStrip_Obj[ledStripIdx].led[ledStrip_Obj[ledStripIdx].curLedIdx].red >> (7 - (j - 8))) & 0x01;
            }
            else if((j >= 16) && (j < 24))
            {
                curBitEncode = (ledStrip_Obj[ledStripIdx].led[ledStrip_Obj[ledStripIdx].curLedIdx].blue >> (7 - (j - 16)) & 0x01);
            }
            else
            {

            }

            #if LED_OUTPUT_TYPE == PWN_CTRL
            /* convert the bit into duty cycle */
            /* interpret to the duty cycle */
            if(curBitEncode == 1)
            {
                /* duty cycle code for bit 1 */
	            encodeVal = (uint16)PWM_PERIOD_CNT * (uint16)LED_BIT_HIGH_DUTY / 100;

            }
            else if(curBitEncode == 0)
            {
                /* duty cycle code for bit 0 */
                encodeVal = PWM_PERIOD_CNT * LED_BIT_LOW_DUTY / 100;

            }
            else
            {

            }
            #elif LED_OUTPUT_TYPE == GPIO_CTRL
            encodeVal = curBitEncode;
            #endif

            ledDutyCycleArrary[ledStripIdx][k] = encodeVal;
            k ++;
        }
    }
}

void refreshLedStrip(ledStripIdx_type ledStripIdx)
{
    uint16 i = 0;
    for(i = 0; i < LED_NUM * BITS_FOR_EACH_LED; i ++)
    {
        
    }
}