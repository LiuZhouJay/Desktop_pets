
//******************************************************************************/

#include "app_iic.h"

#define I2C_HOST  0

#define EXAMPLE_LCD_PIXEL_CLOCK_HZ    (400 * 1000)

#define EXAMPLE_PIN_NUM_SDA           5
#define EXAMPLE_PIN_NUM_SCL           4
//使用OLED的硬件地址，i2c_master_write_to_device()函数内会转换为写地址
#define EXAMPLE_I2C_HW_ADDR           0x3C

#define I2C_MASTER_TIMEOUT_MS       1000

 void i2c_master_init(void)
{
	  i2c_config_t i2c_conf = {
	        .mode = I2C_MODE_MASTER,
	        .sda_io_num = EXAMPLE_PIN_NUM_SDA,
	        .scl_io_num = EXAMPLE_PIN_NUM_SCL,
	        .sda_pullup_en = GPIO_PULLUP_ENABLE,
	        .scl_pullup_en = GPIO_PULLUP_ENABLE,
	        .master.clk_speed = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
	    };
	    ESP_ERROR_CHECK(i2c_param_config(I2C_HOST, &i2c_conf));
	    ESP_ERROR_CHECK(i2c_driver_install(I2C_HOST, I2C_MODE_MASTER, 0, 0, 0));
}


uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */

    static uint8_t buf[128];
    static uint8_t buf_idx;

    switch (msg)
    {
    case U8X8_MSG_BYTE_INIT:
    {
        i2c_master_init();
        break;
    }
    case U8X8_MSG_BYTE_START_TRANSFER:
    {
        buf_idx = 0;
        break;
    }
    case U8X8_MSG_BYTE_SEND:
    {
        while (arg_int > 0)
        {
            buf[buf_idx++] = *(uint8_t*)arg_ptr++;
            arg_int--;
        }
        break;
    }
    case U8X8_MSG_BYTE_END_TRANSFER:
    {
        int ret;
        ret = i2c_master_write_to_device(I2C_HOST, OLED_ADDRESS, buf, buf_idx, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
		if (ret!= ESP_OK) return 0;
		else break;
    }
    case U8X8_MSG_BYTE_SET_DC:
        break;

    default:
        return 0;
    }

    return 1;
}



uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	//使用硬件IIC，部分分支可忽略不写
    switch (msg)
    {
    case U8X8_MSG_DELAY_100NANO: // delay arg_int * 100 nano seconds
        break;
    case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
        break;
    case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
        break;
    case U8X8_MSG_DELAY_I2C: // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
        break;                    // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    case U8X8_MSG_GPIO_I2C_CLOCK: // arg_int=0: Output low at I2C clock pin
        break;                    // arg_int=1: Input dir with pullup high for I2C clock pin
    case U8X8_MSG_GPIO_I2C_DATA:  // arg_int=0: Output low at I2C data pin
        break;                    // arg_int=1: Input dir with pullup high for I2C data pin
    case U8X8_MSG_GPIO_MENU_SELECT:
        u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_NEXT:
        u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_PREV:
        u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_HOME:
        u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
        break;
    default:
        u8x8_SetGPIOResult(u8x8, 1); // default return value
        break;
    }
    return 1;
}

void u8g2Init(u8g2_t *u8g2)
{
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay); //
	u8g2_InitDisplay(u8g2);                                                                       //
	u8g2_SetPowerSave(u8g2, 0);                                                                   //
	u8g2_ClearBuffer(u8g2);
}




