#ifndef __APP_PWM_H__
#define __APP_PWM_H__

#include "app_divers.h"

void app_pwm_init(void);
void set_servo_angle(uint8_t angle,ledc_channel_t chanel);
void app_set_angle(char *data);

#define PWM_channel_1 LEDC_CHANNEL_1
#define PWM_channel_2 LEDC_CHANNEL_2
#define PWM_channel_3 LEDC_CHANNEL_3
#define PWM_channel_4 LEDC_CHANNEL_4

#endif // !__APP_PWM_H__
