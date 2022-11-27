#include "DigiKeyboard.h"

void setup() {
  pinMode(0, OUTPUT);
  DigiKeyboard.delay(2000);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println("test");
}

void loop() {
  DigiKeyboard.delay(500000);
}
