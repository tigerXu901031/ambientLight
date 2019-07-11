#ifndef __LEDCTRL_H__
#define __LEDCTRL_H__

#include "../srv/led.h"

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

typedef enum{
    /* 切换亮度基准，亮/暗，暗为亮的一半  */
    ledMode_1 = 1,
    /* 所有灯常绿 */
    ledMode_2,
    /* 所有灯闪烁的绿光，0.5s亮，0.5s灭 */
    ledMode_3,
    /* 从闪烁状态，从中心灯开始常绿，直至5s后所有灯常亮 */
    ledMode_4,
    /* 流水灯，四灯一组，红橙黄绿蓝紫六色，0.5s移动一灯 */
    ledMode_5,
    /* 所有灯蓝色 */
    ledMode_6,
    /* 所有灯闪烁的红色，亮度最大 */
    ledMode_7,
    /* 从最左侧的灯开始亮黄灯，每1s向中间增加1灯，最终亮4灯 */
    ledMode_8,
    /* 从最右侧的灯开始亮黄灯，每1s向中间增加1灯，最终亮4灯 */
    ledMode_9,
    /* 所有灯为闪烁黄色，0.5s亮，0.5s灭 */
    ledMode_10,
    /* 所有灯交替闪烁黄色和红色，0.5s红，0.5s黄 */
    ledMode_11,
    /* 从最右侧的灯开始3灯绿色，0.5s向左运动一灯，运动至正中间位置重复
       初始情况从1灯开始亮 */
    ledMode_12,
    /* 从最左侧的灯开始3灯绿色，0.5s向右运动一灯，运动至正中间位置重复
       初始情况从1灯开始亮 */
    ledMode_13,
    ledMode_max,
}ledMode_enum;



extern void ledModeTransitionUpdate(ledMode_enum userInpMode);

#endif