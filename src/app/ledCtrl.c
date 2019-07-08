#include "ledCtrl.h"

const rgb_type colorArr[color_max] = {
                                        /* color_green */
                                        {0  , 255, 0  },
                                        /* color_blue */
                                        {0  , 0  , 255},
                                        /* color_red */
                                        {255, 0  , 0  },
                                        /* color_orange */
                                        {200, 100, 0  },
                                        /* color_yellow */
                                        {255, 255, 0  },
                                        /* color_purple */
                                        {204, 0  , 255},
                                        /* color_off */
                                        {0  , 0  , 0  }
};

/* TODO: need to check which mode need the old mode state
   if needed then transfer the old state as an argument */

static void ledMode1Ctrl()
{
    
}

static void ledMode2Ctrl()
{
    uint8 i = 0;
    for(i = 0; i < LED_NUM; i ++)
    {
        setSingleLed(ledStripIdx_left, i, colorArr[color_green]);
    }
    
}

static void ledMode3Ctrl()
{
    uint8 i = 0, j = 0;
    
    switch(i)
    {
        /* all green ON first 500ms */
        case 0: case 1: case 2: case 3: case 4:
            for(j = 0; j < LED_NUM; j ++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
            }
            i ++;
            break;
        /* all OFF next 500ms */
        case 5: case 6: case 7: case 8: case 9:
            for(j = 0; j < LED_NUM; j ++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
            }
            i ++;
            if(i = 10)
                i = 0;
            break;
        default:
            break;
    }
}

static void ledMode4Ctrl()
{
    uint8 i = 0, j = 0;
    
    switch(i)
    {
        /* all green ON first 500ms */
        case 0: case 1: case 2: case 3: case 4:
            for(j = 0; j < LED_NUM; j ++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
            }
            i ++;
            break;
        /* all OFF next 500ms */
        case 5: case 6: case 7: case 8: case 9:
            for(j = 0; j < LED_NUM; j ++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
                if((j == 5) || (j == 6))
                    setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
                else{}
            }
            i ++;
            if(i = 10)
                i = 0;
            else{}
            break;
        default:
            break;
    }
}

static void ledMode5Ctrl()
{
    
}

static void ledMode6Ctrl()
{
}

static void ledMode7Ctrl()
{
}

static void ledMode8Ctrl()
{
}

static void ledMode9Ctrl()
{
}

static void ledMode10Ctrl()
{
}

static void ledMode11Ctrl()
{
}

static void ledMode12Ctrl()
{
}

static void ledMode13Ctrl()
{
}

static void ledMode14Ctrl()
{
}

static void ledMode15Ctrl()
{
}

static void ledMode16Ctrl()
{
}

static void ledMode17Ctrl()
{
}

static void ledMode18Ctrl()
{
}

void ledModeTransitionUpdate(ledMode_enum userInpMode)
{
    switch (userInpMode)
    {
        case ledMode_1:
            ledMode1Ctrl();
            break;
        case ledMode_2:
            ledMode2Ctrl();
            break;
        case ledMode_3:
            ledMode3Ctrl();
            break;
        case ledMode_4:
            ledMode4Ctrl();
            break;
        case ledMode_5:
            ledMode5Ctrl();
            break;
        case ledMode_6:
            ledMode6Ctrl();
            break;
        case ledMode_7:
            ledMode7Ctrl();
            break;
        case ledMode_8:
            ledMode8Ctrl();
            break;
        case ledMode_9:
            ledMode9Ctrl();
            break;
        case ledMode_10:
            ledMode10Ctrl();
            break;
        case ledMode_11:
            ledMode11Ctrl();
            break;
        case ledMode_12:
            ledMode12Ctrl();
            break;
        case ledMode_13:
            ledMode13Ctrl();
            break;
        case ledMode_14:
            ledMode14Ctrl();
            break;
        case ledMode_15:
            ledMode15Ctrl();
            break;
        case ledMode_16:
            ledMode16Ctrl();
            break;
        case ledMode_17:
            ledMode17Ctrl();
            break;
        case ledMode_18:
            ledMode18Ctrl();
            break;
        default:
            /* when system start without any mode transition command */
            break;
    }
}