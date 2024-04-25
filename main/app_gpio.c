#include "app_gpio.h"

void app_gpio_init(void)
{
    gpio_reset_pin(0);
    gpio_reset_pin(1);
    gpio_set_direction(0,GPIO_MODE_OUTPUT);
    gpio_set_direction(1,GPIO_MODE_INPUT);
    while(1)
    {
        if(gpio_get_level(1) == 1){
                gpio_set_level(0,0);
                printf("test: %d",gpio_get_level(1));
                vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else{
            gpio_set_level(0,1);
            printf("test: %d",gpio_get_level(1));
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
    
}
