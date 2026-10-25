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
*/
