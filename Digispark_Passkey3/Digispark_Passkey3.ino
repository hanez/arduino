// Passkey for Arduino using the Digispark Rev.3 board.
// Copyright 2022 by Johannes Findeisen <you@hanez.org>
// Licensed under the terms of the MIT license.

// For using the Blinker library you have to install it from:
// https://github.com/MajenkoLibraries/Blinker
// Since the code is included in Passkey you easily can just copy
// Blinker/src/Blinker.cpp and Blinker/src/Blinker.h to the root of 
// Passkey.
#include "Blinker.h"
#include "DigiKeyboard.h"

// The button pin
#define BUTTON_PIN 0
// The LED pin
#define LED_PIN 1
// The pause after last button press before executing a command
#define PAUSE 2000

// Local variables
unsigned long last;
unsigned int count;

// Create blinker object
Blinker blinker(LED_PIN);

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
  // Set button pin to high.
  pinMode(BUTTON_PIN, INPUT);
  // Set BUTTON_PIN pin to high because the button is connected 
  // to GND when pressed and will go LOW
  digitalWrite(BUTTON_PIN, HIGH);

  // Set blink effect (ON, OFF) in milliseconds
  blinker.setDelay(25, 9075);
  blinker.start();

  // Initialize HID
  DigiKeyboard.delay(0);
  DigiKeyboard.sendKeyStroke(0);

  // Light up the LED for a second to show that passkey is ready
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Start LED blink effect
  blinker.blink();

  // Read button state
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Button is pressed
    count++;
    digitalWrite(LED_PIN, HIGH);
    // Wait until button is released
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(1);
    }
    // Set the last press timestamp
    last = millis();
    digitalWrite(LED_PIN, LOW);
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
