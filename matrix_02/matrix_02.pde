#include <TimerOne.h>

#define COLS 5
#define ROWS 7
#define PINS 13

#define SPACE { \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0} \
}

#define H { \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 1, 1, 1, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1} \
}

#define E { \
    {1, 1, 1, 1, 1}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 1, 1, 1, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 1, 1, 1, 1} \
}

#define L { \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 1, 1, 1, 1} \
}

byte col = 0;
byte leds[COLS][ROWS];

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[PINS]= {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// col[xx] of leds = pin yy on led matrix
int cols[COLS] = {pins[1], pins[3], pins[10], pins[7], pins[8]};

// row[xx] of leds = pin yy on led matrix
int rows[ROWS] = {pins[12], pins[11], pins[2], pins[9], pins[4], pins[5], pins[6]};


void setup() {
  
  Serial.begin(9600);

  for (int i = 0; i < PINS; i++) {
    pinMode(pins[i], OUTPUT);
  }
  for (int i = 1; i <= COLS; i++) {
    digitalWrite(cols[i - 1], 0);
  }
  for (int i = 1; i <= ROWS; i++) {
    digitalWrite(rows[i - 1], 1);
  }


  
  /*
  digitalWrite(cols[0], 0);
  digitalWrite(cols[1], 1);
  digitalWrite(cols[2], 0);
  digitalWrite(cols[3], 0);
  digitalWrite(cols[4], 0);
  digitalWrite(rows[0], 0);
  digitalWrite(rows[1], 1);
  digitalWrite(rows[2], 1);
  digitalWrite(rows[3], 1);
  digitalWrite(rows[4], 1);
  digitalWrite(rows[5], 1);
  digitalWrite(rows[6], 1);
  delay(2000);
  digitalWrite(cols[0], 0);
  digitalWrite(cols[1], 0);
  digitalWrite(cols[2], 1);
  digitalWrite(cols[3], 0);
  digitalWrite(cols[4], 0);
  digitalWrite(rows[0], 0);
  digitalWrite(rows[1], 1);
  digitalWrite(rows[2], 1);
  digitalWrite(rows[3], 1);
  digitalWrite(rows[4], 1);
  digitalWrite(rows[5], 1);
  digitalWrite(rows[6], 1);
  delay(2000);
  digitalWrite(cols[0], 0);
  digitalWrite(cols[1], 0);
  digitalWrite(cols[2], 0);
  digitalWrite(cols[3], 1);
  digitalWrite(cols[4], 0);
  digitalWrite(rows[0], 0);
  digitalWrite(rows[1], 1);
  digitalWrite(rows[2], 1);
  digitalWrite(rows[3], 1);
  digitalWrite(rows[4], 1);
  digitalWrite(rows[5], 1);
  digitalWrite(rows[6], 1);
  delay(2000);
  digitalWrite(cols[0], 0);
  digitalWrite(cols[1], 0);
  digitalWrite(cols[2], 0);
  digitalWrite(cols[3], 0);
  digitalWrite(cols[4], 1);
  digitalWrite(rows[0], 0);
  digitalWrite(rows[1], 1);
  digitalWrite(rows[2], 1);
  digitalWrite(rows[3], 1);
  digitalWrite(rows[4], 1);
  digitalWrite(rows[5], 1);
  digitalWrite(rows[6], 1);
  delay(2000);
  */
}

void loop() {
  Serial.println("Foo");
  
  digitalWrite(cols[0], 1);
  digitalWrite(cols[1], 1);
  digitalWrite(cols[2], 1);
  digitalWrite(cols[3], 1);
  digitalWrite(cols[4], 1);
  digitalWrite(rows[0], 0);
  digitalWrite(rows[1], 0);
  digitalWrite(rows[2], 0);
  digitalWrite(rows[3], 0);
  digitalWrite(rows[4], 0);
  digitalWrite(rows[5], 0);
  digitalWrite(rows[6], 0);
  delay(2000);
  digitalWrite(cols[0], 1);
  digitalWrite(cols[1], 0);
  digitalWrite(cols[2], 1);
  digitalWrite(cols[3], 0);
  digitalWrite(cols[4], 1);
  digitalWrite(rows[0], 1);
  digitalWrite(rows[1], 0);
  digitalWrite(rows[2], 1);
  digitalWrite(rows[3], 0);
  digitalWrite(rows[4], 1);
  digitalWrite(rows[5], 0);
  digitalWrite(rows[6], 1);
  delay(2000);

}
