
#include "app_svr.h"

#define TAG "app_svr"

extern  uint16_t conn_handle;
extern char *device_name;

uint16_t service1_char1_handle = 1;
uint16_t service1_char2_handle = 2;
uint16_t service2_char1_handle = 3;
uint16_t service2_char2_handle = 4;
uint16_t service2_char3_handle = 5;
uint16_t service2_char4_handle = 6;
uint16_t service2_char5_handle = 7;

static int gatt_svr_cb1(uint16_t conn_handle, uint16_t attr_handle,
                                struct ble_gatt_access_ctxt *ctxt, void *arg);

static int gatt_svr_cb2(uint16_t conn_handle, uint16_t attr_handle,
                                struct ble_gatt_access_ctxt *ctxt, void *arg);

/*
 * @description	: 接收网关发送来的信息
 * @param - char *data	: 从网关接收到的数据的指针
 * @return 		: 从网关接收到的数据
 */
void ble_receive_data(const char *data) {
    if (data != NULL) {
        ble_send_notify(data);
    } else {
        ESP_LOGI(TAG, "data is NULL");
    }
}

/*
 * @description	: 向客户端发送通知
 * @param - void *buf	: 要发送的通知数据
 * @return 		: 无
 */
void ble_send_notify(const void *buf){
    struct os_mbuf *txom;
    txom = ble_hs_mbuf_from_flat(buf, strlen(buf));
    int rc= ble_gatts_notify_custom(conn_handle,service1_char1_handle,txom);
    if (rc == 0) {
        ESP_LOGI(TAG, "Notification send successfully");
    } else {
        ESP_LOGI(TAG, "Notification send failed rc = %d", rc);
    }
}

static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    {
        /* ******************Service1***************************
        ********该服务主要用来读取特定消息和接收蓝牙通知************
        */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(GATT_SEVER_1_UUID),
        .characteristics = (struct ble_gatt_chr_def[])
        { {
                /* Characteristic1*/
                .uuid = BLE_UUID16_DECLARE(GATT_SEVER_1_CHARACTERISTIC_1_UUID),
                .access_cb = gatt_svr_cb1,
                .val_handle = &service1_char1_handle,
                .flags =BLE_GATT_CHR_F_NOTIFY,
            }, 
            {
                /* Characteristic2*/
                .uuid = BLE_UUID16_DECLARE(GATT_SEVER_1_CHARACTERISTIC_2_UUID),
                .access_cb = gatt_svr_cb1,
                .val_handle = &service1_char2_handle,
                .flags = BLE_GATT_CHR_F_READ,
            }, {
                0, /* No more characteristics in this service */
            },
        }
    },
    {
        /* ******************Service2***************************
        ********该服务主要用来改变终端的mac地址和终端名称以及向终端发送消息***********
        */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(GATT_SEVER_2_UUID),
        .characteristics = (struct ble_gatt_chr_def[])
        { {
                /* 特征值1 ***** 主要用来向网关发送消息***********/
                .uuid = BLE_UUID16_DECLARE(GATT_SEVER_2_CHARACTERISTIC_1_UUID),
                .access_cb = gatt_svr_cb2,
                .flags = BLE_GATT_CHR_F_WRITE,
                .val_handle=&service2_char1_handle,
            },
            {
                /* 特征值2 ***** 更改设备名称***********/
                .uuid = BLE_UUID16_DECLARE(GATT_SEVER_2_CHARACTERISTIC_2_UUID),
                .access_cb = gatt_svr_cb2,
                .flags = BLE_GATT_CHR_F_WRITE,
                .val_handle=&service2_char2_handle,
            },
            {
                /* 特征值3 ***** 更改设备mac地址***********/
                .uuid = BLE_UUID16_DECLARE(GATT_SEVER_2_CHARACTERISTIC_3_UUID),
                .access_cb = gatt_svr_cb2,
                .flags = BLE_GATT_CHR_F_WRITE,
                .val_handle=&service2_char3_handle,
            },
            {
                /* 特征值4 ***** 更改设备mac地址***********/
                .uuid = BLE_UUID16_DECLARE(GATT_SEVER_2_CHARACTERISTIC_4_UUID),
                .access_cb = gatt_svr_cb2,
                .flags = BLE_GATT_CHR_F_WRITE,
                .val_handle=&service2_char4_handle,
            }, 
            {
                /* 特征值4 ***** 更改设备mac地址***********/
                .uuid = BLE_UUID16_DECLARE(GATT_SEVER_2_CHARACTERISTIC_5_UUID),
                .access_cb = gatt_svr_cb2,
                .flags = BLE_GATT_CHR_F_WRITE,
                .val_handle=&service2_char5_handle,
            },{
                0, /* No more characteristics in this service */
            },
        }
        
    },

    {
        0, /* No more services */
    },
};

static int
gatt_svr_cb1(uint16_t conn_handle, uint16_t attr_handle,
                               struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR){
        ESP_LOGI(TAG, "Sever1 ch1 Doing RADE");
        // os_mbuf_append(ctxt->om, (const void*)model_num, strlen(model_num));
    }
    return 0;
}

static int gatt_svr_cb2(uint16_t conn_handle, uint16_t attr_handle,
                       struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    uint16_t uuid;
    uuid = ble_uuid_u16(ctxt->chr->uuid);
    /* *******************特征值1 向网关发送数据*********************/
    if (uuid == GATT_SEVER_2_CHARACTERISTIC_1_UUID) {

    }
    /* *******************特征值2 更改设备名称***********************/
    if (uuid == GATT_SEVER_2_CHARACTERISTIC_2_UUID) {

    }
    /* *******************特征值3 更改设备macaddr***********************/
    if (uuid == GATT_SEVER_2_CHARACTERISTIC_3_UUID) {

    }
    /* *******************特征值4 功能性选项 重启等操作***********************/
    if (uuid == GATT_SEVER_2_CHARACTERISTIC_4_UUID) {

    }
    /* *******************特征值5 功能性选项 设置终端时隙***********************/
    if (uuid == GATT_SEVER_2_CHARACTERISTIC_5_UUID) {

        // turmass_sequence_parse(*(ctxt->om->om_data));

    }
    return 0;
}
void app_svr_init(void)
{
    ble_svc_gap_init();
    ble_svc_gatt_init();

    ble_gatts_count_cfg(gatt_svr_svcs);
    ble_gatts_add_svcs(gatt_svr_svcs);
}