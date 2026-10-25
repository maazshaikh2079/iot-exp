// Experiment No  6: To design and implement a Smart Traffic Signal using NodeMCU ESP8266 and Blynk IoT, where a single button in the Blynk mobile application starts and stops the automatic traffic light sequence using Red, Yellow, and Green LEDs.
// iotexp61tempLEDONOFF:

#define BLYNK_TEMPLATE_ID "TMPL3o0UCw5RV"
#define BLYNK_TEMPLATE_NAME "iotexp61tempLEDONOFF"
#define BLYNK_AUTH_TOKEN "i7YqKwDJu2AmtsaeXcrGi-rdQfZeLZv3"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "RCOE-202";
char pass[] = "rcoe1234";

// Traffic light pins
#define RED_LED D1
#define YELLOW_LED D2
#define GREEN_LED D3

// 1 second for each light
unsigned long previousMillis = 0;
const unsigned long interval = 1000;

bool trafficStarted = false;
int state = 0;

// Blynk button V0
BLYNK_WRITE(V0)
{
  int button = param.asInt();

  if (button == 1)
  {
    trafficStarted = true;

    // Start from RED
    state = 0;
    previousMillis = millis();

    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("RED");
  }
  else
  {
    trafficStarted = false;

    // Turn everything OFF
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("TRAFFIC STOPPED");
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();

  if (trafficStarted)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;

      // Turn all LEDs OFF
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);

      // RED -> YELLOW -> GREEN
      if (state == 0)
      {
        digitalWrite(YELLOW_LED, HIGH);
        state = 1;

        Serial.println("YELLOW");
      }
      else if (state == 1)
      {
        digitalWrite(GREEN_LED, HIGH);
        state = 2;

        Serial.println("GREEN");
      }
      else
      {
        digitalWrite(RED_LED, HIGH);
        state = 0;

        Serial.println("RED");
      }
    }
  }
}

/*
Expected Output:
When Blynk Button (V0) is pressed ON (1):
RED
YELLOW
GREEN
RED
YELLOW
GREEN

When Blynk Button (V0) is pressed OFF (0):
TRAFFIC STOPPED

-----------------------------------------------------
Hardware Required:
- NodeMCU ESP8266
- Red LED
- Yellow LED
- Green LED
- 3 x 220 Ohm Resistors
- Breadboard
- Jumper Wires
- USB Cable
- Wi-Fi Connection
- Smartphone

Software Required:
- Arduino IDE
- ESP8266 Board Package
- Blynk Library
- Blynk IoT Account
- Blynk Mobile Application

Circuit Connections:
Traffic Light   NodeMCU Pin   Connection
---------------------------------------------------------
Red LED         D1 (GPIO5)    D1 -> 220 Ohm -> Red LED -> GND
Yellow LED      D2 (GPIO4)    D2 -> 220 Ohm -> Yellow LED -> GND
Green LED       D3 (GPIO0)    D3 -> 220 Ohm -> Green LED -> GND

Blynk Datastream:
- V0: Traffic Start/Stop Button (Integer: 0 to 1)

Procedure:
1. Connect the Red LED to D1 through a 220 Ohm resistor.
2. Connect the Yellow LED to D2 through a 220 Ohm resistor.
3. Connect the Green LED to D3 through a 220 Ohm resistor.
4. Connect the short leg (cathode) of all LEDs to GND.
5. Connect the NodeMCU ESP8266 to the computer using a USB cable.
6. Open the Arduino IDE and install the ESP8266 board package and Blynk library.
7. Create a Blynk IoT template (iotexp61tempLEDONOFF) for NodeMCU ESP8266.
8. Create a Virtual Datastream V0 with integer values from 0 to 1.
9. Add a Button widget in the Blynk app and assign it to the V0 datastream.
10. Enter the Blynk Template ID, Template Name, and Auth Token in the program.
11. Enter the Wi-Fi SSID and password.
12. Compile and upload the program to the NodeMCU.
13. Open the Blynk mobile application.
14. Switch the traffic button ON (1).
15. Observe the automatic sequence of Red, Yellow, and Green LEDs (1 second each).
16. Switch the button OFF (0) to stop the traffic signal and turn all LEDs OFF.
*/
