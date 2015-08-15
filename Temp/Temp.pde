

#include <Wire.h>

#define BUTTON1  2
#define BUTTON2  3

// ds1621 has 0x9(b1001) A0 A1 A2
#define DS1621_ADDR ((0x9 << 3) | 0x00)

// start up ds1621
void ds1621_init()
{
  
  Serial.print(DS1621_ADDR, HEX);
  // write 0x2 to config register 0xac
  Wire.beginTransmission(DS1621_ADDR);
  Wire.send(0xac);
  Wire.send(0x02);
  Wire.endTransmission();
  delay(20);

  // tell the ds1621 to start measuring temperature
  Wire.beginTransmission(DS1621_ADDR);
  Wire.send(0xEE);
  Wire.endTransmission();   
}

// read temperature
unsigned int ds161_read_temp()
{
  unsigned int data;

  // tell ds1621 that we want to read register 0xaa (the temperature is in there)
  Wire.beginTransmission(DS1621_ADDR);
  Wire.send(0xaa);
  Wire.endTransmission();

  // start reading the 2 bytes of temp data  
  Wire.beginTransmission(DS1621_ADDR);
  Wire.requestFrom(DS1621_ADDR, 2);
  if(Wire.available())
    data = Wire.receive() << 8;
  if(Wire.available())
    data |= Wire.receive();
  return data;
}

// format and output the temperature read from a ds1621
void ds1621_print_temp(int temp)
{
   if(temp & 0x8000)
    Serial.print("-");
  else
    Serial.print("");
  temp &= 0x7fff;
  Serial.print(temp >> 8);
  if(temp & 0xff)
     Serial.print(",5");
  else
    Serial.print(",0");
  Serial.print("\n");
  delay(1000); 
}
int a = 0;
// this function is called everytime button1 is pressed
void button1_isr(void)
{
//  Serial.print("button1\n"); 
  a= 1;
}

// this function is called everytime button2 is pressed
void button2_isr(void)
{
  //Serial.print("button2\n"); 
  a=2;
}

void setup()
{

  pinMode(13, OUTPUT);  //we'll use the debug LED to output a heartbeat

  // start serial
  Serial.begin(9600);

  // start i2c
  Wire.begin();
  
  // start thermometer
  ds1621_init();   
  
  // setup button gpio 
  // gpio is input and internal pullup enabled
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  digitalWrite(BUTTON1, HIGH);
  digitalWrite(BUTTON2, HIGH);

  // give both buttons an interrupt handler
  attachInterrupt(0, button1_isr, FALLING);
  attachInterrupt(1, button2_isr, FALLING);
  interrupts();
}

void loop()
{

  int temp = ds161_read_temp();
  ds1621_print_temp(temp);
  delay(1000);
}
