//------------------------------------------------------------------------------
#include "ey_iot.c"
#include "ey_iot_config.h"

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

//------------------------------------------------------------------------------
#define PUB_TOPIC   "eyantra/notify/me"
#define DELAY_SEC	60

// macro definitions
#define ECHO_TEST_TXD  (GPIO_NUM_32)            // Connected to AVR Rx-0
#define ECHO_TEST_RXD  (GPIO_NUM_33)            // Connected to AVR Tx-0
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

#define BUF_SIZE (150)

//------------------------------------------------------------------------------
// Global variables, sensor data and actuator data
char sensor_data[18], Light[3], Fan[12];

//------------------------------------------------------------------------------
void init_callback(void);
void my_wifi_start(void);
void my_wifi_disconnect(void);
void my_mqtt_disconnect(void);

void rcv_sensor_data(void *arg)
{
    // configure UART driver
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &uart_config));
    
    // set the UART pins
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));
    
    // install the UART driver and set UART to default config
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0));

    // create temporary buffer for incoming data
    uint8_t* sensor_data = (uint8_t *) malloc(BUF_SIZE);
    float sensor_light, sensor_temp, sensor_humid;

    while (1)
    {
        // read data from the UART
        int len = uart_read_bytes(UART_NUM_1, sensor_data, BUF_SIZE, 20 / portTICK_PERIOD_MS);

        if (len > 0)
        {
            sensor_data[len] = '\0';
            char *token = strtok((char *) sensor_data, "|");

            while( token != NULL )
            {
                sensor_light = atof(token);
                token = strtok(NULL, "|");

                sensor_temp = atof(token);
                token = strtok(NULL, "|");

                sensor_humid = atof(token);
                token = strtok(NULL, "|");

                printf("%0.2f | ", sensor_light);
                printf("%0.2f | ", sensor_temp);
                printf("%0.2f \n", sensor_humid);

                x_ey_push_sensor_data(GOOGLE_SHEET, 3, sensor_temp, sensor_humid, sensor_light);
                break;
            }
            if (alert_msg[0] != '\0')
            {
                printf("alert rcvd: %s\n", alert_msg);
                char *token1 = strtok((char *) alert_msg, "|");

                while(token1 != NULL)
                {
                    char fan_msg[50];
                    strcpy(fan_msg, token1);
                    
                    token1 = strtok(NULL, "|");

                    char light_msg[50];
                    strcpy(light_msg, token1);

                    printf("%s | %s\n", fan_msg, light_msg);

                    ey_mqtt_publish(PUB_TOPIC, light_msg, 0);

                    break;
                }
                alert_msg[0] = '\0';
            }
        }
    }
}

//------------------------------------------------------------------------------
void app_main(void){
	init_callback();
	ey_init_nvs();
    ey_init_wifi_sta(EY_CONFIG_WIFI_SSID, EY_CONFIG_WIFI_PASS);
    ey_mqtt_start();

    xTaskCreate(rcv_sensor_data, "uart_rcv_task_and_publish", 8120, NULL, 10, NULL);
}


//------------------------------------------------------------------------------
void init_callback(void){
	
	ey_register_callback(EY_WIFI_EVENT_STA_START, my_wifi_start);
	ey_register_callback(EY_WIFI_EVENT_STA_DISCONNECTED, my_wifi_disconnect);
}


void my_wifi_start() { 
	printf("USER: Wi-Fi Start\n");
}


void my_wifi_disconnect() { 
	printf("USER: Wi-Fi Disconnect\n");
	ey_wifi_auto_reconnect();
}


void my_mqtt_disconnect(){
	printf("USER: MQTT Disconnect\n");
	ey_wifi_auto_reconnect();
}
