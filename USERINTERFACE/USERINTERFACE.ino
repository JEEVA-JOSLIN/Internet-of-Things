#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(172, 16, 2, 111);
IPAddress gateway(172, 16, 16, 1);
IPAddress subnet(255, 255, 224, 0);
EthernetServer server(80);

String read = "";

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
  // Set pins for the two LEDs
  pinMode(13, OUTPUT); // LED 1
  pinMode(9, OUTPUT);  // LED 2
}

void loop() {
  EthernetClient client = server.available();
  if (client) {

    Serial.println("CONNECTED");
    boolean currentLine = true;

    while (client.connected()) {
      if (client.available()) {
        char c = (char)client.read();
        read = read + c;

        if (c == '\n' && currentLine) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<!DOCTYPE>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Control LEDs</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>Welcome to Arduino LED Control</h1>");
          
          client.println("<table style=\"width:100%; border-collapse:collapse;\">");
          client.println("<tr>");
          client.println("<th style=\"border: 1px solid black; padding: 10px;\">LED 1</th>");
          client.println("<th style=\"border: 1px solid black; padding: 10px;\">LED 2</th>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td style=\"border: 1px solid black; text-align:center;\">");
          client.println("<a href=\"/?led1on\" style=\"color:green;\">Turn On</a><br />");
          client.println("<a href=\"/?led1off\" style=\"color:red;\">Turn Off</a>");
          client.println("</td>");
          client.println("<td style=\"border: 1px solid black; text-align:center;\">");
          client.println("<a href=\"/?led2on\" style=\"color:green;\">Turn On</a><br />");
          client.println("<a href=\"/?led2off\" style=\"color:red;\">Turn Off</a>");
          client.println("</td>");
          client.println("</tr>");
          client.println("</table>");

          if (read.indexOf(" /?led1on") > 0) {
            Serial.println("LED 1 switched on");
            digitalWrite(13, HIGH); // Turn on LED 1
          }

          if (read.indexOf(" /?led1off") > 0) {
            Serial.println("LED 1 switched off");
            digitalWrite(13, LOW); // Turn off LED 1
          }

          if (read.indexOf(" /?led2on") > 0) {
            Serial.println("LED 2 switched on");
            digitalWrite(9, HIGH); // Turn on LED 2
          }

          if (read.indexOf(" /?led2off") > 0) {
            Serial.println("LED 2 switched off");
            digitalWrite(9, LOW); // Turn off LED 2
          }

          read = "";
          break;
        }

        if (c == '\n') {
          currentLine = true;
        } else if (c != '\r') {
          currentLine = false;
        }
      }
    }
    delay(1000);
    client.stop();
  }
}



