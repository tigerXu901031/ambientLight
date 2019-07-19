#ifndef __LEDCTRL_H__
#define __LEDCTRL_H__

#include "../srv/led.h"
#include "../srv/canSrv.h"

typedef enum{
   color_green,
   color_blue,
   color_red,
   color_orange,
   color_yellow,
   color_purple,
   color_off,
   color_max,
}color_enum;


/* 
 ********************************************************
   mode 1:  根据外部亮度调节全局亮度，无特殊说明均使用全局亮度值将亮
            度分为三档，高(100%功率)，中（75%功率），低(50%功率)
   mode 2:  所有灯常绿
   mode 3:  所有灯闪烁的绿光，0.5s亮，0.5s灭
   mode 4:  从闪烁状态，从中心灯开始常绿，直至5s后所有灯常亮
   mode 5:  流水灯，四灯一组，红橙黄绿蓝紫六色，0.5s移动一灯
   mode 6:  所有灯蓝色
   mode 7:  所有灯闪烁的红色，亮度最大
   mode 8:  从最左侧的灯开始亮黄灯，每1s向中间增加1灯，最终亮4灯
   mode 9:  从最右侧的灯开始亮黄灯，每1s向中间增加1灯，最终亮4灯
   mode 10: 所有灯为闪烁黄色，0.5s亮，0.5s灭
   mode 11: 所有灯交替闪烁黄色和红色，0.5s红，0.5s黄
   mode 12: 从最右侧的灯开始3灯绿色，0.5s向左运动一灯，运动至正中间位
            置重复初始情况从1灯开始亮
   mode 13: 从最左侧的灯开始3灯绿色，0.5s向右运动一灯，运动至正中间位
            置重复初始情况从1灯开始亮
 ********************************************************
 */
typedef enum{
    ledMode_1 = 1,
    ledMode_2,
    ledMode_3,
    ledMode_4,
    ledMode_5,
    ledMode_6,
    ledMode_7,
    ledMode_8,
    ledMode_9,
    ledMode_10,
    ledMode_11,
    ledMode_12,
    ledMode_13,
    ledMode_max,
}ledMode_enum;



extern void ledModeTransitionUpdate(canSignalsType *canSigObj);

#endif