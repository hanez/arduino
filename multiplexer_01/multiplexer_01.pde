
#define OUTPUT0 13
#define OUTPUT1 12
#define OUTPUT2 11

void setup() {

  //Serial.begin(9600);
  

 pinMode(OUTPUT0, OUTPUT);
 pinMode(OUTPUT1, OUTPUT);
 pinMode(OUTPUT2, OUTPUT);


}

void loop() {
   digitalWrite(OUTPUT0, LOW);
   digitalWrite(OUTPUT1, LOW);
   digitalWrite(OUTPUT2, LOW);
   delay(100);
   digitalWrite(OUTPUT0, HIGH);
   digitalWrite(OUTPUT1, LOW);
   digitalWrite(OUTPUT2, LOW);
   delay(100);
   digitalWrite(OUTPUT0, LOW);
   digitalWrite(OUTPUT1, HIGH);
   digitalWrite(OUTPUT2, LOW);
   delay(100);
   digitalWrite(OUTPUT0, HIGH);
   digitalWrite(OUTPUT1, HIGH);
   digitalWrite(OUTPUT2, LOW);
   delay(100);
}
