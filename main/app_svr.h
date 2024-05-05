#ifndef _APP_SVR_H_
#define _APP_SVR_H_

#include "app_divers.h"

#define GATT_SEVER_1_UUID                       0x2000
#define GATT_SEVER_1_CHARACTERISTIC_1_UUID      0x200A
#define GATT_SEVER_1_CHARACTERISTIC_2_UUID      0x200B

#define GATT_SEVER_2_UUID                       0x2100
#define GATT_SEVER_2_CHARACTERISTIC_1_UUID      0x210A
#define GATT_SEVER_2_CHARACTERISTIC_2_UUID      0x210B
#define GATT_SEVER_2_CHARACTERISTIC_3_UUID      0x210C
#define GATT_SEVER_2_CHARACTERISTIC_4_UUID      0x210D
#define GATT_SEVER_2_CHARACTERISTIC_5_UUID      0x210E

void app_svr_init(void);
void ble_receive_data(const char*data);
void ble_send_notify(const void *buf);

#endif






