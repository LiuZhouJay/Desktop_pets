#include "app_divers.h"

static void servo_task(void *arg)
{
    while (1)
    {
        set_servo_angle(90,PWM_channel_1);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        set_servo_angle(180,PWM_channel_2);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        set_servo_angle(180,PWM_channel_1);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        set_servo_angle(90,PWM_channel_2);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

static void oled_task(void *arg)
{
    // 初始u8g2
    u8g2_t u8g2;
    u8g2Init(&u8g2);
    while(1){
        // draw(&u8g2);
        app_oled_init(u8g2);
    	vTaskDelay(50 / portTICK_PERIOD_MS);
    }   
}

void app_main(void)
{
    app_pwm_init();
    
    xTaskCreate(servo_task, "servo_task", 2048, NULL, 10, NULL);
    xTaskCreate(oled_task, "oled_task", 2048, NULL, 10, NULL);
}
    
