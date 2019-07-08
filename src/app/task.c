#include "task.h"

void taskInit()
{

    /* globally disable interrupts */
    PSW_IEN = 0;

/*  -----------------------------------------------------------------------
     Configuration of the System Clock:
    -----------------------------------------------------------------------
 */

    /* 
    - VCO clock used, input clock is connected
    - input frequency is 8.00 MHz
    - system clock is 80.00 MHz
    */

    /* unlock write security */
    MAIN_vUnlockProtecReg();
    /* load PLL control register */
    MAIN_vChangeFreq();

/*  -----------------------------------------------------------------------
     Initialization of the Peripherals:
    -----------------------------------------------------------------------
 */

/* initializes the Capture / Compare Unit 60 (CCU60) */
#if LED_OUTPUT_TYPE == PWN_CTRL
    CCU60_vInit();
#elif LED_OUTPUT_TYPE == GPIO_CTRL
    IO_vInit();
#endif
/*  -----------------------------------------------------------------------
    Initialization of the Bank Select registers:
    -----------------------------------------------------------------------
 */

    /* lock write security */
    MAIN_vLockProtecReg();

/*  -----------------------------------------------------------------------
    Initialization of app module:
    -----------------------------------------------------------------------
 */

    /* globally enable interrupts */
    PSW_IEN = 1;
}

/* task will be running in this 100ms task cycle
   so far using while loop to manually realize the
   scheduler 
   So first do an very rough estimation of 100ms cycle.
   Later add an time stamp at the entry of this function
   and wait for some while to 
    1. change led strip mode
    2. CAN message Rx / Tx 
 */
void taskSlow()
{
    /* TODO: add entry time stamp record and some delay logic
       to ensure the time interval between two taskSlow is 100ms */
    /* test purpose only */
    rgb_type rgbVal;
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 0, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 1, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 2, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 3, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 4, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 5, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 6, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 7, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 8, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 9, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 10, rgbVal);
    rgbVal.blue = 0xf0, rgbVal.red = 0xaa, rgbVal.green = 0xaa;
    setSingleLed(ledStripIdx_left, 11, rgbVal);

    /* get the user input from can */
    

    /* according to the user input then do the led mode transition */
    ledModeTransitionUpdate(0xff);

    /* encode all the led strip */
    ledRgbEncodeUpdate(ledStripIdx_left);
    // ledRgbEncodeUpdate(ledStripIdx_center);
    // ledRgbEncodeUpdate(ledStripIdx_right);
}

/* task will be running in this 1.25us task cycle
    1. encode the 24-bit NZR communication protocol
       to the single led
 */
void taskFast()
{
    ledUpdate(ledStripIdx_left);
    // ledUpdate(ledStripIdx_right);
    // ledUpdate(ledStripIdx_center);
}