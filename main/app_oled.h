#ifndef __APP_OLED_H__
#define __APP_OLED_H__

#include "app_divers.h"

void app_oled_init(u8g2_t u8g2);
void draw(u8g2_t *u8g2);
void draw_progress_bar(u8g2_t *u8g2);

typedef struct
{
    char*str;
}SETTING_LIST;

#endif // !__APP_OLED_H__


