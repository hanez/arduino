#include <Wire.h> 

//fuzzywobble.com 2012
//this code turns every PCF8575 pin into an input (without interrupt)
//datasheet - http://www.ti.com/general/docs/lit/getliterature.tsp?genericPartNumber=pcf8575&fileType=pdf
//i2c code adapted from i2c_dio_pcf8575c.cpp - Arduino class library for TI PCF8575C 16-bit I2C I/O expander

//address is |0100|A0|A1|A2|
int address = 0x20; //0100000 (7bit)  
uint16_t dataReceive; //16bit data received
uint16_t dataSend;  //16bit data sent

void setup(){ 
  Wire.begin(); 
  Serial.begin(9600);
  //turn pins to input in setup
  //if bit = 0, pin functions as input or an output that is off
  //if bit = 1, pin functions as an output that is on
  dataSend = word(B01111111,B11111111); //turn every pin to output
  pcf8575_write(dataSend); //turn the pcf8575 pins to output
} 

void loop(){ 
  dataSend = word(B01111110,B01110001);
  pcf8575_write(dataSend); //read the pcf8575 pins
  delay(100);
  dataSend = word(B00000000,B00000000);
  pcf8575_write(dataSend); //read the pcf8575 pins
  delay(100);
} 


//custom functions -----------------------------

//I2C/TWI success (transaction was successful).
static const uint8_t ku8TWISuccess                   = 0;
//I2C/TWI device not present (address sent, NACK received).
static const uint8_t ku8TWIDeviceNACK                = 2;
//I2C/TWI data not received (data sent, NACK received).
static const uint8_t ku8TWIDataNACK                  = 3;
//I2C/TWI other error.
static const uint8_t ku8TWIError                     = 4;

uint8_t error;
void pcf8575_write(uint16_t dt){
  Wire.beginTransmission(address);
  Wire.write(lowByte(dt));
  Wire.write(highByte(dt));
  error = Wire.endTransmission();
  if(error == ku8TWISuccess){ //okay!
  
  }
  else{ //we have an error
    //do something here if you like
  }
}
uint8_t hi,lo;
uint16_t pcf8575_read(){
  Wire.beginTransmission(address);
  error = Wire.endTransmission();
  if(error == ku8TWISuccess){ //okay!
    Wire.requestFrom(address,2); 
    if(Wire.available()){
      lo = Wire.read();
      hi = Wire.read();
      return(word(hi,lo)); //joing bytes 
    }
    else{//error
      //do something here if you like  
    }
  }
  else{ //error
    //do something here if you like  
  }
}




