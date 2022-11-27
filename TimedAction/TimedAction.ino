#include <TimedAction.h>
 
TimedAction timedAction = TimedAction(1000,blink1);

boolean ledState1 = false;
 
 
void setup(){
  pinMode(13,OUTPUT);
  digitalWrite(13,ledState1);
}
 
void loop(){
  timedAction.check();
}
 
void blink1(){
  ledState1 ? ledState1=false : ledState1=true;
  digitalWrite(13,ledState1);
}
void blink2(){
  ledState2 ? ledState2=false : ledState2=true;
  digitalWrite(12,ledState2);
}
