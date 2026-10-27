# IoT Experiments (`iot-exp`)

**Live Web App:** [https://iot-exp.vercel.app](https://iot-exp.vercel.app)

A collection of Internet of Things (IoT) laboratory experiments built for **NodeMCU ESP8266** and **Arduino UNO**, featuring ready-to-download `.ino` sketches complete with circuit connections, hardware/software requirements, procedures, and expected outputs.

---

## Live Portal

Visit **[https://iot-exp.vercel.app](https://iot-exp.vercel.app)** to browse and download any experiment `.ino` file directly.

---

## Included Experiments (`src/asset/`)

| Exp No. | File | Experiment Title | Platform / Cloud |
| :--- | :--- | :--- | :--- |
| **Exp 3** | `iotexp3.ino` | Light Intensity Measurement using LDR and NodeMCU | NodeMCU ESP8266 + Serial Monitor |
| **Exp 4** | `iotexp4.ino` | To Upload DHT11 Temperature and Humidity Sensor Data on Arduino IDE App Using NodeMCU | NodeMCU ESP8266 + DHT11 + Blynk IoT |
| **Exp 5** | `iotexp5.ino` | To Upload Light Intensity Sensor Data using LDR, NodeMCU and Wireless Communication Protocol | NodeMCU ESP8266 + LDR + Blynk IoT |
| **Exp 6** | `iotexp6.ino` | Smart Traffic Signal using NodeMCU ESP8266 and Blynk IoT (Red, Yellow, Green LEDs) | NodeMCU ESP8266 + LEDs + Blynk IoT |
| **Exp 7** | `iotexp7.ino` | To interface the DHT22 temperature and humidity sensor with the NodeMCU ESP8266 and upload | NodeMCU ESP8266 + DHT22 + Blynk IoT |
| **Exp 8** | `iotexp8.ino` | To interface a DHT11/DHT22 sensor with Arduino UNO and ESP8266 Wi-Fi module and upload to ThingSpeak | Arduino UNO + ESP8266 + DHT11 + ThingSpeak |
| **Exp 9** | `iotexp9.ino` | To interface the DHT22 sensor with Arduino UNO and ESP8266 Wi-Fi module and upload to ThingSpeak | Arduino UNO + ESP8266 + DHT22 + ThingSpeak |
| **Exp 10** | `iotexp10.ino` | Publish–Subscribe communication model using MQTT protocol with DHT11 and NodeMCU ESP8266 | NodeMCU ESP8266 + DHT11 + HiveMQ Cloud MQTT |

---

## Project Structure

```text
iot-exp/
├── DESIGN.md              # Monolith Editorial Design System specification
├── README.md              # Project documentation
├── vercel.json            # Vercel routing configuration
└── src/
    ├── index.html         # Web portal for downloading experiment .ino files
    └── asset/
        ├── iotexp3.ino
        ├── iotexp4.ino
        ├── iotexp5.ino
        ├── iotexp6.ino
        ├── iotexp7.ino
        ├── iotexp8.ino
        ├── iotexp9.ino
        └── iotexp10.ino
```
