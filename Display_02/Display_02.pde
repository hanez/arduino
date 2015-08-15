
#include <LiquidCrystal.h>

// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

#define OUTPIN 7
#define INPIN 8

void setup()
{
  
  pinMode(OUTPIN, OUTPUT);
  digitalWrite(OUTPIN, LOW);
  pinMode(INPIN, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  
  
  
  
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd.print("Hej Katrin...");    // change this text to whatever you like. keep it clean.
  lcd.setCursor(0,1);           // set cursor to column 0, row 1
  lcd.print("Jeg elsker dig!");
  
  // if you have a 4 row LCD, uncomment these lines to write to the bottom rows
  // and change the lcd.begin() statement above.
  //lcd.setCursor(0,2);         // set cursor to column 0, row 2
  //lcd.print("Row 3");
  //lcd.setCursor(0,3);         // set cursor to column 0, row 3
  //lcd.print("Row 4");
}

void loop()
{
   /*
   boolean val = digitalRead(INPIN);
  
   if(val == LOW) {
     digitalWrite(OUTPIN, LOW);
     digitalWrite(13, LOW);

   }
   
   if(val == HIGH) {
     for(int i = 15; i >= 0; i--) {
       lcd.clear();
       lcd.setCursor(i,1);
       lcd.print("<");
       delay(200);
     }
     for(int i = 0; i <= 15; i++) {
       lcd.clear();
       lcd.setCursor(i,0);
       lcd.print(">");
       delay(200);
       if(i == 15) {
         lcd.clear();
       }
       
     }
     digitalWrite(OUTPIN, HIGH);
     digitalWrite(13, HIGH);
    // delay(200);
   }
   */
   //
 ///}
 delay(333);

}
