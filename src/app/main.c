#include "task.h"
#include "ledCtrl.h"
#include "../srv/led.h"

void main()
{
     taskInit();

    while(1)
    {  
        taskFast();
        taskSlow();
    }
}