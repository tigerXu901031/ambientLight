#include "canSrv.h"

static void canMsg0x505Upack(canSignalsType* canSignalObj)
{
    canSignalObj->input.ledCtrlMode = msgObj0x505.ubData[0];
}

void canUpdate(canSignalsType* canSignalObj)
{
    canMsg0x505Upack(canSignalObj);
}