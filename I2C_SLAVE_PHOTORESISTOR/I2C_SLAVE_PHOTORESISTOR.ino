// Written 2015 by Johannes Findeisen <you@hanez.org>

#include <Wire.h>

int lightPin = 0;

void setup()
{
  pinMode(13, OUTPUT);
  Wire.begin(7); // join i2c bus with address #7
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600); //Begin serial communcation
}

void loop()
{
  //Serial.println(analogRead(lightPin));
  //delay(60000);
}

void requestEvent()
{
  Wire.write(analogRead(lightPin)); // respond with message of 6 bytes
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
}
