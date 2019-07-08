#include "task.h"

void taskInit()
{

    /* globally disable interrupts */
    PSW_IEN        =  0;          

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

    task10Hz();

    /* globally enable interrupts */
    PSW_IEN        =  1;          
}

/* task will be running in this 100ms task cycle
    1. change led strip mode
    2. CAN message Rx / Tx 
 */
void task10Hz()
{
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

        /* test purpose only */
    ledRgbEncode(ledStripIdx_left);
    // ledRgbEncode(ledStripIdx_center);
    // ledRgbEncode(ledStripIdx_right);
}

/* task will be running in this 1.25us task cycle
    1. encode the 24-bit NZR communication protocol
       to the single led
 */
void task800kHz()
{

}