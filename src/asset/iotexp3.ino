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
*/
