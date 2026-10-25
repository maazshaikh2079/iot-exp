// Experiment No  4: To Upload DHT11 Temperature and Humidity Sensor Data on Arduino IDE App Using NodeMCU
// IoTExp4TemperatureAndHumidity:

#define BLYNK_TEMPLATE_ID "TMPL3_-bmJ683"
#define BLYNK_TEMPLATE_NAME "IoTExp4TemperatureAndHumidity"
#define BLYNK_AUTH_TOKEN "9TGYS0k0pHokdPzW7cLRjg74GnEKFlRm"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "RCOE-202";
char pass[] = "rcoe1234";

#define DHTPIN D5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT11!");
    return;
  }

  // Print values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" C");

  Serial.print(" | Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // Send values to Blynk
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  Serial.println("Data sent to Blynk");
  Serial.println("--------------------");
}

void setup()
{
  Serial.begin(9600);
  delay(1000);

  Serial.println();
  Serial.println("ESP8266 Starting...");
  Serial.println("Initializing DHT11...");

  dht.begin();

  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Blynk connected!");

  timer.setInterval(2000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

/*
Expected Output:
ESP8266 Starting...
Initializing DHT11...
Connecting to Blynk...
Blynk connected!
Temperature: 28.40 C | Humidity: 62.00 %
Data sent to Blynk
--------------------
Temperature: 28.50 C | Humidity: 61.00 %
Data sent to Blynk
--------------------

-----------------------------------------------------
Hardware Required:
- NodeMCU ESP8266
- DHT11 Temperature and Humidity Sensor
- Breadboard
- Jumper Wires
- USB Cable
- Wi-Fi Connection

Software Required:
- Arduino IDE
- Blynk IoT Mobile App / Web Dashboard
- Blynk Library
- DHT Sensor Library
- ESP8266 Board Package

Circuit Connections:
DHT11 Pin       NodeMCU Pin
---------------------------
VCC             3.3 V / 5 V (VIN)
GND             GND
DATA            D5 (GPIO14)

Blynk Datastreams:
- V0: Temperature
- V1: Humidity

Procedure:
1. Connect the DHT11 sensor to the NodeMCU as per the circuit connections table (DATA to D5).
2. Install the Blynk, DHT sensor library, and ESP8266 board package in the Arduino IDE.
3. Create a template (IoTExp4TemperatureAndHumidity) and virtual pin datastreams (V0 for Temperature, V1 for Humidity) in the Blynk Cloud.
4. Obtain the Blynk Template ID, Template Name, and Authentication Token.
5. Enter the Wi-Fi SSID, password, and Blynk credentials in the program.
6. Compile and upload the program to the NodeMCU.
7. Open the Serial Monitor (9600 baud) and the Blynk App/Dashboard.
8. Observe the real-time temperature and humidity values on the Serial Monitor and Blynk dashboard.
*/
