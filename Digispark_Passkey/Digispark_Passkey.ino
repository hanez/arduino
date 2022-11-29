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
const char *passwords[] = {
  "PASSWORD1", 
  "PASSWORD2",
  "PASSWORD3",
  "PASSWORD4"
};

void setup() {
  // set button pin to high
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);

  // light up the LED for a second to show that passkey is ready
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

  // set blink effect (ON, OFF) in milliseconds
  blinker.setDelay(25, 10000);
  blinker.start();
  
  // initialize HID
  DigiKeyboard.delay(0);
  DigiKeyboard.sendKeyStroke(0);
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
    while(digitalRead(BUTTON_PIN) == LOW) {
      delay(1);
    }
  }

  // wait PAUSE time before executing a command
  if (count > 0 && (millis() - last) >= PAUSE) {
    // the switch case is the number of button presses
    switch(count) {
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
        DigiKeyboard.println(passwords[3]);
        break;
      default:
        break;
    }
    count = 0; // reset the counter
  }
}
