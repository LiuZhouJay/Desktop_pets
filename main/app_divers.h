#ifndef __APP_DIVERS_H__
#define __APP_DIVERS_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "freertos/portmacro.h"
#include "freertos/FreeRTOSConfig.h" 

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
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
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "mqtt_client.h"
#include "nimble/nimble_port.h" 
#include "nimble/nimble_port_freertos.h" 
#include "host/ble_hs.h" 
#include "host/util/util.h" 
#include "console/console.h" 
#include "services/gap/ble_svc_gap.h" 
#include "host/ble_gatt.h"
#include "host/ble_uuid.h"
#include "services/gatt/ble_svc_gatt.h"
#include "esp_nimble_hci.h"

#include "u8g2.h"
#include "u8x8.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2c.h"
#include "driver/ledc.h"
#include "driver/uart.h"

#include "app_oled.h"
#include "app_iic.h"
#include "app_pwm.h"
#include "app_gpio.h"
#include "app_wifi.h"
#include "app_get_weather.h"
#include "app_mqtt.h"
#include "app_uart.h"
#include "app_ble.h"
#include "app_svr.h" 


#endif // !__APP_DIVERS_H__


