#include <Wire.h>

// Set I2C address
int address = 0x20;

int samples = 2;
int collectDelay = 1000;
int ledPin = 13;
int tempPin = 0;

float tempC = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Wire.begin();
  pf575_write(word(B11111111,B11111111));
  delay(200);
  pf575_write(word(B00000000,B11111111));
  delay(200);
  pf575_write(word(B11111111,B11111111));
  delay(200);
  pf575_write(word(B00000000,B11111111));
  delay(200);
  pf575_write(word(B11111111,B11111111));
  delay(1000);
} 

void loop() {
  tempC = 0;
  for(int i = 0; i <= (samples - 1); i++) {
    tempC = tempC + ((5.0 * analogRead(tempPin) * 100.0) / 1024.0);
    digitalWrite(ledPin, HIGH);
    delay((collectDelay / 2));
    digitalWrite(ledPin, LOW);
    delay((collectDelay / 2));
  }
  tempC = tempC / (float)samples;
  if(tempC > 21) {
    pf575_write(word(B11111110,B11111111));
  }
  if(tempC > 23) {
    pf575_write(word(B11111100,B11111111));
  }
  if(tempC > 25) {
    pf575_write(word(B11111000,B11111111));
  }
  if(tempC > 27) {
    pf575_write(word(B11110000,B11111111));
  }
  if(tempC > 29) {
    pf575_write(word(B11100000,B11111111));
  }
  if(tempC > 31) {
    pf575_write(word(B11000000,B11111111));
  }
  if(tempC > 33) {
    pf575_write(word(B10000000,B11111111));
  }
  if(tempC > 35) {
    pf575_write(word(B00000000,B11111111));
  }
} 

void pf575_write(uint16_t data) {
  Wire.beginTransmission(address);
  Wire.write(highByte(data));
  Wire.write(lowByte(data));
  Wire.endTransmission();
}
