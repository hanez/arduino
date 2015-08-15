/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 
 */
int brightness1 = 0;    // how bright the LED is
int brightness2 = 85;    // how bright the LED is
int brightness3 = 170;    // how bright the LED is
int fadeAmount1 = 5;    // how many points to fade the LED by
int fadeAmount2 = 5;    // how many points to fade the LED by
int fadeAmount3 = 5;    // how many points to fade the LED by

void setup()  { 
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
} 

void loop()  { 
  analogWrite(9, brightness1);    
  analogWrite(10, brightness2);
  analogWrite(11, brightness3);

  brightness1 = brightness1 + fadeAmount1;
  brightness2 = brightness2 + fadeAmount2;
  brightness3 = brightness3 + fadeAmount3;

  if (brightness1 == 0 || brightness1 == 255) {
    fadeAmount1 = -fadeAmount1 ; 
  }  
  if (brightness2 == 0 || brightness2 == 255) {
    fadeAmount2 = -fadeAmount2 ; 
  }  
  if (brightness3 == 0 || brightness3 == 255) {
    fadeAmount3 = -fadeAmount3 ; 
  }    

  delay(250);                            
}
