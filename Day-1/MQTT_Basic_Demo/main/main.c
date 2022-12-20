//------------------------------------------------------------------------------
#include "ey_iot.h"
#include "ey_iot_config.h"

//------------------------------------------------------------------------------
#define PUB_TOPIC   "/eyantra/chat/my"
#define DELAY_SEC	60

//------------------------------------------------------------------------------
void init_callback(void);
void my_wifi_start(void);
void my_wifi_disconnect(void);
void my_mqtt_rx(void);
void my_mqtt_disconnect(void);

//------------------------------------------------------------------------------
void app_main(void){

	init_callback();
	ey_init_nvs();
    ey_init_wifi_sta(EY_CONFIG_WIFI_SSID, EY_CONFIG_WIFI_PASS);
    ey_mqtt_start();

	int counter = 1;

	while (counter <= 11)
	{
		ey_mqtt_publish(PUB_TOPIC, "You are subscibed", 0);
		printf("Published %d times ...", counter);
		vTaskDelay(1000 / portTICK_PERIOD_MS);

		counter = counter + 1;
	}
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
