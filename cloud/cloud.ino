#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;

// On Arduino: 0 - 1023 maps to 0 - 5 volts
#define VOLTAGE_MAX 5.0
#define VOLTAGE_MAXCOUNTS 1023.0


int waterSensorPin = A0; 
unsigned long myChannelNumber = 2673837;
const char *myWriteAPIKey = "96W5DKX0VNPBXP2I";

void setup() {
    Serial.begin(9600);
    
    // Start Ethernet and ThingSpeak
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        while (true); // Stop if Ethernet connection fails
    }
    
    ThingSpeak.begin(client);
}

void loop() {
    // Simulating sensor values with random numbers between 0 and 1023
    int sensorValue = alalogRead(waterSensorPin);
    
    // Convert sensor value to voltage
    float voltage = sensorValue * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
    
    // Print sensor value and voltage to Serial Monitor
    Serial.println(sensorValue);
    Serial.println(voltage);
    
    // You can add your ThingSpeak update logic here to send data to the cloud
}
