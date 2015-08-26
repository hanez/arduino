// Written 2015 by Johannes Findeisen <you@hanez.org>

#include <Wire.h>

void setup() {
  pinMode(13, OUTPUT);
  Wire.begin();
}

void loop() {
  Wire.requestFrom(7, 1); // request 1 byte from slave device #7
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(950);
}
