#include "app_wifi.h"

uint8_t conunt =0;

SemaphoreHandle_t wifi_connect_sendfinish_semaphore = NULL;

void STA_Callback(void* event_handler_arg,esp_event_base_t event_base,int32_t event_id,void* event_data)
{
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START){
        esp_wifi_connect();
    }
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED){
        conunt++;
        if(conunt<=5){
            esp_wifi_connect();
        }else{
            printf("连接失败\n");
        }
    }
    if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP){
        printf("连接成功\n");
        ip_event_got_ip_t*info =(ip_event_got_ip_t*)event_data;
        printf("IP:"IPSTR"\n",IP2STR(&info->ip_info.ip));
        xSemaphoreGive(wifi_connect_sendfinish_semaphore);
    }
}

void app_wifi_init(void)
{
    nvs_flash_init();//esp32 nvs初始化 配置AP、STA等信息时会储存在nvs中，必须先初始化
    esp_event_loop_create_default();//配置默认事件循环队列
    esp_event_handler_instance_register(WIFI_EVENT,WIFI_EVENT_STA_START,STA_Callback,NULL,NULL);         //检测wifi配置是否成功或wifi是否开启
    esp_event_handler_instance_register(WIFI_EVENT,WIFI_EVENT_STA_DISCONNECTED,STA_Callback,NULL,NULL);  //检测wifi是否连接失败
    esp_event_handler_instance_register(IP_EVENT,IP_EVENT_STA_GOT_IP,STA_Callback,NULL,NULL);            //检测wifi是否连接成功
    //初始化网卡配置
    esp_netif_init();

    //以默认方式配置一个STA类型的网卡
    esp_netif_create_default_wifi_sta();

    //初始化wifi底层
    wifi_init_config_t crg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&crg);

    //设置wifi模式
    esp_wifi_set_mode(WIFI_MODE_STA);

    //设置AP参数
    wifi_config_t crg2 = {
        .sta = {
             .ssid = "123",                  //wifi名称
             .password = "lyl20020712"                 //wifi密码
        }
    };
    esp_wifi_set_config(WIFI_IF_STA,&crg2);

    //启动
    esp_wifi_start();

    wifi_connect_sendfinish_semaphore = xSemaphoreCreateBinary();
}