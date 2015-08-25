// Written 2015 by Johannes Findeisen <you@hanez.org>

#include <Wire.h>
#include <BH1750FVI.h>
#include <LiquidCrystal_I2C.h>

BH1750FVI LightSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 20 chars and 4 line display

// Define how many samples should be collected every $collectDelay miliseconds.
// After sample collection the temperature is beeing calculated and then
// send to the LCD.
int samples = 8;

// Collect delay between each sample.
int collectDelay = 1000;

// The pin where the status LED is connected to.
int ledPin = 13;

// The analog input pin where the LM35 is connected to.
int tempPin = 0;

// Just some variable initializations.
float tempC = 0;
float tempClast = 0;
float tempF = 0;

uint16_t lux = 0;

int photo = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);

  Wire.begin();

  LightSensor.begin();
  LightSensor.SetAddress(Device_Address_L); // Address 0x23
  LightSensor.SetMode(Continuous_H_resolution_Mode);

  lcd.init();
  lcd.backlight();

  // Get data for the first time.
  // Read this to understand the temperature calculation:
  // http://www.danielandrade.net/2008/07/05/temperature-sensor-arduino/
  tempC = (5.0 * analogRead(tempPin) * 100.0) / 1024.0;
  tempClast = tempC;

  // Celsius to Fahrenheit conversion
  tempF = (tempC * 9) / 5 + 32;

  // Get light sensor data
  lux = LightSensor.GetLightIntensity();

  // Get data from other Arduino on 0x07
  read_wire();

  // Refresh the LCD output
  lcd_refresh();
}

void loop()
{
  int i;
  tempC = 0;
  for (i = 0; i <= (samples - 1); i++) {
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

  // Get light sensor data
  lux = LightSensor.GetLightIntensity();

  // Get data from I2C attached Arduino
  read_wire();

  // Print results to the display.
  lcd_refresh();

  // Remember current temperature for next run.
  tempClast = tempC;
}

// Prints results to the display
void lcd_refresh() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(lux);
  lcd.print("Lux/");
  lcd.print(photo);
  lcd.print((char)0b11110100); // Thats the sign for Ohm but the value is not Ohm. I use this sign to represent the photo resister value
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print((char)223); // ASCII code 223 = "°"
  lcd.print("C/");
  lcd.print(tempF);
  lcd.print((char)223); // ASCII code 223 = "°"
  lcd.print("F");
}

void read_wire() {
  Wire.requestFrom(7, 1); // request 1 bytes from slave device #7
  photo = Wire.read();
}

