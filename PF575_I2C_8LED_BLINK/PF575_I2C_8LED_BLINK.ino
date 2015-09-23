#include <Wire.h>

/** 
 *  Arduino PF575/PCF8575 I2C I/O port exapander LED blink example
 *  
 *  Setup:
 *  
 *  1. Connect A0, A1 and A2 to GND to set the address to 0x20.
 *  2. Connect SDL and SCL to the Arduino's I2C bus.
 *  3. Connect a LED to the P0 port of the I2C exapander.
 *     In my setup I am using a PNP Transistor connected to 5V unsing 
 *     an resistor, the LED and the Arduino to make sure the LED gets
 *     a current from Vcc and not from the I2C exapander port.
 *  
 *  This code is trying to explain how it works as simple as possible.
 *  More detailed examples are found on the web. Search for pcf8575 and
 *  you will find what you want.
*/

// Set I2C address
int address = 0x20;

void setup(){ 
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

void loop(){
  int dTime = 150;
  pf575_write(word(B11111110,B11111111));
  delay(dTime);
  pf575_write(word(B11111101,B11111111));
  delay(dTime);
  pf575_write(word(B11111011,B11111111));
  delay(dTime);
  pf575_write(word(B11110111,B11111111));
  delay(dTime);
  pf575_write(word(B11101111,B11111111));
  delay(dTime);
  pf575_write(word(B11011111,B11111111));
  delay(dTime);
  pf575_write(word(B10111111,B11111111));
  delay(dTime);
  pf575_write(word(B01111111,B11111111));
  delay(dTime);
  pf575_write(word(B10111111,B11111111));
  delay(dTime);
  pf575_write(word(B11011111,B11111111));
  delay(dTime);
  pf575_write(word(B11101111,B11111111));
  delay(dTime);
  pf575_write(word(B11110111,B11111111));
  delay(dTime);
  pf575_write(word(B11111011,B11111111));
  delay(dTime);
  pf575_write(word(B11111101,B11111111));
  delay(dTime);
} 

// Function for writing two Bytes to the I2C expander device
void pf575_write(uint16_t data) {
  Wire.beginTransmission(address);
  Wire.write(highByte(data));
  Wire.write(lowByte(data));
  Wire.endTransmission();
}
