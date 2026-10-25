// Experiment No  8: To interface a DHT11/DHT22 temperature and humidity sensor with an Arduino UNO and ESP8266 Wi-Fi module and upload the sensor data to the ThingSpeak cloud platform for real-time monitoring
// DHT22 Temperature and Humidity:

// ThingSpeak | maazshaikh@eng.rizvi.edu.in
// Channel Name: DHT22 Temperature and Humidity
// Channel ID: 3545156
// Author: mwa0000042963098
// Access: Private
// Write API Key: 92GO4BH3TFPNRTO5
// Read API Key: 13ARI7ZVW3C599PW

#include <SoftwareSerial.h>
#include <DHT.h>

// =====================================================
// DHT11 SETTINGS
// =====================================================

#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

// =====================================================
// ESP8266 SERIAL
// =====================================================
//
// Arduino UNO:
// D10 = RX -> receives ESP8266 TX
// D11 = TX -> sends to ESP8266 RX
//
// IMPORTANT:
// D11 -> VOLTAGE DIVIDER -> ESP8266 RX
// =====================================================

#define ESP_RX 10
#define ESP_TX 11

SoftwareSerial espSerial(ESP_RX, ESP_TX);

// =====================================================
// WIFI SETTINGS
// =====================================================

const char* WIFI_SSID = "RCOE-202";
const char* WIFI_PASSWORD = "rcoe1234";

// =====================================================
// THINGSPEAK SETTINGS
// =====================================================

const char* THINGSPEAK_API_KEY = "92GO4BH3TFPNRTO5";
const char* THINGSPEAK_HOST = "api.thingspeak.com";

// =====================================================
// UPDATE INTERVAL
// =====================================================

const unsigned long UPDATE_INTERVAL = 20000;

unsigned long previousMillis = 0;

// =====================================================
// FUNCTION: Clear ESP8266 serial buffer
// =====================================================

void clearESPBuffer()
{
  while (espSerial.available())
  {
    espSerial.read();
  }
}

// =====================================================
// FUNCTION: Send AT command
// =====================================================

bool sendATCommand(
  String command,
  String expected,
  unsigned long timeout
)
{
  clearESPBuffer();

  Serial.print(">> ");
  Serial.println(command);

  espSerial.println(command);

  unsigned long startTime = millis();

  String response = "";

  while (millis() - startTime < timeout)
  {
    while (espSerial.available())
    {
      char c = espSerial.read();

      response += c;

      Serial.write(c);

      if (response.indexOf(expected) >= 0)
      {
        Serial.println();
        return true;
      }

      if (response.indexOf("ERROR") >= 0)
      {
        Serial.println();
        return false;
      }

      if (response.indexOf("FAIL") >= 0)
      {
        Serial.println();
        return false;
      }
    }
  }

  Serial.println();
  Serial.println("TIMEOUT");

  return false;
}

// =====================================================
// FUNCTION: Initialize ESP8266
// =====================================================

bool initializeESP8266()
{
  Serial.println();
  Serial.println("================================");
  Serial.println("Initializing ESP8266-12E");
  Serial.println("================================");

  // Test communication
  if (!sendATCommand("AT", "OK", 3000))
  {
    Serial.println("ESP8266 did not respond.");
    return false;
  }

  // Disable command echo
  sendATCommand("ATE0", "OK", 3000);

  // Set Wi-Fi station mode
  if (!sendATCommand("AT+CWMODE=1", "OK", 5000))
  {
    Serial.println("Could not set station mode.");
    return false;
  }

  Serial.println("ESP8266 initialized.");

  return true;
}

// =====================================================
// FUNCTION: Connect ESP8266 to Wi-Fi
// =====================================================

bool connectWiFi()
{
  Serial.println();
  Serial.println("================================");
  Serial.println("Connecting to Wi-Fi");
  Serial.println("================================");

  String command =
    "AT+CWJAP=\"" +
    String(WIFI_SSID) +
    "\",\"" +
    String(WIFI_PASSWORD) +
    "\"";

  if (sendATCommand(command, "OK", 30000))
  {
    Serial.println();
    Serial.println("Wi-Fi connected!");

    return true;
  }

  Serial.println();
  Serial.println("Wi-Fi connection failed.");

  return false;
}

// =====================================================
// FUNCTION: Check Wi-Fi status
// =====================================================

bool checkWiFi()
{
  clearESPBuffer();

  espSerial.println("AT+CIPSTATUS");

  unsigned long startTime = millis();

  String response = "";

  while (millis() - startTime < 5000)
  {
    while (espSerial.available())
    {
      char c = espSerial.read();

      response += c;

      Serial.write(c);
    }
  }

  Serial.println();

  // STATUS:2 = got IP
  // STATUS:3 = connected
  if (response.indexOf("STATUS:2") >= 0 ||
      response.indexOf("STATUS:3") >= 0)
  {
    return true;
  }

  return false;
}

// =====================================================
// FUNCTION: Send sensor data to ThingSpeak
// =====================================================

bool sendToThingSpeak(
  float temperature,
  float humidity
)
{
  Serial.println();
  Serial.println("================================");
  Serial.println("Sending data to ThingSpeak");
  Serial.println("================================");

  // ---------------------------------------------------
  // Start TCP connection
  // ---------------------------------------------------

  String tcpCommand =
    "AT+CIPSTART=\"TCP\",\"" +
    String(THINGSPEAK_HOST) +
    "\",80";

  if (!sendATCommand(tcpCommand, "OK", 10000))
  {
    Serial.println("TCP connection failed.");

    sendATCommand(
      "AT+CIPCLOSE",
      "OK",
      3000
    );

    return false;
  }

  // ---------------------------------------------------
  // Create HTTP GET request
  // ---------------------------------------------------

  String request =
    "GET /update?api_key=" +
    String(THINGSPEAK_API_KEY) +
    "&field1=" +
    String(temperature, 1) +
    "&field2=" +
    String(humidity, 1) +
    " HTTP/1.1\r\n"
    "Host: api.thingspeak.com\r\n"
    "Connection: close\r\n"
    "\r\n";

  // ---------------------------------------------------
  // Tell ESP8266 number of bytes
  // ---------------------------------------------------

  String sendCommand =
    "AT+CIPSEND=" +
    String(request.length());

  if (!sendATCommand(
    sendCommand,
    ">",
    5000
  ))
  {
    Serial.println("CIPSEND failed.");

    sendATCommand(
      "AT+CIPCLOSE",
      "OK",
      3000
    );

    return false;
  }

  // ---------------------------------------------------
  // Send HTTP request
  // ---------------------------------------------------

  Serial.println("HTTP request:");
  Serial.println(request);

  espSerial.print(request);

  // ---------------------------------------------------
  // Read ThingSpeak response
  // ---------------------------------------------------

  unsigned long startTime = millis();

  String response = "";

  while (millis() - startTime < 10000)
  {
    while (espSerial.available())
    {
      char c = espSerial.read();

      response += c;

      Serial.write(c);
    }
  }

  Serial.println();
  Serial.println("--------------------------------");
  Serial.println("ThingSpeak server response:");
  Serial.println(response);
  Serial.println("--------------------------------");

  // ---------------------------------------------------
  // Close TCP connection
  // ---------------------------------------------------

  sendATCommand(
    "AT+CIPCLOSE",
    "OK",
    3000
  );

  // ---------------------------------------------------
  // Check ThingSpeak response
  // ---------------------------------------------------

  if (response.indexOf("\r\n0\r\n") >= 0)
  {
    Serial.println("ThingSpeak update FAILED.");
    return false;
  }

  if (response.indexOf("200 OK") >= 0)
  {
    Serial.println("ThingSpeak update successful!");
    return true;
  }

  // ThingSpeak may return an entry number.
  if (response.indexOf("\r\n1\r\n") >= 0)
  {
    Serial.println("ThingSpeak update successful!");
    return true;
  }

  Serial.println("Server response received.");

  return true;
}

// =====================================================
// SETUP
// =====================================================

void setup()
{
  // Arduino USB Serial
  Serial.begin(9600);

  // ESP8266 Serial
  espSerial.begin(9600);

  // Start DHT11
  dht.begin();

  Serial.println();
  Serial.println("======================================");
  Serial.println(" DHT11 + Arduino UNO + ESP8266-12E");
  Serial.println(" ThingSpeak IoT Temperature Monitor");
  Serial.println("======================================");

  delay(2000);

  // ---------------------------------------------------
  // Initialize ESP8266
  // ---------------------------------------------------

  if (!initializeESP8266())
  {
    Serial.println();
    Serial.println("ERROR:");
    Serial.println("ESP8266 initialization failed.");
    Serial.println("Check wiring and power.");
  }

  // ---------------------------------------------------
  // Connect Wi-Fi
  // ---------------------------------------------------

  if (!connectWiFi())
  {
    Serial.println();
    Serial.println("WARNING:");
    Serial.println("Wi-Fi connection failed.");
  }
}

// =====================================================
// LOOP
// =====================================================

void loop()
{
  unsigned long currentMillis = millis();

  // ---------------------------------------------------
  // Read sensor every 20 seconds
  // ---------------------------------------------------

  if (
    currentMillis - previousMillis >= UPDATE_INTERVAL ||
    previousMillis == 0
  )
  {
    previousMillis = currentMillis;

    // ================================================
    // Read DHT11
    // ================================================

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // ================================================
    // Check DHT11
    // ================================================

    if (
      isnan(humidity) ||
      isnan(temperature)
    )
    {
      Serial.println();
      Serial.println("ERROR: DHT11 reading failed.");

      Serial.println("Check:");

      Serial.println("1. DHT11 + -> Arduino 5V");
      Serial.println("2. DHT11 OUT -> Arduino D2");
      Serial.println("3. DHT11 - -> Arduino GND");

      return;
    }

    // ================================================
    // Display sensor values
    // ================================================

    Serial.println();
    Serial.println("======================================");

    Serial.print("Temperature = ");
    Serial.print(temperature, 1);
    Serial.println(" C");

    Serial.print("Humidity = ");
    Serial.print(humidity, 1);
    Serial.println(" %");

    Serial.println("======================================");

    // ================================================
    // Check Wi-Fi
    // ================================================

    if (!checkWiFi())
    {
      Serial.println("Wi-Fi connection lost.");

      Serial.println("Reconnecting...");

      if (!connectWiFi())
      {
        Serial.println("Wi-Fi reconnection failed.");
        return;
      }
    }

    // ================================================
    // Upload to ThingSpeak
    // ================================================

    sendToThingSpeak(
      temperature,
      humidity
    );
  }
}

/*
Expected Output:
======================================
 DHT11 + Arduino UNO + ESP8266-12E
 ThingSpeak IoT Temperature Monitor
======================================

================================
Initializing ESP8266-12E
================================
>> AT
OK
ESP8266 initialized.

================================
Connecting to Wi-Fi
================================
>> AT+CWJAP="RCOE-202","rcoe1234"
WIFI CONNECTED
WIFI GOT IP
OK
Wi-Fi connected!

======================================
Temperature = 28.0 C
Humidity = 60.0 %
======================================

================================
Sending data to ThingSpeak
================================
ThingSpeak update successful!
*/
