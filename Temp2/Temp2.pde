#include <Wire.h>

// ds1621 has 0x9(b1001) A0 A1 A2
//#define DS1621_ADDR 72
#define DS1621_ADDR ((0x9 << 3) | 0x00)

void setup()
{
  // start serial
  Serial.begin(9600);

  // write 0x2 to config register 0xac
  Wire.begin(DS1621_ADDR);
  Wire.send(0xac);
  Wire.send(0x02);
  
  delay(20);
  
  // tell the ds1621 to start measuring temperature
  Wire.send(0xee);
  
  // tell ds1621 that we want to read register 
  // 0xaa (the temperature is in there)
  Wire.send(0xaa);
}

void loop()
{
  unsigned int data;
  
  // start reading the 2 bytes of temp data  
  Wire.requestFrom(DS1621_ADDR, 2);
  
  if(Wire.available())
    data  = Wire.receive() << 8;
  if(Wire.available())
    data |= Wire.receive();

  Serial.print(data >> 8);
  
  if(data & 0xff)
    Serial.print(",5");
  else
    Serial.print(",0");

  Serial.println("");
  delay(1000);
}
