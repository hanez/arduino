#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int   samples[30];
float tempC;
float tempClast = 0;
float tempF;
int   tempPin = 0;

void setup() {
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Temperature:");
}

void loop() {
  int i;
  tempC = 0;
  for(i = 0; i <= 29; i++) {
    samples[i] = (5.0 * analogRead(tempPin) * 100.0) / 1024.0;
    tempC = tempC + samples[i];
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }
  tempC = tempC / 30.0;
  tempF = (tempC*9) / 5 + 32;
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print("C/");
  lcd.print(tempF);
  lcd.print("F  ");
  if(tempClast > tempC) {
    lcd.print("-");
  } else if(tempClast < tempC) {
    lcd.print("+");
  } else {
    lcd.print("*");
  }
  tempClast = tempC;
}
