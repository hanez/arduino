


int buttonState = 0;

void setup() {

  Serial.begin(9600);

  
  pinMode(7, INPUT);
  pinMode(13, OUTPUT); 
}

void loop() {
  

  
  buttonState = digitalRead(7);

  if (buttonState == HIGH) {         
    digitalWrite(13, HIGH);  
  } 
  else {
    digitalWrite(13, LOW); 
  }
  Serial.println(buttonState, DEC);
  delay(1000);              // wait for a second
}
