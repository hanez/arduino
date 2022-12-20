// Passkey for Arduino using the Digispark Rev.3 board.
// Copyright 2022 by Johannes Findeisen <you@hanez.org>
// Licensed under the terms of the MIT license.

// Maybe I need to use HIGH instead of LOW for triggering and then I think I need a pullup resistor 
// when using the LED pin as INPUT pin:
// https://electronics.stackexchange.com/questions/361944/digispark-pin-mode-input-pullup-reading-low-on-pin-1
// A pulldown resistor should maybe do the work too.
// I like the pulldown idea because the button is easier to connect on a breadboard with one less cable... ;)

// More info:
// https://arduino.stackexchange.com/questions/75473/using-the-led-pin-for-input
// http://thetoivonen.blogspot.com/2015/12/fixing-pin-p5-or-6-on-digispark-clones.html

// NOTE: I tested it when make triggering on HIGH without using a pullup resistor and it works. Need to set 
// the pin to LOW in setup() though. No need to read LOW from that pin anymore and no resistor required... \o/
// I need to evaluate this pulldown-/up stuff a little more.
#include "DigiKeyboard.h"

// The button pin
#define BUTTON_PIN 1
// The pause after last button press before executing a command
#define PAUSE 2000

// Local variables
unsigned long last;
unsigned int count;

// The list of available passwords
// The number and overall lenght of passwords depends 
// because the memory of the digispark is very limited...
// I recommend to use a prefix you easily can remember 
// for the password/passwords to make the passwords
// on the passkey unusable for others in case you've lost 
// your passkey. E.g.: WhatAWonderfulWorld -> then press the button.
const char *passwords[] = {
  // passwords[0]
  "n0Emb871NAQPSIqBoldh8R7UDaNhncF7Pt60Amdo6GWdTdAPwVBi2A3KU8x8DTCRo6GWdTdXNn2wLh3SUbxVWQvFDVPtatDg",
  // passwords[1]
  "oaxt6e3lSgflOuJ3C6Q6sUb5gvmvI5IEPFku5fqcbxJljBOUblHIT121wCu",
  // passwords[2]
  "jUgKGBtiJ0iNN1Ok9vejrXNn2wLh3SUbxVWQvFDVPtat0OxJlKU8x8DTCRo6GWdTdAPwVBi2A3KUrTKQwjUgK",
  // passwords[3]
  "G57dFnXsPUnRq1eC1CjrGxpCjuiJFlDti54W6wBS9Ro6GWdTdAPwVBi2A3KU8x8KGBtiJ0iNN1Ok9vejrXNn2wLhH" 
};

void setup() {
  // Set button pin to be INPUT.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // Set BUTTON_PIN pin to LOW because the button is connected 
  // to VCC when pressed and will go HIGH.
  digitalWrite(BUTTON_PIN, LOW);
  // Initialize HID
  DigiKeyboard.delay(0);
  DigiKeyboard.sendKeyStroke(0);
}

void loop() {
  // Read button state
  if (digitalRead(BUTTON_PIN) == HIGH) {
    // Button is pressed; increment count.
    count++;
    // Wait until button is released
    while (digitalRead(BUTTON_PIN) == HIGH) {
      delay(1);
    }
    // Set the last press timestamp
    last = millis();
  }
  // Wait PAUSE time before executing a command
  if (count > 0 && (millis() - last) >= PAUSE) {
    // The switch case is the number of button presses
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
        // You can use print instead of println if you don't want 
        // to hit enter automatically after inserting the password
        DigiKeyboard.print(passwords[3]);
        break;
      default:
        break;
    }
    // Reset the counter
    count = 0;
  }
}
