#include "app_uart.h"

static QueueHandle_t uart1_receive_queue;

void uart_receive_task(void *arg)
{
    uart_event_t event;
    uint8_t data[2048];
    size_t len;
    while (1)
    {
        if (xQueueReceive(uart1_receive_queue, (void *)&event, (TickType_t)portMAX_DELAY))
        {
            switch (event.type)
            {
            case UART_DATA:
                if (event.size <= sizeof(data))
                {
                    len = uart_read_bytes(UART_NUM_1, data, event.size, 0);
                    data[len] = 0;
                    printf("receive data: %s \n", data);
                }
                break;

            case UART_FIFO_OVF:
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart1_receive_queue);
                break;
            case UART_BUFFER_FULL:
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart1_receive_queue);
                break;
            case UART_BREAK:
                break;
            case UART_PARITY_ERR:
                break;
            case UART_FRAME_ERR:
                break;
            case UART_PATTERN_DET:
                break;
            default:
                printf("uart event type: %d", event.type);
                break;
            }
        }
    }
}

void uart_send_task(void *arg)
{
    // uart_write_bytes(UART_NUM_1, (const char *)data, len);
}


void app_uart_init(void)
{
    uart_config_t uart_config;

    uart_config.baud_rate = 115200;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_config.source_clk = SOC_MOD_CLK_APB;

    uart_driver_install(UART_NUM_1, 1024 * 5, 1024 * 5, 30, &uart1_receive_queue, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, 6, 7, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    xTaskCreate(uart_receive_task, "uart_receive_task", 1024 * 4, NULL, 10, NULL);
    // xTaskCreate(uart_send_task, "uart_send_task", 2048, NULL, 10, NULL);

}