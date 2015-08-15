

#include <LCD4Bit.h> 

//create object to control an LCD.  
//number of lines in display=2
LCD4Bit lcd = LCD4Bit(2); 




void setup(void) {
  pinMode(13, OUTPUT);  //we'll use the debug LED to output a heartbeat
  lcd.init();
}

void loop() {  
  
  lcd.clear();                      // Clear display
  
  //lcd.printIn("fuck the world guys... ?");    // Dislay text on first line
  //lcd.leftScroll(32, 600);
 // lcd.cursorTo(2,0);                // Move cursor to second line, position 0

  //lcd.printIn("<<<<fuck off>>>>");  // Display text on second line


lcd.printIn("Hey guys...");
lcd.cursorTo(2,0);
delay(5000);
lcd.printIn("what's up?");
delay(5000);
lcd.cursorTo(1,0);
lcd.printIn("Hehehehehhe....");
lcd.cursorTo(2,0);
lcd.printIn(".................");
delay(10000);
//lcd.printIn("");
//lcd.printIn("");

delay(5000);
/*
  while(1)                          // Endless loop flashing the LED
  {
    digitalWrite(13, HIGH);  
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }
  */
}
