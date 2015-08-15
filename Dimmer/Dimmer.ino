/*
 * Dimmer
 * by David A. Mellis
 *
 * Demonstrates the sending data from the computer to the Arduino board,
 * in this case to control the brightness of an LED.  The data is sent
 * in individual bytes, each of which ranges from 0 to 255.  Arduino
 * reads these bytes and uses them to set the brightness of the LED.
 *
 * http://www.arduino.cc/en/Tutorial/Dimmer
 */
 
int ledPin = 13;

void setup()
{
  // begin the serial communication
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  byte val;
  
  // check if data has been sent from the computer
  if (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255)
    val = Serial.read();
    // set the brightness of the LED
    analogWrite(ledPin, val);
    //Serial.write(255);
    Serial.write(val/2);
  }
  
}
