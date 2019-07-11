#ifndef __CAN_H__
#define __CAN_H__

#include "../drv/can.h"
#include "type.h"

typedef struct
{
    struct
    {
        uint8 ledCtrlMode;
    }input;
    struct
    {
        uint8 dummySig;
    }output;

}canSignals;

extern void canUpdate(canSignals* canSignalObj);

#endif