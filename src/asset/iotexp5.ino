// Experiment No  5: To Upload Light Intensity Sensor Data using LDR, NodeMCU and Wireless Communication Protocol
// iotExp5LDRwNodeMCU:

#define BLYNK_TEMPLATE_ID "TMPL3FmQO2LRg"
#define BLYNK_TEMPLATE_NAME "iotExp5LDRwNodeMCU"
#define BLYNK_AUTH_TOKEN "UEUh9YDi0cX-ApMMXSEoOpeN5l9BH59M"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "RCOE-202";
char pass[] = "rcoe1234";

int LDR = A0;

BlynkTimer timer;

void sendLightData()
{
  int lightValue = analogRead(LDR);

  Serial.print("Light Intensity: ");
  Serial.println(lightValue);

  // Send LDR value to Blynk Virtual Pin V0
  Blynk.virtualWrite(V0, lightValue);
}

void setup()
{
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Send data every 2 seconds
  timer.setInterval(2000L, sendLightData);
}

void loop()
{
  Blynk.run();
  timer.run();
}

/*
Expected Output:
Light Intensity: 145
Light Intensity: 382
Light Intensity: 765
(Values are continuously sent to Blynk Virtual Pin V0 every 2 seconds)
*/
