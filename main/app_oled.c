#include "app_oled.h"

int x ,x_trg;
int y  = 10,y_trg = 10;
int state;

SETTING_LIST list[] ={
    {"Lylz"},
    {"zey"},
    {"lyl"},
};

void draw_progress_bar(u8g2_t *u8g2)
{
    u8g2_FirstPage(u8g2); // 进度条完
    do
    {
        for (uint8_t i = 0; i <= 99; i = i + 1)
        {
            u8g2_ClearBuffer(u8g2);

            char buff[20];
            u8g2_SetFont(u8g2, u8g2_font_ncenB08_tf); // 字体
            sprintf(buff, "%d%%", (int)(i / 100.0 * 100));
            u8g2_DrawStr(u8g2, 105, 49, buff); // 当前进度显示
            u8g2_DrawStr(u8g2, 0, 10, "Lylz");
            u8g2_DrawBox(u8g2, 2, 40, i, 10);     // 填充框实心矩形框
            u8g2_DrawFrame(u8g2, 0, 38, 103, 14); // 空心矩形框

            vTaskDelay(10 / portTICK_PERIOD_MS);
            u8g2_SendBuffer(u8g2);
        }
    } while (u8g2_NextPage(u8g2));
}

int draw_scroll_chr(int *a,int *a_trg)
{
    if(*a<*a_trg)
    {
        *a +=2;
        
    }else if(*a > *a_trg)
    {
        *a -=2;
    }else
    {
        return 0;
    }
    return 1;
}

void app_oled_init(u8g2_t u8g2)
{
    // x_trg = 64;
    // y_trg = -64;

    int list_len = sizeof(list)/sizeof(SETTING_LIST);

    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tf); // 字体

    for(int i = 0;i < list_len;i++)
    {
        u8g2_DrawStr(&u8g2, x, y+i*10, list[i].str);
    }
    if(draw_scroll_chr(&y,&y_trg) == 0)
    {
        switch(state)
        {
            case 0:
            {
                y_trg = 0;
                state = 1;
                break;
            }
            case 1:
            {
                y_trg = 50;
                state = 0;
                break;
            }
        }
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
    u8g2_SendBuffer(&u8g2);
}


void draw(u8g2_t *u8g2)
{
    // int y = 1;
    // for(int x = 0;x < 256;x+=y)
    // {
    // u8g2_ClearBuffer(u8g2);
    // u8g2_SetFontMode(u8g2, 1); /*字体模式选择*/
    // u8g2_SetFontDirection(u8g2, 0); /*字体方向选择*/
    // u8g2_SetFont(u8g2, u8g2_font_7x14_tr); /*字库选择*/
    // u8g2_DrawStr(u8g2, 0, 10, "Lylz");
    //     u8g2_DrawStr(u8g2, x-128, 40, "LYL LOVE ZEY");
    // u8g2_SetFontDirection(u8g2, 1);
    // u8g2_SetFont(u8g2, u8g2_font_inb30_mn);
    // u8g2_DrawStr(u8g2, 21,8,"8");

    // u8g2_SetFontDirection(u8g2, 0);
    // u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    // u8g2_DrawStr(u8g2, 51,30,"g");
    // u8g2_DrawStr(u8g2, 67,30,"\xb2");

    // u8g2_DrawHLine(u8g2, 2, 35, 47);
    // u8g2_DrawHLine(u8g2, 3, 36, 47);
    // u8g2_DrawVLine(u8g2, 45, 32, 12);
    // u8g2_DrawVLine(u8g2, 46, 33, 12);

    // u8g2_SetFont(u8g2, u8g2_font_5x7_tr);
    // u8g2_DrawStr(u8g2, 1,54,"github.com/olikraus/u8g2");
    // u8g2_SendBuffer(u8g2);
    // }
}
