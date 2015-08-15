void alle(int CMD)
{
  for(int i=0;i<8;i++) {
    digitalWrite(i, CMD);
  }
}

void setup()
{
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop()
{
  alle(HIGH);
  delay(500);
  alle(LOW); 
  delay(500);
  /*
  digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(0, LOW); 
  delay(500);
  
  digitalWrite(1, HIGH);
  delay(500);
  digitalWrite(1, LOW); 
  delay(500);
  
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW); 
  delay(500);
  
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW); 
  delay(500);
  
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW); 
  delay(500);
  
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW); 
  delay(500);
  
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, LOW); 
  delay(500);
  
  digitalWrite(7, HIGH);
  delay(500);
  digitalWrite(7, LOW); 
  delay(500); */
}
