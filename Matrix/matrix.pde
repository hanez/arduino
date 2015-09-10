#include <TimerOne.h>
#include <MatrixFonts3x5.h>

#define COLS 5
#define ROWS 7
#define PINS 13

#define MATRIX1 { \
  {1,0,1,0,1,0,1}, \
  {0,1,0,1,0,1,0}, \
  {1,0,1,0,1,0,1}, \
  {0,1,0,1,0,1,0}, \
  {1,0,1,0,1,0,1} \
}

#define MATRIX2 { \
  {0,1,0,1,0,1,0}, \
  {1,0,1,0,1,0,1}, \
  {0,1,0,1,0,1,0}, \
  {1,0,1,0,1,0,1}, \
  {0,1,0,1,0,1,0} \
}

byte col = 0;
byte leds[COLS][ROWS];

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[PINS]= {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// col[xx] of leds = pin yy on led matrix
int cols[COLS] = {pins[1], pins[3], pins[10], pins[7], pins[8]};

// row[xx] of leds = pin yy on led matrix
int rows[ROWS] = {pins[12], pins[11], pins[2], pins[9], pins[4], pins[5], pins[6]};

const int numPatterns = 14;
byte patterns[numPatterns][COLS][ROWS] = {H,A,L,L,O,DASH,W,E,L,T,DOT,DOT,DOT,SPACE};

int pattern = 0;

void setup() {
  
  //Serial.begin(9600);
  
  // sets the pins as output
  for (int i = 0; i < PINS; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // set up cols
  for (int i = 1; i <= COLS; i++) {
    digitalWrite(cols[i - 1], 0);
  }
  //  and rows
  for (int i = 1; i <= ROWS; i++) {
    digitalWrite(rows[i - 1], 1);
  }
 
  blink();
  five2one();
  
  clearLeds();

  Timer1.initialize(2000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(display);  // attaches display() as a timer overflow interrupt
 
  setPattern(pattern);
}

void loop() {
 pattern = ++pattern % numPatterns;
 slidePattern(pattern, 180);
}
// Interrupt routine
void display() {
  digitalWrite(cols[col], 0);  // Turn whole previous column off
  col++;
  if (col == 5) {
    col = 0;
  }
  for (int row = 0; row < 7; row++) {
    if (leds[col][(ROWS - 1) - row] == 1) {
      digitalWrite(rows[row], 0);  // Turn on this led
    }
    else {
      digitalWrite(rows[row], 1); // Turn off this led
    }
   // delay(10);
  }
  digitalWrite(cols[col], 1); // Turn whole column on at once (for equal lighting times)

}

void slidePattern(int pattern, int del) {
  for (int l = 0; l < COLS; l++) {
    for (int i = 0; i < (COLS - 1); i++) {
      for (int j = 0; j < ROWS; j++) {
        leds[i][j] = leds[i + 1][j];
      }
    }
    for (int j = 0; j < ROWS; j++) {
      leds[4][j] = patterns[pattern][0 + l][j];
    }
    delay(del);
  }
}

void clearLeds() {
  // Clear display array
  for (int i = 0; i < COLS; i++) {
    for (int j = 0; j < ROWS; j++) {
      leds[i][j] = 0;
    }
  }
}
  
void setPattern(int pattern) {
  for (int i = 0; i < COLS; i++) {
    for (int j = 0; j < ROWS; j++) {
      leds[i][j] = patterns[pattern][i][j];
    }
  }
}

void blink() {
  for(int i = 0; i < 12; i++) {
    if(i % 2 != 0) {
      digitalWrite(cols[0], 1);
      digitalWrite(cols[1], 0);
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
    } else {
      digitalWrite(cols[0], 0);
      digitalWrite(cols[1], 0);
      digitalWrite(cols[2], 0);
      digitalWrite(cols[3], 0);
      digitalWrite(cols[4], 0);
      digitalWrite(rows[0], 1);
      digitalWrite(rows[1], 1);
      digitalWrite(rows[2], 1);
      digitalWrite(rows[3], 1);
      digitalWrite(rows[4], 1);
      digitalWrite(rows[5], 1);
      digitalWrite(rows[6], 1);
    }
    delay(100);
  }
}

void five2one() {
  digitalWrite(cols[0], 1);
  digitalWrite(cols[1], 0);
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
  delay(100);
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
  delay(100);
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
  delay(100);
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
  delay(100);
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
  delay(100);
}

