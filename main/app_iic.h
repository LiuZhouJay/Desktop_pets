
#ifndef __APP_IIC_H_
#define __APP_IIC_H_

#define u8 unsigned char
#define u32 unsigned int

#include "app_divers.h"

#define u8         unsigned char  // ?unsigned char ????
#define MAX_LEN    128  //
#define OLED_ADDRESS  0x3C // oled
#define OLED_CMD   0x00  //
#define OLED_DATA  0x40  //

/* USER CODE BEGIN Prototypes */
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void u8g2Init(u8g2_t *u8g2a);
void draw(u8g2_t *u8g2);
// void testDrawPixelToFillScreen(u8g2_t *u8g2);


#endif /* MAIN_OLED_H_ */




