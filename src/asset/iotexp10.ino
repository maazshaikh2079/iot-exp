// Experiment No  10: To implement the Publish–Subscribe communication model using the MQTT protocol by transmitting DHT11 temperature and humidity sensor data through a NodeMCU ESP8266.
// URL : 61156311cd4246998b465fd5b819e511.s1.eu.hivemq.cloud
// Username : Test123
// Password : Test@123
// Topics : student
// IoTExp10MQTT:

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

// =============================
// Wi-Fi
// =============================
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// =============================
// HiveMQ Cloud
// =============================

// Copy this from your HiveMQ Cloud cluster
const char* mqtt_server = "61156311cd4246998b465fd5b819e511.s1.eu.hivemq.cloud";

// HiveMQ Cloud TLS port
const int mqtt_port = 8883;

// MQTT credentials created in HiveMQ Cloud
const char* mqtt_username = "Test123";
const char* mqtt_password = "Test@123";

// MQTT topic
const char* mqtt_topic = "student";

// =============================
// DHT11
// =============================

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// =============================
// Secure MQTT connection
// =============================

WiFiClientSecure espClient;
PubSubClient client(espClient);

// =============================
// Connect Wi-Fi
// =============================

void setup_wifi()
{
  Serial.println();
  Serial.print("Connecting to Wi-Fi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// =============================
// Connect MQTT
// =============================

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Connecting to HiveMQ Cloud...");

    String clientID = "NodeMCU-DHT11-";
    clientID += String(ESP.getChipId());

    if (client.connect(
          clientID.c_str(),
          mqtt_username,
          mqtt_password))
    {
      Serial.println("CONNECTED!");
    }
    else
    {
      Serial.print("FAILED, rc=");
      Serial.println(client.state());

      delay(5000);
    }
  }
}

// =============================
// Setup
// =============================

void setup()
{
  Serial.begin(115200);

  dht.begin();

  setup_wifi();

  // For laboratory/testing use.
  // It encrypts the connection but does not validate
  // the broker certificate.
  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);
}

// =============================
// Loop
// =============================

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  // Read DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check reading
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("DHT11 reading failed!");
    delay(2000);
    return;
  }

  // Display on Serial Monitor
  Serial.println("-------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Create JSON message
  String message = "{";
  message += "\"temperature\":";
  message += String(temperature, 2);
  message += ",";
  message += "\"humidity\":";
  message += String(humidity, 2);
  message += "}";

  // Publish
  if (client.publish(mqtt_topic, message.c_str()))
  {
    Serial.println("MQTT Publish Successful!");

    Serial.print("Topic: ");
    Serial.println(mqtt_topic);

    Serial.print("Message: ");
    Serial.println(message);
  }
  else
  {
    Serial.println("MQTT Publish Failed!");
  }

  delay(5000);
}
