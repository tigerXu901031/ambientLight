#include "ledCtrlPrj1.h"

const rgb_type colorArrOrign[color_max] = {
    /* color_green */
    {0, 255, 0},
    /* color_blue */
    {0, 0, 255},
    /* color_red */
    {255, 0, 0},
    /* color_orange */
    {200, 100, 0},
    /* color_yellow */
    {255, 255, 0},
    /* color_purple */
    {204, 0, 255},
    /* color_off */
    {0, 0, 0}};

rgb_type colorArr[color_max] = {
    /* color_green */
    {0, 255, 0},
    /* color_blue */
    {0, 0, 255},
    /* color_red */
    {255, 0, 0},
    /* color_orange */
    {200, 100, 0},
    /* color_yellow */
    {255, 255, 0},
    /* color_purple */
    {204, 0, 255},
    /* color_off */
    {0, 0, 0}};


static void ledMode1Ctrl(ledMode_enum oldInpMode)
{
    static uint8 darknessLevel = 0;
    uint8 j = 0;
    if (oldInpMode != ledMode_1)
    {
        darknessLevel++;
        if (darknessLevel == 2)
        {
            darknessLevel = 0;
        }
        else
        {

        }
        for (j = 0; j < color_max; j++)
        {
            colorArr[j].blue = colorArrOrign[j].blue * (1 - (0.5 * darknessLevel));
            colorArr[j].green = colorArrOrign[j].green * (1 - (0.5 * darknessLevel));
            colorArr[j].red = colorArrOrign[j].red * (1 - (0.5 * darknessLevel));
        }
    }
}

static void ledMode2Ctrl()
{
    uint8 i = 0;
    for (i = 0; i < LED_NUM; i++)
    {
        setSingleLed(ledStripIdx_left, i, colorArr[color_green]);
    }
}

static void ledMode3Ctrl()
{
    static uint8 i = 0;
    uint8 j = 0;

    switch (i)
    {
        /* all green ON first 500ms */
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
            }
            i++;
            break;
        /* all OFF next 500ms */
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
            }
            i++;
            if (i == 10)
                i = 0;
            break;
        default:
            break;
    }
}

static void ledMode4Ctrl(ledMode_enum oldInpMode)
{
    static uint8 i = 0, k = 0;
    uint8 j = 0;

    if (oldInpMode != ledMode_4)
    {
        i = 0;
        k = 0;
    }
    else
    {
    }

    i++;
    if (i == 10)
    {
        i = 0;
        if (k <= 5)
        {
            k++;
        }
    }
    else
    {
    }

    switch (i)
    {
        /* all green ON first 500ms */
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
            }
            i++;
            break;
        /* all OFF next 500ms */
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(k < 5)
            {
                for (j = 0; j < LED_NUM; j++)
                {
                    setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
                    if ((j == 5) || (j == 6))
                        setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
                    else
                    {
                        setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
                    }
                }
            }
            else
            {
                
            }
            break;
        default:
            break;
    }
}

static void ledMode5Ctrl(ledMode_enum oldInpMode)
{
    static uint8 cycCnt = 0;
    static rgb_type streamColorArr[6];
    rgb_type colorTemp;
    uint8 i = 0, j = 0, k = 0;
    
    if(oldInpMode != ledMode_5)
    {
        cycCnt = 0;
        streamColorArr[0] = colorArr[color_red];
        streamColorArr[1] = colorArr[color_orange];
        streamColorArr[2] = colorArr[color_yellow];
        streamColorArr[3] = colorArr[color_green];
        streamColorArr[4] = colorArr[color_blue];
        streamColorArr[5] = colorArr[color_purple];
    }
    cycCnt ++;
    /* each 0.5s update the stream arrary */
    if(cycCnt == 5)
    {
        cycCnt = 0;
        
        colorTemp = streamColorArr[5];
        for(i = 0; i < 5; i ++)
        {
            streamColorArr[5 - i] = streamColorArr[4 - i];
        }
        streamColorArr[0] = colorTemp;
    }
    
    /* light the led according to the stream array */
    for(j = 0; j < LED_NUM; j ++)
    {
        setSingleLed(ledStripIdx_left, j, streamColorArr[j % 4]);
    }
}

static void ledMode6Ctrl()
{
    uint8 i = 0;
    for (i = 0; i < LED_NUM; i++)
    {
        setSingleLed(ledStripIdx_left, i, colorArr[color_blue]);
    }
}

static void ledMode7Ctrl()
{
    static uint8 i = 0;
    uint8 j = 0;

    switch (i)
    {
        /* all green ON first 500ms */
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_red]);
            }
            i++;
            break;
        /* all OFF next 500ms */
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
            }
            i++;
            if (i == 10)
                i = 0;
            break;
        default:
            break;
    }
}

static void ledMode8Ctrl(ledMode_enum oldInpMode)
{
    static uint8 i = 0, ledOnNum = 0;
    uint8 j = 0;

    if(oldInpMode != ledMode_8)
    {
        i = 0;
        ledOnNum = 0;
    }

    i ++;
    if(i == 10)
    {
        i = 0;
        if(ledOnNum < 4)
        {
            ledOnNum ++;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }

    for(j = 0; j < LED_NUM; j ++)
    {
        if(j < ledOnNum)
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_yellow]);
        }
        else
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
        }
    }

}

static void ledMode9Ctrl(ledMode_enum oldInpMode)
{
    static uint8 i = 0, ledOnNum = 0;
    uint8 j = 0;

    if(oldInpMode != ledMode_9)
    {
        i = 0;
        ledOnNum = 0;
    }
    else
    {
        /* do nothing */
    }

    i ++;
    if(i == 10)
    {
        i = 0;
        if(ledOnNum < 4)
        {
            ledOnNum ++;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }

    for(j = 0; j < LED_NUM; j ++)
    {
        if(j > (11 - ledOnNum))
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_yellow]);
        }
        else
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
        }
    }
}

static void ledMode10Ctrl()
{
    static uint8 i = 0;
    uint8 j = 0;

    switch (i)
    {
        /* all green ON first 500ms */
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_yellow]);
            }
            i++;
            break;
        /* all OFF next 500ms */
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
            }
            i++;
            if (i == 10)
                i = 0;
            break;
        default:
            break;
    }
}

static void ledMode11Ctrl()
{
    static uint8 i = 0;
    uint8 j = 0;

    switch (i)
    {
        /* all green ON first 500ms */
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_yellow]);
            }
            i++;
            break;
        /* all OFF next 500ms */
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            for (j = 0; j < LED_NUM; j++)
            {
                setSingleLed(ledStripIdx_left, j, colorArr[color_red]);
            }
            i++;
            if (i == 10)
                i = 0;
            break;
        default:
            break;
    }
}

static void ledMode12Ctrl(ledMode_enum oldInpMode)
{
    static uint8 i = 0, ledOnNum = 0;
    uint8 j = 0;

    if(oldInpMode != ledMode_12)
    {
        i = 0;
        ledOnNum = 3;
    }

    i ++;
    if(i == 5)
    {
        i = 0;
        if(ledOnNum < 6)
        {
            ledOnNum ++;
        }
        else
        {
            ledOnNum = 3;
        }
    }
    else
    {
        
    }

    for(j = 0; j < LED_NUM; j ++)
    {
        if(j < ledOnNum)
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
        }
        else
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
        }
    }

}

static void ledMode13Ctrl(ledMode_enum oldInpMode)
{
    static uint8 i = 0, ledOnNum = 0;
    uint8 j = 0;

    if(oldInpMode != ledMode_13)
    {
        i = 0;
        ledOnNum = 3;
    }

    i ++;
    if(i == 5)
    {
        i = 0;
        if(ledOnNum < 6)
        {
            ledOnNum ++;
        }
        else
        {
            ledOnNum = 3;
        }
    }
    else
    {
        
    }

    for(j = 0; j < LED_NUM; j ++)
    {
        if(j > (11 - ledOnNum))
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
        }
        else
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
        }
    }
}

void ledModeTransitionUpdate(canSignalsType *canSigObj)
{
    static ledMode_enum oldUserInpMode = 0xff;
    switch (canSigObj->input.ledCtrlMode)
    {
    case ledMode_1:
        ledMode1Ctrl(oldUserInpMode);
        break;
    case ledMode_2:
        ledMode2Ctrl();
        break;
    case ledMode_3:
        ledMode3Ctrl();
        break;
    case ledMode_4:
        ledMode4Ctrl(oldUserInpMode);
        break;
    case ledMode_5:
        ledMode5Ctrl(oldUserInpMode);
        break;
    case ledMode_6:
        ledMode6Ctrl();
        break;
    case ledMode_7:
        ledMode7Ctrl();
        break;
    case ledMode_8:
        ledMode8Ctrl(oldUserInpMode);
        break;
    case ledMode_9:
        ledMode9Ctrl(oldUserInpMode);
        break;
    case ledMode_10:
        ledMode10Ctrl();
        break;
    case ledMode_11:
        ledMode11Ctrl();
        break;
    case ledMode_12:
        ledMode12Ctrl(oldUserInpMode);
        break;
    case ledMode_13:
        ledMode13Ctrl(oldUserInpMode);
        break;
    default:
        /* when system onStart without any mode transition command */
        break;
    }
    oldUserInpMode = canSigObj->input.ledCtrlMode;
}