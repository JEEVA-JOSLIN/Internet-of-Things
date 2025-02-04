#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
char server[] = "172.16.6.40"; 
IPAddress ip(172, 16, 0, 0); 
EthernetClient client;
int waterSensorPin = A0; 
int waterLevel;          
void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip); 
  }
  delay(1000);
}
void loop() {
  waterLevel = analogRead(waterSensorPin); 
  Sending_To_phpmyadmindatabase(); 
  delay(300); 
}
void Sending_To_phpmyadmindatabase() {
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET /testcode/waterlevel.php?water_level="); 
    client.print(waterLevel); 
    client.print(" ");
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 172.16.10.148"); 
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

