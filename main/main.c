#include "app_divers.h"

static EventBits_t r_event;

extern EventGroupHandle_t Event_Handle;
extern esp_http_client_handle_t client;

extern char mqtt_data[100];

static void servo_task(void *arg)
{
    while (1)
    {
        app_set_angle(mqtt_data);
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
    r_event = xEventGroupWaitBits(Event_Handle,  /* 事件对象句柄 */
                                  (0x01 << 0),/* 接收线程感兴趣的事件 */
                                  pdTRUE,   /* 退出时清除事件位 */
                                  pdTRUE,   /* 满足感兴趣的所有事件 */
                                  (TickType_t)portMAX_DELAY);/* 指定超时事件,一直等 */

    while(1){
        app_http_get_weather(client);
    	vTaskDelay(60000 / portTICK_PERIOD_MS);
    }   
}


void app_main(void)
{
    app_wifi_init();
    app_get_weather_init();
    app_mqtt_init();
    app_pwm_init();
    app_gpio_init();
    
    xTaskCreate(servo_task, "servo_task", 2048, NULL, 10, NULL);
    xTaskCreate(oled_task, "oled_task", 2048, NULL, 10, NULL);
    xTaskCreate(get_weather_task, "get_weather_task", 2048, NULL, 10, NULL);
}
    
