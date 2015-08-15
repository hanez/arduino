void setup()
{
  Serial.begin(9600); // USB is always 12 Mbit/sec
}

void loop()
{
  digitalWrite(13, HIGH);
  Serial.println("Hello World...");
  delay(1000);
  digitalWrite(13, LOW);
  //Serial.println("Hello World...");
  delay(1000);
}
