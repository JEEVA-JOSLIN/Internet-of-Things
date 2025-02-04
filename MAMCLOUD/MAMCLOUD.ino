#include <Ethernet.h>
#include "ThingSpeak.h"
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
String waterData;
unsigned long channelNumber =2673837;
const char* channelKey = "96W5DKX0VNPBXP2I";
int id = 1;
EthernetClient client;
void setup() {
  Serial.begin(9600);
  
  if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  }else{
    Serial.println("configured Ethernet using DHCP");
    IPAddress myIPAddress = Ethernet.localIP(); 
    Serial.println(myIPAddress);
  }
  delay(500);
  ThingSpeak.begin(client);
}

void loop(){
  waterData = String((float)analogRead(A0), DEC);
  useThingSpeakApi(waterData);
  delay(5000);
}

void useThingSpeakApi(String data){
  int x = ThingSpeak.writeField(channelNumber, 1, data, channelKey);
  if(x == 200){
    Serial.println("Channel update successful with field1="+data);
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}