#include "app_divers.h"

void app_main(void)
{
    app_wifi_init();
    app_get_weather_init();
    app_mqtt_init();
    app_pwm_init();
    app_gpio_init();
    app_uart_init();
    app_ble_init();
    app_oled_init();
}
    
