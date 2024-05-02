#ifndef __APP_OLED_H__
#define __APP_OLED_H__

#include "app_divers.h"

void app_oled_init(void);

typedef struct
{
  char* str;
  int len;
}SETTING_LIST;

#endif // !__APP_OLED_H__


