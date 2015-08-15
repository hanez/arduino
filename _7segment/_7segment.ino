/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  Serial.begin(9600); 
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);    
  pinMode(12, OUTPUT);    
  pinMode(11, OUTPUT);    
  pinMode(10, OUTPUT);    
  pinMode(9, OUTPUT);    
  pinMode(8, OUTPUT);    
  pinMode(7, OUTPUT);    
  pinMode(6, OUTPUT);     
}

void loop() {
  digitalWrite(13, LOW);   // set the LED on
  digitalWrite(12, HIGH);   // set the LED on
  digitalWrite(11, LOW);   // set the LED on
  digitalWrite(10, HIGH);   // set the LED on
  digitalWrite(9, LOW);   // set the LED on
  digitalWrite(8, LOW);   // set the LED on
  digitalWrite(7, LOW);   // set the LED on
  digitalWrite(6, LOW);   // set the LED on
  

}
