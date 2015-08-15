#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float temp;
int tempPin = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Temperature:");
}

void loop() {
  temp = analogRead(tempPin);
  temp = temp * 0.48828125;
  //temp = (5.0 * temp * 100.0)/1024.0;
  lcd.setCursor(0, 1);
  lcd.print(temp);
  delay(1000); 
}

