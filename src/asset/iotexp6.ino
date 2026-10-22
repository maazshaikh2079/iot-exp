// Experiment No  6: To design and implement a Smart Traffic Signal using NodeMCU ESP8266 and Blynk IoT, where a single button in the Blynk mobile application starts and stops the automatic traffic light sequence using Red, Yellow, and Green LEDs.
// iotexp61tempLEDONOFF:

#define BLYNK_TEMPLATE_ID "TMPL3o0UCw5RV"
#define BLYNK_TEMPLATE_NAME "iotexp61tempLEDONOFF"
#define BLYNK_AUTH_TOKEN "i7YqKwDJu2AmtsaeXcrGi-rdQfZeLZv3"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

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
