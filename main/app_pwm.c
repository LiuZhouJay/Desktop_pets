#include "app_pwm.h"


//205  410  614 819 1024 
void set_servo_angle(uint8_t angle,ledc_channel_t chanel)
{
    switch (angle)
    {
    case 0:
        ledc_set_duty(LEDC_LOW_SPEED_MODE,chanel,205);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,chanel);
        break;
    case 45:
        ledc_set_duty(LEDC_LOW_SPEED_MODE,chanel,410);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,chanel);
        break;
    case 90:
        ledc_set_duty(LEDC_LOW_SPEED_MODE,chanel,614);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,chanel);
        break;
    case 135:
        ledc_set_duty(LEDC_LOW_SPEED_MODE,chanel,819);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,chanel);
        break;
    case 180:
        ledc_set_duty(LEDC_LOW_SPEED_MODE,chanel,1024);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,chanel);
        break;
    default:
        break;
    }
}

void app_pwm_init(void) 
{
    ledc_timer_config_t ledc_timer = { 
        .duty_resolution = LEDC_TIMER_13_BIT,	// PWM占空比分辨率
        .freq_hz = 50,						// PWM信号频率
        .speed_mode = LEDC_LOW_SPEED_MODE,				// 定时器模式
        .timer_num = LEDC_TIMER_0				// 定时器序号;使用哪个定时器0-3;
    };
    ledc_channel_config_t ledc_channel1 = { 
        .channel =	LEDC_CHANNEL_1,	// LED控制器通道号, 
        .duty = 8191, 
        .gpio_num = 0,				// LED控制器通道对应GPIO, 
        .speed_mode = LEDC_LOW_SPEED_MODE, // 模式, 
        .timer_sel = LEDC_TIMER_0,   		// 使用哪个定时器0-3
    };
    ledc_channel_config_t ledc_channel2 = { 
        .channel =	LEDC_CHANNEL_2,	// LED控制器通道号, 
        .duty = 8191, 
        .gpio_num = 1,				// LED控制器通道对应GPIO, 
        .speed_mode = LEDC_LOW_SPEED_MODE, // 模式, 
        .timer_sel = LEDC_TIMER_0,   		// 使用哪个定时器0-3
    };
    ledc_channel_config_t ledc_channel3 = { 
        .channel =	LEDC_CHANNEL_3,	// LED控制器通道号, 
        .duty = 8191, 
        .gpio_num = 2,				// LED控制器通道对应GPIO, 
        .speed_mode = LEDC_LOW_SPEED_MODE, // 模式, 
        .timer_sel = LEDC_TIMER_0,   		// 使用哪个定时器0-3
    };
    ledc_channel_config_t ledc_channel4 = { 
        .channel =	LEDC_CHANNEL_4,	// LED控制器通道号, 
        .duty = 8191, 
        .gpio_num = 3,				// LED控制器通道对应GPIO, 
        .speed_mode = LEDC_LOW_SPEED_MODE, // 模式, 
        .timer_sel = LEDC_TIMER_0,   		// 使用哪个定时器0-3
    };
    // 配置LED控制器
    ledc_timer_config(&ledc_timer);

    // 配置LED控制器
    ledc_channel_config(&ledc_channel1);
    ledc_channel_config(&ledc_channel2);
    ledc_channel_config(&ledc_channel3);
    ledc_channel_config(&ledc_channel4);

}