// --------------------------------------
 // i2c_scanner
 //
 // This program (or code that looks like it)
 // can be found in many places.
 // For example on the Arduino.cc forum.
 // The original author is not know.
 //
 // This sketch tests the standard 7-bit addresses
 // from 0 to 127. Devices with higher bit address
 // might not be seen properly.
 //
 // Adapted to be as simple as possible by Arduino.cc user Krodal
 //
 // June 2012
 // Using Arduino 1.0.1
 //
 // Source: https://forum.arduino.cc/t/atmel-24c256-showing-up-at-wrong-i2c-address/123760/4
 // Better code but not working for me:
 // https://create.arduino.cc/projecthub/sainisagar7294/how-to-find-i2c-address-using-arduino-a24f72
 // https://stackoverflow.com/questions/57978198/can-an-i2c-eeprom-have-two-addresses
 
#include <Wire.h>
 

void setup()
 {
   Wire.begin();
 
  Serial.begin(9600);
   Serial.println("\nI2C Scanner");
 }
 

void loop()
 {
   byte error, address;
   int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
   for(address = 0; address <= 254; address++ ) 
  {
     // The i2c_scanner uses the return value of
     // the Write.endTransmisstion to see if
     // a device did acknowledge to the address.
     Wire.beginTransmission(address);
     error = Wire.endTransmission();
 
    if (error == 0)
     {
       Serial.print("I2C device found at address 0x");
       if (address<16) 
        Serial.print("0");
       Serial.print(address,HEX);
       Serial.println(" !");
 
      nDevices++;
     }
     else if (error==4) 
    {
       Serial.print("Unknow error at address 0x");
       if (address<16) 
        Serial.print("0");
       Serial.println(address,HEX);
     }    
   }
   if (nDevices == 0)
     Serial.println("No I2C devices found\n");
   else
     Serial.println("done\n");
 
  delay(8000);           // wait 8 seconds for next scan
 }
