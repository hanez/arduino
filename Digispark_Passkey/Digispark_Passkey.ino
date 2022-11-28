#include "Blinker.h"
#include "DigiKeyboard.h"
#include "ezButton.h"

int ACTION_PIN = 0;
int LED_PIN = 1;

Blinker blinker(LED_PIN);
ezButton button(ACTION_PIN);

char *passwords[] = {
  "0qMpI7Af06Z4XnMDhzXROnEgtuxPsCPLiBJT90Rb1F2BZKCmIhpLOdxtBpurUa9Tg", 
  "1qMpI7Af06Z4XnMDhzXROnEgtuxPsCPLiBJT90Rb1F2BZKCmIhpLOdxtBpurUa9Tg",
  "2qMpI7Af06Z4XnMDhzXROnEgtuxPsCPLiBJT90Rb1F2BZKCmIhpLOdxtBpurUa9Tg",
  "3qMpI7Af06Z4XnMDhzXROnEgtuxPsCPLiBJT90Rb1F2BZKCmIhpLOdxtBpurUa9Tg"
};

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  blinker.setDelay(25, 10000);
  blinker.start();
  button.setCountMode(COUNT_RISING);
  button.setDebounceTime(0);
  DigiKeyboard.delay(0);
  DigiKeyboard.sendKeyStroke(0);
}

void loop() {
  blinker.blink();
  button.loop();

  /*digitalWrite(LED_PIN, HIGH);
  delay(25);  
  digitalWrite(1, LOW);
  delay(10000);*/
   
  if(button.isPressed()) {
    //DigiKeyboard.println("Hello World!");
    /*DigiKeyboard.println(passwords[0]);
    DigiKeyboard.println(passwords[1]);
    DigiKeyboard.println(passwords[2]);
    DigiKeyboard.println(passwords[3]);*/
  }

  unsigned long count = button.getCount();

  // press button five times to get a password
  if(count == 5) {
    //DigiKeyboard.println(count);
    DigiKeyboard.println(passwords[0]);
    button.resetCount();
  }
}
