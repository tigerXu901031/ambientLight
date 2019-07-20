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
        /* darknessLevel: 0 - highest, 1 - middle, 2 - lowest */
        darknessLevel++;
        if (darknessLevel == 3)
        {
            darknessLevel = 0;
        }
        else
        {

        }
        for (j = 0; j < color_max; j++)
        {
            colorArr[j].blue = colorArrOrign[j].blue * (1 - (0.25 * darknessLevel));
            colorArr[j].green = colorArrOrign[j].green * (1 - (0.25 * darknessLevel));
            colorArr[j].red = colorArrOrign[j].red * (1 - (0.25 * darknessLevel));
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
    for(j = 0; j < LED_NUM; j ++)
    {
        if((j >= (5 - k)) && (j <= (6 + k)))
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_green]);
        }
        else
        {
            setSingleLed(ledStripIdx_left, j, colorArr[color_off]);
        }
    }
}

static void ledMode5Ctrl(ledMode_enum oldInpMode)
{
    static uint8 cycCnt = 0;
    static rgb_type streamColorArr[24];
    rgb_type colorTemp;
    uint8 i = 0, j = 0, k = 0;
    
    if(oldInpMode != ledMode_5)
    {
        cycCnt = 0;
        streamColorArr[0] = colorArr[color_red];
        streamColorArr[1] = colorArr[color_red];
        streamColorArr[2] = colorArr[color_red];
        streamColorArr[3] = colorArr[color_red];

        streamColorArr[4] = colorArr[color_orange];
        streamColorArr[5] = colorArr[color_orange];
        streamColorArr[6] = colorArr[color_orange];
        streamColorArr[7] = colorArr[color_orange];

        streamColorArr[8] = colorArr[color_yellow];
        streamColorArr[9] = colorArr[color_yellow];
        streamColorArr[10] = colorArr[color_yellow];
        streamColorArr[11] = colorArr[color_yellow];

        streamColorArr[12] = colorArr[color_green];
        streamColorArr[13] = colorArr[color_green];
        streamColorArr[14] = colorArr[color_green];
        streamColorArr[15] = colorArr[color_green];

        streamColorArr[16] = colorArr[color_blue];
        streamColorArr[17] = colorArr[color_blue];
        streamColorArr[18] = colorArr[color_blue];
        streamColorArr[19] = colorArr[color_blue];

        streamColorArr[20] = colorArr[color_purple];
        streamColorArr[21] = colorArr[color_purple];
        streamColorArr[22] = colorArr[color_purple];
        streamColorArr[23] = colorArr[color_purple];
    }
    cycCnt ++;
    /* each 0.5s update the stream arrary */
    if(cycCnt == 5)
    {
        cycCnt = 0;
        
        colorTemp = streamColorArr[23];
        for(i = 0; i < 23; i ++)
        {
            streamColorArr[23 - i] = streamColorArr[22 - i];
        }
        streamColorArr[0] = colorTemp;
    }
    
    /* light the led according to the stream array */
    for(j = 0; j < LED_NUM; j ++)
    {
        setSingleLed(ledStripIdx_left, j, streamColorArr[j]);
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
        if((j > (11 - ledOnNum)) && (j <= (14 - ledOnNum)))
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
        if((j < ledOnNum) && (j >= ledOnNum - 3))
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