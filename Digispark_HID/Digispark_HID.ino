#include "Keyboard.h"

void setup() {
  //initialize keyboard
  Keyboard.begin();
}

void loop() {
  Keyboard.print("Hello World!"); //print "Hello World!"
  delay(3000); //wait 3 seconds
}
