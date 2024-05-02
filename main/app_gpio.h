#ifndef __APP_GPIO_H__
#define __APP_GPIO_H__

#include "app_divers.h"

void app_gpio_init(void);

#define KEY_1 18
#define KEY_2 19

//按键状态结构体
typedef struct key_state{
    int8_t short_flag;    //短按flag
    int8_t long_flag;     //长按flag
    int8_t two_flag;      //双击flag
    int8_t level_state;   //电平状态
    int32_t start_time;   //按下时间
    int32_t end_time;     //松开时间
    int8_t press_cnt;     //按下次数
    int32_t time_gap;     //时间间隔（两次按下）
    int8_t judge_flag;    //按键裁决
}key_state_t;

#endif // !__APP_GPIO_H__
