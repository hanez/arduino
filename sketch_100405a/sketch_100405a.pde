//164 pins
int clearPin = 2; // enablepin
int dataPin = 3;
int clockPin = 4;

//165 pins
int inclearPin = 11; // enablepin
int indataPin = 9;
int inclockPin = 10;
int inloadPin = 12; // toggling this tells the 165 to read the value into its memory for reading

int temp = 0;

void setup() {

  //start serial
  Serial.begin(9600);

  //164
  pinMode(clearPin, OUTPUT);
  digitalWrite(clearPin, 1); // enable output, you could also tie this pin to VCC
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  //165
  pinMode(inclearPin, OUTPUT);
  digitalWrite(inclearPin, 0); // enable input, you could also tie this pin to GND
  pinMode(indataPin, INPUT);
  pinMode(inclockPin, OUTPUT);
  pinMode(inloadPin, OUTPUT);


  //we want to set the 164's outputs to any combination of 1's and 0's we want
  //going to set the 164 outputs to 11101101 or on,on,on,off,on,on,off,on if you prefer, where on is 5v and off is grnd
  //1st bit
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, 1);
  digitalWrite(clockPin, 1);
  //2nd bit
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, 1);
  digitalWrite(clockPin, 1);
  //3rd bit
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, 1);
  digitalWrite(clockPin, 1);
  //4th bit
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  //5th bit
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, 1);
  digitalWrite(clockPin, 1);
  //6th bit
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, 1);
  digitalWrite(clockPin, 1);
  //7th bit
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  //8th bit
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, 1);
  digitalWrite(clockPin, 1);

}

// now its time to read the values that we outputted back in

void loop() {

  digitalWrite(inloadPin, 0); // read into register (tells the 165 to take a snapshot of its input pins)
  digitalWrite(inloadPin, 1); // done reading into register, ready for us to read

  for(int i=0; i<=7; i++){ // read each of the 165's 8 inputs (or its snapshot of it rather)

  // tell the 165 to send the inputs pin state
  digitalWrite(inclockPin, 0);
  // read the current output
  temp = digitalRead(indataPin); // read the state
  // tell the 165 we are done reading
  digitalWrite(inclockPin, 1);

  Serial.print (temp);

  }

  Serial.println ("");
  Serial.println ("--------");

  delay(2000);

}
