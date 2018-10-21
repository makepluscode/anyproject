#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

const char *SSID = "TELLO-C698AD";
const char *PASS = "";
const char *ADDR = "192.168.10.1";
const int  PORT  = 8889;

void setup()
{
  Serial.begin(74880);

  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected!");

  Serial.println("[NETWORK]");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  Serial.println("");

  udp.begin(PORT);
}

void SendCmd(char *cmd)
{
  char buf[255];
  Serial.print("Wemos sent : ");
  Serial.println(cmd);
  
  udp.beginPacket(ADDR, PORT);
  udp.printf(cmd);
  udp.endPacket();

  memset(buf, 0x0, sizeof(buf));

  while(udp.parsePacket() <= 0)
  {
    delay(5);
  }

  if(udp.read(buf, sizeof(buf)) > 0)
  {
    Serial.print("Tell said : ");
    Serial.println(buf);
  }
}

void loop()
{
  SendCmd((char *)"command");
  SendCmd((char *)"time?");
  SendCmd((char *)"battery?");  
  SendCmd((char *)"speed?");
  SendCmd((char *)"speed 50");
  SendCmd((char *)"speed?");  
  
  SendCmd((char *)"takeoff");
  delay(5000);
  SendCmd((char *)"land");
  delay(5000);

  Serial.println("All done!");

  while(true)
  {
    //do nothing
    delay(1000);
  }
}
