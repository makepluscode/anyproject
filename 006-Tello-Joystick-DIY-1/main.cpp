#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

// Make sure to add your own information
const char *SSID = "****";
const char *PASS = "****";

void setup()
{ 
  Serial.begin(74880);

  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.print("Connected! ");
  Serial.println(WiFi.localIP());

  udp.begin(1004);
}

void loop()
{
  char buffer[255];
  int size = udp.parsePacket();

  if (size)
  {
    int len;
    memset(buffer, 0x0, sizeof(buffer));

    len = udp.read(buffer, sizeof(buffer));
    Serial.printf("Received Packet : %s\n", buffer);

    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.write("Welcomm to Wemos");
    udp.endPacket();
  }
}
