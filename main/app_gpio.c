#include "app_gpio.h"

int app_key_read(int i)
{
    if(gpio_get_level(i) == 0)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
        if(gpio_get_level(i) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else{
        return 1;
    }
    
}

void app_gpio_init(void)
{
    gpio_reset_pin(18);
    gpio_reset_pin(19);
    gpio_set_direction(19,GPIO_MODE_INPUT);
    gpio_set_direction(18,GPIO_MODE_INPUT);
    
}
