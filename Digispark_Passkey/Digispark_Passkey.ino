#include "DigiKeyboard.h"
#include <ezButton.h>

void setup() {
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  DigiKeyboard.delay(3000);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println("qMpI7Af06Z4XnMDhzXROnEgtuxPsCPLiBJT90Rb1F2BZKCmIhpLOdxtBpurUa9Tg");
}

void loop() {
  digitalWrite(1, HIGH);
  delay(25);  
  digitalWrite(1, LOW);
  delay(10000);
  //DigiKeyboard.delay(500000);
}
