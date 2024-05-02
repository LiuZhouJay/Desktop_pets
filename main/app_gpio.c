#include "app_gpio.h"

//按键部分
 
enum {JUDGE = 0, SINGLE = 1, DBCLICK = 2};    //状态机的状态类型
key_state_t g_key[2];    //按键状态全局变量
 
SemaphoreHandle_t key_read_semaphore = NULL;

//定时器回调函数，已经配置为10ms触发一次定时器中断回调
void app_key_read(void)
{
        static int32_t press_time_cnt[2] = {0};        //按下持续计数值
        static int32_t wait_press_cnt[2] = {0};        //等待按键按下计数值
        g_key[0].level_state =    gpio_get_level(KEY_1);//读取引脚电平值
        g_key[1].level_state =    gpio_get_level(KEY_2);       
        // g_key[2].level_state =    HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);        
        // g_key[3].level_state =    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);    
        
        for(int i=0; i<2; i++)
        {
            switch(g_key[i].judge_flag)
            {
                case JUDGE:
                    if(g_key[i].level_state == 0)         //按下
                    {
                        if(g_key[i].press_cnt == 0)
                            g_key[i].judge_flag = 1;
                        else
                            g_key[i].judge_flag = 2;
                    }else if(g_key[i].level_state == 1)     //松开
                    {        
                        if(g_key[i].press_cnt == 1)                     //双击的第一次按下已经松开了
                        {
                            g_key[i].judge_flag = 2;
                        }
                    }
                    break;
                    
                case SINGLE:    //第一次按下，长按、短按
                    if(g_key[i].level_state == 0)        //按键按下
                    {
                        press_time_cnt[i]++;
                    }else if(g_key[i].level_state == 1)    //按键松开
                    {
                        if(press_time_cnt[i] > 50)       //长按（按下持续时间>=500ms）
                        {
                            g_key[i].long_flag  = 1;     //长按标志置1
                            g_key[i].short_flag = 0;
                            g_key[i].two_flag   = 0;
                            g_key[i].press_cnt  = 0;     //长按则清除双击的按下按键计数 
                            
                        }else if(press_time_cnt[i] > 9)  //短按(持续时间>=90ms)
                        {
                            g_key[i].short_flag = 0;     //短按标志需要进一步判断，在一定时间内，如果没有第二次按下，则是短按
                            g_key[i].long_flag  = 0;
                            g_key[i].two_flag   = 0;
                            if(g_key[i].press_cnt == 0)
                            {
                                g_key[i].press_cnt = 1;  //记录双击的第一次按下
                            }
                        }
                        g_key[i].judge_flag = 0;        
                        press_time_cnt[i] = 0;           //清空按下和松开间的计数
                    }
                    break;
                
                case DBCLICK:
                    if(g_key[i].level_state == 1) //按键松开
                    {
                        if(wait_press_cnt[i]++ >= 25)    //250ms内未按下第二次，说明为短按
                        {
                            g_key[i].short_flag = 1;    //短按标志位置1
                            g_key[i].long_flag  = 0;
                            g_key[i].two_flag   = 0;
                            g_key[i].press_cnt  = 0;
                            g_key[i].judge_flag = 0;
                            wait_press_cnt[i]   = 0;    
                        }
                        
                    }else if(g_key[i].level_state == 0)    //第二次按键按下
                    {
                        if((press_time_cnt[i]++ >=7) && (wait_press_cnt[i] >= 5))        //50~250ms内第二次按下且按下的时间大于70ms，则是双击
                        {
                            g_key[i].two_flag   = 1;    //双击标志置1
                            g_key[i].short_flag = 0;
                            g_key[i].long_flag  = 0;
                            g_key[i].press_cnt  = 0;
                            g_key[i].judge_flag = 0;
                            wait_press_cnt[i]   = 0;
                            press_time_cnt[i]   = 0;
                        }
                    }
                    break;
                    
            }
        }
        xSemaphoreGive(key_read_semaphore);
}

static void key_read_task(void *arg)
{
    while(1){
    	vTaskDelay(10 / portTICK_PERIOD_MS);
        app_key_read();
    }   
}

void app_gpio_init(void)
{
    gpio_reset_pin(KEY_1);
    gpio_reset_pin(KEY_2);
    gpio_set_direction(KEY_2,GPIO_MODE_INPUT);
    gpio_set_direction(KEY_1,GPIO_MODE_INPUT);

    key_read_semaphore = xSemaphoreCreateBinary();
    xTaskCreate(key_read_task, "key_read_task", 2048, NULL, 10, NULL);
}


