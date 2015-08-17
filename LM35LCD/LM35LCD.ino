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
int samples = 16;

// Collect delay between each sample. 
int collectDelay = 2000;

// The pin where the status LED is connected to.
int ledPin = 13;

// The analog input pin where the LM35 is connected to.
int tempPin = 0;

// Just some variable initializations.
float tempC = 0;
float tempClast = 0;
float tempF = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
  // Get data for the first time.
  // Read this to understand the temperature calculation:
  // http://www.danielandrade.net/2008/07/05/temperature-sensor-arduino/
  tempC = (5.0 * analogRead(tempPin) * 100.0) / 1024.0;
  tempClast = tempC;
  // Celsius to Fahrenheit conversion
  tempF = (tempC * 9) / 5 + 32;
  // Refresh the LCD output
  lcd_refresh();
}

void loop() {
  int i;
  tempC = 0;
  for(i = 0; i <= (samples - 1); i++) {
    tempC = tempC + ((5.0 * analogRead(tempPin) * 100.0) / 1024.0);
    digitalWrite(ledPin, HIGH);
    delay((collectDelay / 2));
    digitalWrite(ledPin, LOW);
    delay((collectDelay / 2));
  }
  // Calculate temperature
  tempC = tempC / (float)samples;
  // Celsius to Fahrenheit conversion.
  tempF = (tempC * 9) / 5 + 32;
  // Print results to the display.
  lcd_refresh();
  // Remember current temperature for next run.
  tempClast = tempC;
}

// Prints results to the display
void lcd_refresh() {
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.print((char)40); // ASCII code 40 = "("
  if(tempClast > tempC) {
    lcd.print((char)60); // ASCII code 60 = "<"
  } else if(tempClast < tempC) {
    lcd.print((char)62); // ASCII code 62 = ">"
  } else {
    lcd.print((char)61); // ASCII code 61 = "="
  }
  lcd.print((char)41); // ASCII code 41 = ")"
  lcd.print((char)58); // ASCII code 58 = ":"
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print((char)223); // ASCII code 223 = "°"
  lcd.print("C/");
  lcd.print(tempF);
  lcd.print((char)223); // ASCII code 223 = "°"
  lcd.print("F");
}
