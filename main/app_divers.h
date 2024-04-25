#ifndef __APP_DIVERS_H__
#define __APP_DIVERS_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "freertos/portmacro.h"


#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "string.h"
#include "stdlib.h"
#include "sys/unistd.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"


#include "u8g2.h"
#include "u8x8.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2c.h"
#include "driver/ledc.h"


#include "app_oled.h"
#include "app_iic.h"
#include "app_pwm.h"
#include "app_gpio.h"








#endif // !__APP_DIVERS_H__


