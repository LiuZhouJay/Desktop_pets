#ifndef __APP_GET_WEATHER_H__
#define __APP_GET_WEATHER_H__

#include "app_divers.h"

void app_get_weather_init(void);
void app_http_get_weather(esp_http_client_handle_t client);

#endif