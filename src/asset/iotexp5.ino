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

-----------------------------------------------------
Hardware Required:
- NodeMCU ESP8266
- LDR Sensor
- 10 kOhm Resistor
- Breadboard
- Jumper Wires
- USB Cable
- Wi-Fi Connection

Software Required:
- Arduino IDE
- Blynk IoT Mobile App / Web Dashboard
- ESP8266 Board Package
- Blynk Library

Circuit Connections:
LDR Circuit             NodeMCU Pin
-----------------------------------
Voltage Divider Output  A0
VCC                     3.3 V
GND                     GND

Blynk Datastream:
- V0: Light Intensity (ADC: 0 to 1024)

Procedure:
1. Connect the LDR and 10 kOhm resistor in a voltage divider circuit and connect the output to NodeMCU pin A0.
2. Install the ESP8266 board package and Blynk library in the Arduino IDE.
3. Create a template (iotExp5LDRwNodeMCU) and a Virtual Pin V0 datastream for Light Intensity in the Blynk Cloud.
4. Obtain the Blynk Template ID, Template Name, and Authentication Token.
5. Enter the Wi-Fi SSID, password, and Blynk Auth Token in the program.
6. Compile and upload the program to the NodeMCU.
7. Open the Serial Monitor (9600 baud) and the Blynk App/Dashboard.
8. Observe the real-time light intensity values on the Serial Monitor and Blynk dashboard.
*/
