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
