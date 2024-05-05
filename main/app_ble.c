#include "app_ble.h"

static const char *tag = "NimBLE_BLE";

uint16_t conn_handle;

char device_name[32] = "Terminal";
int length = sizeof(device_name);

char end_name[512]; 

static int blehr_gap_event(struct ble_gap_event *event, void *arg);

static uint8_t blehr_addr_type = 0x00;

uint32_t mac_addr;

void
print_addr(const void *addr)
{
    const uint8_t *u8p;

    u8p = addr;
    MODLOG_DFLT(INFO, "%02x:%02x:%02x:%02x:%02x:%02x",
                u8p[5], u8p[4], u8p[3], u8p[2], u8p[1], u8p[0]);
}

static void blehr_advertise(void)
{
    struct ble_gap_adv_params adv_params;
    struct ble_hs_adv_fields fields;

    memset(&fields, 0, sizeof(fields));

    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;
    fields.tx_pwr_lvl_is_present = 1;
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;
    fields.name = (uint8_t *)end_name;
    fields.name_len = strlen(end_name);
    fields.name_is_complete = 1;

    ble_gap_adv_set_fields(&fields);

    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    ble_gap_adv_start(blehr_addr_type, NULL, BLE_HS_FOREVER,
                           &adv_params, blehr_gap_event, NULL);
}

static int blehr_gap_event(struct ble_gap_event *event, void *arg)
{
    switch (event->type) {
        case BLE_GAP_EVENT_CONNECT:
            MODLOG_DFLT(INFO, "connection %s; status=%d\n",
                        event->connect.status == 0 ? "established" : "failed",
                        event->connect.status);
            if (event->connect.status != 0) {
                blehr_advertise();
            }
            conn_handle = event->connect.conn_handle;
            break;

        case BLE_GAP_EVENT_DISCONNECT:
            MODLOG_DFLT(INFO, "disconnect; reason=%d\n", event->disconnect.reason);
            blehr_advertise();
            break;

        case BLE_GAP_EVENT_ADV_COMPLETE:
            MODLOG_DFLT(INFO, "adv complete\n");
            blehr_advertise();
            break;

        case BLE_GAP_EVENT_SUBSCRIBE:
            ESP_LOGI("BLE_GAP_SUBSCRIBE_EVENT", "conn_handle from subscribe=%d", conn_handle);
            break;

        case BLE_GAP_EVENT_MTU:
            MODLOG_DFLT(INFO, "mtu update event; conn_handle=%d mtu=%d\n",
                        event->mtu.conn_handle,
                        event->mtu.value);
            break;

    }

    return 0;
}

static void blehr_on_sync(void)
{
    // rc = ble_hs_id_infer_auto(0, &blehr_addr_type);

    uint8_t addr_val[6] = {0};
    ble_hs_id_copy_addr(blehr_addr_type, addr_val, NULL);

    MODLOG_DFLT(INFO, "Device Address: ");
    print_addr(addr_val);
    MODLOG_DFLT(INFO, "\n");

    memcpy(&mac_addr, addr_val, 4);
    MODLOG_DFLT(INFO, "mac_addr: %08X",(unsigned int)mac_addr);
    MODLOG_DFLT(INFO, "\n");

    char mac_str[9]; 

    sprintf(mac_str, "%08X", (unsigned int)mac_addr);

    strcpy(end_name, device_name);
    strcat(end_name, mac_str);

    // app_localdata_write("Terminal_mac",mac_addr);

    // xSemaphoreGive(change_macaddr_finish_semaphore);

    ble_svc_gap_device_name_set(end_name);
    
    blehr_advertise();
    
}

static void blehr_on_reset(int reason)
{
    MODLOG_DFLT(ERROR, "Resetting state; reason=%d\n", reason);
}

void blehr_host_task(void *param)
{
    ESP_LOGI(tag, "BLE Host Task Started");
    nimble_port_run();
    nimble_port_freertos_deinit();
    vTaskDelay(pdMS_TO_TICKS(500));
}

void app_ble_init(void)
{
    nimble_port_init();

    ble_hs_cfg.sync_cb = blehr_on_sync;
    ble_hs_cfg.reset_cb = blehr_on_reset;

    app_svr_init();

    nimble_port_freertos_init(blehr_host_task);
}