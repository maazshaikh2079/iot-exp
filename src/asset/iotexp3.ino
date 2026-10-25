// Experiment No  3: Light Intensity Measurement using LDR and NodeMCU
// IoTExp3LightIntensity:

const int LDR = A0;
int input_val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // GPIO13 (D7 on NodeMCU)
}

void loop() {
  input_val = analogRead(LDR);
  Serial.print("LDR value is : ");
  Serial.println(input_val);

  if (input_val < 50) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  delay(1000);
}

/*
Expected Output:
The Serial Monitor displays the light intensity values.
Light Intensity: 145
Light Intensity: 382
Light Intensity: 765

-----------------------------------------------------
Hardware Required:
- NodeMCU ESP8266
- LDR Sensor
- 10 kOhm Resistor
- LED (Optional, for dark threshold indicator on D7 / GPIO13)
- Breadboard
- Jumper Wires
- USB Cable

Software Required:
- Arduino IDE

Circuit Connections:
LDR Circuit             NodeMCU Pin
-----------------------------------
Voltage Divider Output  A0
VCC                     3.3 V
GND                     GND
LED Anode (Optional)    D7 (GPIO13)
LED Cathode (Optional)  GND

Procedure:
1. Connect the LDR and 10 kOhm resistor in a voltage divider circuit.
2. Connect the voltage divider output to the A0 pin of the NodeMCU, VCC to 3.3 V, and GND to GND (and optionally connect an LED to D7/GPIO13).
3. Open the Arduino IDE and select the NodeMCU 1.0 (ESP-12E Module) board and COM port.
4. Write or upload the program to the NodeMCU.
5. Open the Serial Monitor at 9600 baud rate.
6. Observe the light intensity values while changing the amount of light falling on the LDR.
*/
