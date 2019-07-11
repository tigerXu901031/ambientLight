#include "canSrv.h"

static void canMsg0x505Upack(canSignals* canSignalObj)
{
    canSignalObj->input.ledCtrlMode = msgObj0x505.ubData[0];
}

void canUpdate(canSignals* canSignalObj)
{
    canMsg0x505Upack(canSignalObj);
}