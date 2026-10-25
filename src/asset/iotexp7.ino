// Experiment No  7: To interface the DHT22 temperature and humidity sensor with the NodeMCU ESP8266 and upload
// IotExp7TemperatureAndHumidity:

#define BLYNK_TEMPLATE_ID "TMPL3ZIkeTTMb"
#define BLYNK_TEMPLATE_NAME "IotExp7TemperatureAndHumidity"
#define BLYNK_AUTH_TOKEN "n5ginAg0sq7iSbVQ6G45XjfKlmaSFjQS"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "RCOE-202";
char pass[] = "rcoe1234";

// DHT22 settings
#define DHTPIN D2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// Function to read DHT22 and send data to Blynk
void sendSensorData()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if sensor reading failed
  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }

  // Display values in Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send data to Blynk
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}

void setup()
{
  Serial.begin(115200);

  // Start DHT22
  dht.begin();

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Send sensor data every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

void loop()
{
  Blynk.run();
  timer.run();
}

/*
Expected Output:
Temperature: 27.80 C
Humidity: 58.40 %
Temperature: 27.90 C
Humidity: 58.20 %
(Temperature and Humidity values are uploaded to Blynk Virtual Pins V0 and V1 every 2 seconds)

-----------------------------------------------------
Hardware Required:
- NodeMCU ESP8266
- DHT22 Temperature and Humidity Sensor
- Breadboard
- Jumper Wires
- USB Cable
- Wi-Fi Connection

Software Required:
- Arduino IDE
- Blynk IoT App
- ESP8266 Board Package
- Blynk Library
- DHT Sensor Library

Circuit Connections:
DHT22 Pin       NodeMCU Pin
--------------------------------------------------
VCC             3.3 V
GND             GND
DATA            D2 (GPIO4) [or D4 (GPIO2) if #define DHTPIN D4]

Blynk Datastreams:
- V0: Temperature
- V1: Humidity

Procedure:
1. Connect the DHT22 sensor to the NodeMCU as per the circuit connections table.
2. Install the ESP8266 board package and required libraries (Blynk, DHT) in the Arduino IDE.
3. Create a template (IotExp7TemperatureAndHumidity) and datastreams (V0 for Temperature and V1 for Humidity) in the Blynk Cloud.
4. Obtain the Blynk Authentication Token.
5. Enter the Wi-Fi credentials and Blynk Authentication Token in the program.
6. Compile and upload the program to the NodeMCU.
7. Open the Blynk App and connect the device.
8. Observe the temperature and humidity values displayed on the Serial Monitor (115200 baud) and Blynk dashboard.
*/
