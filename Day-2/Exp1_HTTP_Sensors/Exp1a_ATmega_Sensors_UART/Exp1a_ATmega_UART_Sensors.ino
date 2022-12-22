/*
 * Exp1a_ATmega_UART_Sensors.ino
 * 
 * Aim: Enable UART0 communication from ATmega2560 to ESP32.
 * 
 * Target:        eYFi-Mega dev board (https://www.e-yantra.org/products)
 * Last modified: 20-12-2022
 * Author:        e-Yantra Team
 * 
 * Connections:
 * ATmega2560 TX0  ->   ESP32 RX1
 * ATmega2560 RX0  ->   ESP32 TX1
 */

// include Arduino DHT library
#include <DHT.h>

// macro definitions
#define SensorPin  A0

#define DHT_PIN     25      // pin where DHT11 Data is connected
#define DHT_TYPE    DHT11   // type of DHT sensor

// configure the sensor
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
		Serial.begin(9600);

		// set LDR Pin as Input
		pinMode(SensorPin, INPUT);
		
		// initialize the sensor here
		dht.begin();
}

void loop() {

	delay(1000); // Delays 1 seconds, as the DHT11 sampling rate is 1Hz

	// reading light, temperature or humidity takes about 250 ms
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	// Getting the values from the Sensor 
	// int ldr = analogRead(SensorPin);

	// Printing the results on the serial monitor
	Serial.print(t);
	Serial.print("|");
	Serial.println(h);
	// Serial.print("|");
	// Serial.print(ldr);
}