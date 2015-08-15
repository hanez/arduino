int sensorPin = A0;
int ledPin = 13;
int sensorValue = 0;
float printValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  
  printValue = (sensorValue * 0.48828125);
  
  Serial.print(printValue);
  Serial.print("\n");
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
}
