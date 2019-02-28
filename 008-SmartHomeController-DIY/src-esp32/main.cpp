#include <WiFi.h>
#include <PubSubClient.h>
#include "SSD1306.h"
#include "DHT.h"
#include "IRremoteWrapper.h"
#include "ILedWrapper.h"
#include "IPIRWrapper.h"

#define PORT_LED 16

const char* SSID = "";
const char* PASS = "";
const char* SERVER = "";

const int PORT = 1883;

static float humid = 0.0;
static float tempC = 0.0;
static bool bPowerTV = true;
static bool bAnybody = true;
static int  cntNodody = 0;

SSD1306 display(0x3c, 5, 4);

DHT dht(19, DHT11);

WiFiClient espClient;
PubSubClient client(espClient);

IRsendWrapper* ir = new IRsendWrapper();
LedWrapper* led = new LedWrapper();
PIRWrapper* pir = new PIRWrapper();

typedef enum {
    ST_BOOTING,
    ST_AP_CONNECTED,
    ST_MQTT_CONNECTED,
    ST_NOBODY,
};


void initializeLCD() {
    display.init();
    display.setFont(ArialMT_Plain_24);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void updateLCD(String str) {
    display.clear();
    display.drawString(0, 0, str);
    display.display();
}

void sendMsgMQTT()
{
    char bufferMSG[32];

    memset(bufferMSG, 0x00, sizeof(bufferMSG)/sizeof(bufferMSG[0]));
    sprintf(bufferMSG, "%2.1f %2.1f %d %d", humid, tempC, bPowerTV, bAnybody);

    client.publish("liviingroom/status", bufferMSG);

    Serial.print("sendMsgMQTT : ");
    Serial.println(bufferMSG);
}

void callback(char* topic, byte* payload, unsigned int length) {
    char str[32];

    memset(str, 0x00, sizeof(str));

    Serial.println(sizeof(str));
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    for (int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
        str[i] = (char)payload[i];
    }
    Serial.println();

    updateLCD(String(str));
}

void setup()
{
    pinMode(PORT_LED, OUTPUT);
    Serial.begin(115200);

    initializeLCD();

    WiFi.begin(SSID, PASS);
 
    while (WiFi.status() != WL_CONNECTED)
    {
        led->turnOnRed();
        delay(1000);
        led->turnOff();
        delay(1000);
        led->turnOnRed();
        delay(1000);
        led->turnOff();

        Serial.println("Connecting to AP...");
    }

    Serial.println("Connected to AP!!");
    updateLCD("WIFI ON!");

    client.setServer(SERVER, PORT);
    client.setCallback(callback);

    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP32Client")) {
            Serial.println("Connected!!");
            updateLCD("MQTT ON!");
        } else {
            Serial.print("Failure on connect (");
            Serial.print(client.state());
            Serial.println(")");
            updateLCD("MQTT FAIL!");
            delay(2000);
        }
    }
}

void loop()
{
    char bufferLCD[16];
    humid = dht.readHumidity();
    tempC = dht.readTemperature(); // Celsius
  
    memset(bufferLCD, 0x00, sizeof(bufferLCD));

    // check fail
    if (isnan(humid) || isnan(tempC))
    {
        Serial.println("fail to read DHT.");
        updateLCD("Fail to read!");
        humid = tempC = 0.0;

        //delay(1000);
        //return;
    }

    sprintf(bufferLCD, "H:%2.1f T:%2.1f", humid, tempC);
    updateLCD(bufferLCD);

    sendMsgMQTT();

    //blink
    digitalWrite(PORT_LED, LOW);
    led->turnOnGreen();
    delay(1000);

    //PIR
    if(pir->isAnybody())
    {
        bAnybody = true;
        updateLCD("Somebody!");
        cntNodody = 0;
    }
    else
    {
        updateLCD("Nobody!");
        if(cntNodody++ > 10) {
//            ir->sendTurnOffTv();
            bPowerTV = false;
            bAnybody = false;

            while(true)
            {
                static int nCnt = 0;

                led->turnOnBlue();
                delay(1000);
                led->turnOff();
                delay(1000);
                sendMsgMQTT();

                if(pir->isAnybody())
                {
                    bPowerTV = true;
                    bAnybody = true;                    
                    cntNodody = 0;
                    break;
                }

                if(nCnt++>10)
                {
                    ESP.restart();
                }
            }             
        }
    }

    client.loop();
}
