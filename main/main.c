#include "app_divers.h"

extern esp_http_client_handle_t client;
extern SemaphoreHandle_t wifi_connect_sendfinish_semaphore;
static void servo_task(void *arg)
{
    set_servo_angle(90,PWM_channel_1);
    while (1)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);   
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

static void get_weather_task(void *arg)
{
    xSemaphoreTake(wifi_connect_sendfinish_semaphore, (TickType_t)portMAX_DELAY);
    while(1){
        // draw(&u8g2);
        app_http_get_weather(client);
    	vTaskDelay(60000 / portTICK_PERIOD_MS);
    }   
}


void app_main(void)
{
    app_get_weather_init();
    app_pwm_init();
    app_gpio_init();
    
    xTaskCreate(servo_task, "servo_task", 2048, NULL, 10, NULL);
    xTaskCreate(oled_task, "oled_task", 2048, NULL, 10, NULL);
    xTaskCreate(get_weather_task, "get_weather_task", 2048, NULL, 10, NULL);
}
    
