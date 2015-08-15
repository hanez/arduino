//3led fnordlicht//

int value = 0;
int bluepin = 9;
int greenpin = 10;
int redpin = 11;

void setup()
{
pinMode(bluepin, OUTPUT);
pinMode(greenpin, OUTPUT);
pinMode(redpin,OUTPUT);

//led test start
digitalWrite(bluepin, HIGH);
delay(200);
digitalWrite(bluepin, LOW);
digitalWrite(greenpin, HIGH);
delay(200);
digitalWrite(greenpin, LOW);
digitalWrite(redpin, HIGH);
delay(200);
digitalWrite(redpin, LOW);

digitalWrite(bluepin, HIGH);
delay(200);
digitalWrite(bluepin, LOW);
digitalWrite(greenpin, HIGH);
delay(200);
digitalWrite(greenpin, LOW);
digitalWrite(redpin, HIGH);
delay(200);
digitalWrite(redpin, LOW);

digitalWrite(bluepin, HIGH);
delay(200);
digitalWrite(bluepin, LOW);
digitalWrite(greenpin, HIGH);
delay(200);
digitalWrite(greenpin, LOW);
digitalWrite(redpin, HIGH);
delay(200);
digitalWrite(redpin, LOW);
delay(5000);
}

void loop()
{
digitalWrite(bluepin, 255+value);
for(value = 4 ; value <= 255; value+=1)
{
analogWrite(redpin, value);
analogWrite(greenpin, value);
delay(50);
}
for(value = 255; value >=4; value-=1)
{
analogWrite(bluepin, value);
analogWrite(greenpin, value);
delay(50);
}
//fading 2
for(value = 4 ; value <= 255; value+=1)
{
analogWrite(bluepin, value);
analogWrite(greenpin, value);
delay(50);
}
for(value = 255; value >=4; value-=1)
{
analogWrite(bluepin, value);
analogWrite(redpin, value);
delay(50);
}
//fading 3
for(value = 4 ; value <= 255; value+=1)
{
analogWrite(redpin, value);
analogWrite(bluepin, value);
delay(50);
}
for(value = 255; value >=4; value-=1)
{
analogWrite(redpin, value);
analogWrite(greenpin, value);
delay(50);
}
}
