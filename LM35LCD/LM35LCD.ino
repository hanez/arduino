// Written 2015 by Johannes Findeisen <you@hanez.org>

#include <LiquidCrystal.h>

// Initialize the LCD code. Take care of the pins I use. The first two pins 
// are 12 and 11 in most examples around the web. I use pin 7 and 6 because of 
// nicer wiring on my breadboard.
// Read this for more information:
// https://www.arduino.cc/en/Tutorial/LiquidCrystal
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Define how many samples should be collected every $collectDelay miliseconds.
// After sample collection the temperature is beeing calculated and then
// send to the LCD. 
int samples = 30;

// Collect delay between each sample. 
int collectDelay = 2000;

// The pin where the status LED is connected to.
int ledPin = 13;

// The analog input pin where the LM35 is connected to.
int tempPin = 0;

// Just some variable initializations
float tempC = 0;
float tempClast = 0;
float tempF = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  tempC = (5.0 * analogRead(tempPin) * 100.0) / 1024.0;
  tempF = (tempC * 9) / 5 + 32;
  lcd_print();
}

// Prints results to the display
void lcd_print() {
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print((char)223);
  lcd.print("C/");
  lcd.print(tempF);
  lcd.print((char)223);
  lcd.print("F");
  if(tempClast > tempC) {
    lcd.print("-");
  } else if(tempClast < tempC) {
    lcd.print("+");
  } else {
    lcd.print("*");
  }
}

void loop() {
  int i;
  tempC = 0;
  for(i = 0; i <= (samples - 1); i++) {
    // Read this to understand the temperature calculation:
    // http://www.danielandrade.net/2008/07/05/temperature-sensor-arduino/
    tempC = tempC + ((5.0 * analogRead(tempPin) * 100.0) / 1024.0);
    digitalWrite(ledPin, HIGH);
    delay((collectDelay / 2));
    digitalWrite(ledPin, LOW);
    delay((collectDelay / 2));
  }
  // Calculate temperature
  tempC = tempC / (float)samples;
  // Celsius to Fahrenheit cobversation
  tempF = (tempC * 9) / 5 + 32;
  // Print result to the display
  lcd_print();
  // Remember current temperature for next run
  tempClast = tempC;
}
