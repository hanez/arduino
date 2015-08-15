#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

float tempRaw;
float tempC;
float tempF;
int   tempPin = 0;

void setup() {
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Temperature:");
}

void loop() {
  tempRaw = analogRead(tempPin);
  tempC = tempRaw/2;
  tempF = (tempC*9)/5 + 32;
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print("C / ");
  lcd.print(tempF);
  lcd.print("F");
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
