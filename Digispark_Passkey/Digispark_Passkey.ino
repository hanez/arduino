#include "Blinker.h"
#include "DigiKeyboard.h"

// the button pin
#define BUTTON_PIN 0
// the LED pin
#define LED_PIN 1
// the pause after last button press before executing a command
#define PAUSE 2000

// local variables
unsigned long last;
unsigned int count;

// create blinker
Blinker blinker(LED_PIN);

// the list of available passwords
// the number and overall lenght of passwords depends because the memory of the digispark is very limited...
// i recommend to use a prefix you easily can remember for the password/passwords to make the passwords
// on the passkey unusable for others if you have lost your passkey. E.g.: WhatAWonderfulWorld -> then press the button.
const char *passwords[] = {
  "n0Emb871NAQPSIqBoldh8R7UDaNhncF7Pt60Amdo6GWdTdAPwVBi2A3KU8x8DTCRo6GWdTdXNn2wLh3SUbxVWQvFDVPtatDg", // passwords[0]
  "oaxt6e3lSgflOuJ3C6Q6sUb5gvmvI5IEPFku5fqcbxJljBOUblHIT121wCu", // passwords[1]
  "jUgKGBtiJ0iNN1Ok9vejrXNn2wLh3SUbxVWQvFDVPtat0OxJlKU8x8DTCRo6GWdTdAPwVBi2A3KUrTKQwjUgK", // passwords[2]
  "G57dFnXsPUnRq1eC1CjrGxpCjuiJFlDti54W6wBS9Ro6GWdTdAPwVBi2A3KU8x8KGBtiJ0iNN1Ok9vejrXNn2wLhH" // etc...
};

void setup() {
  // set button pin to high
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);

  // set blink effect (ON, OFF) in milliseconds
  blinker.setDelay(25, 10000);
  blinker.start();

  // initialize HID
  DigiKeyboard.delay(0);
  DigiKeyboard.sendKeyStroke(0);

  // light up the LED for a second to show that passkey is ready
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // start LED blink effect
  blinker.blink();

  // read button state
  if (digitalRead(BUTTON_PIN) == LOW) {
    // button is pressed
    last = millis();
    count++;
    // wait until button is released
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(1);
    }
  }

  // wait PAUSE time before executing a command
  if (count > 0 && (millis() - last) >= PAUSE) {
    // the switch case is the number of button presses
    switch (count) {
      case 1:
        DigiKeyboard.println(passwords[0]);
        break;
      case 2:
        DigiKeyboard.println(passwords[1]);
        break;
      case 3:
        DigiKeyboard.println(passwords[2]);
        break;
      case 5:
        // you can use print instead of println if you don't want to
        // hit enter automatically after inserting the password
        DigiKeyboard.print(passwords[3]);
        break;
      default:
        break;
    }
    // reset the counter
    count = 0;
  }
}
