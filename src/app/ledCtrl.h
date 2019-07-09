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
    /* 根据外部亮度调节全局亮度，无特殊说明均使用全局亮度值
       将亮度分为三档，高（100%功率），中（75%功率），低（50%功率）  */
    ledMode_1 = 1,
    /* T-zone全部灯常绿 */
    ledMode_2,
    /* T-zone全部灯闪烁绿光，0.5s灭，0.5s亮  */
    ledMode_3,
    /* 从6，7两灯开始常亮，其余灯保持状态3中的闪烁频率，每次亮向外的两颗灯
       进入常亮状态，直至恢复至状态2 */
    ledMode_4,
    /* 三区构成一个大流水灯，四灯一组，红橙黄绿蓝紫六色，0.5s移动一灯 */
    ledMode_5,
    /* T-zone闪烁的黄色灯0.3s灭，0.3s亮（表示低紧急度） */
    ledMode_6,
    /* 三区黄红交替闪烁0.3s黄0.3s红，并且将亮度调至最高（表示高紧急度）（车
       内其余内饰也应有配合提醒） */
    ledMode_7,
    /* T-zone 全部灯蓝绿闪烁0.5s蓝0.5s绿，3s后切换为低亮度蓝色 */
    ledMode_8,
    /* T-zone 全部灯为低亮度蓝色 */
    ledMode_9,
    /* 从T-zone 1 和L-zone的11、12开始，闪烁黄色0.3s亮0.3s灭，每次闪烁多亮
       三颗灯（T-zone+1，L-zone+2）直至T-zone左侧（1-6）和L-zone全部进入闪
       烁状态 */
    ledMode_10,
    /* 从T-zone 12 和R-zone的1、2开始，闪烁黄色0.3s亮0.3s灭，每次闪烁多亮
       三颗灯（T-zone+1，L-zone+2）直至T-zone右侧（7-12）和R-zone全部进入
       闪烁状态 */
    ledMode_11,
    /* 三区全部灯闪烁红色，0.3s亮，0.3s灭 */
    ledMode_12,
    /* 三区黄红交替闪烁0.3s黄0.3s红 */
    ledMode_13,
    /* 从T-zone的1-4开始四灯绿色，0.5s向左运动一灯即L-zone，运动L-zone 1灯
       开始重复返回T-zone 4灯 */
    ledMode_14,
    /* 从T-zone的1-4开始四灯绿色，0.5s向左运动一灯即L-zone，运动L-zone 1灯
       开始重复返回T-zone 4灯 */
    ledMode_15,
    /* 从T-zone的8-12开始四灯绿色，0.5s向右运动一灯即R-zone，运动至R-zone
       12灯开始重复返回T-zone 8灯 */
    ledMode_16,
    /* 从L-zone 1开始，闪烁黄色0.3s亮0.3s灭；每次闪烁一个灯；逐步过渡到
       2,3,4,5,6,7,8,9,10,11,12; 然后循环开始，重新从1，逐步再次过度到12； */
    ledMode_17,
    /* 从L-zone 12开始，闪烁黄色0.3s亮0.3s灭；每次闪烁一个灯；逐步过渡到
       11,10,9,8,7,6,5,4,3,2,1; 然后循环开始，重新从11，逐步再次过度到1 */
    ledMode_18,
    ledMode_max,
}ledMode_enum;

extern void ledModeTransitionUpdate(ledMode_enum userInpMode);

#endif