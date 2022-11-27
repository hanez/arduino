const int analogIn = A0;

int sensorValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(analogIn);
  Serial.print("Sensor: ");
  Serial.println(sensorValue);
  delay(2000);
}
