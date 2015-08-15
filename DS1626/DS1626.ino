
//#include <LiquidCrystal.h>

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <SoftwareSerial.h>


#define rxPin      0
#define txPin      1
#define ledPin     13

#define rstPin     6
#define clkPin     7
#define dqPin      8

#define tempPin    0

// set up a new serial port
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
byte pinState = 0;

void setup()  {
  // define pin modes for tx, rx, led pins:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(rstPin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  pinMode(dqPin, OUTPUT);
  
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  
  //lcd.begin(16, 2);
  //lcd.print("Temperature:");
}


void loop() {
    float temp;

    rst_low();
    
    clk_high();
    rst_high(); //all data transfer are initiated by driving RST high
    write_command(0x0c); // write config command
    write_command(0x02); // cpu mode
    rst_low();
    delay(200); //wait until the configuration register is written 
    
    clk_high();
    rst_high();
    write_command(0x51); //start conversion
    rst_low();
    delay(200);
   
    clk_high();
    rst_high();
    write_command(0xAA);
    int raw_data = read_raw_data();
    rst_low();
    
    mySerial.print("temperature:");
    mySerial.print(raw_data/20);
    mySerial.println(" C");

    /*
    temp = analogRead(tempPin);
    //temp = temp * 0.48828125;
    temp = (5.0 * temp * 100.0)/1024.0;
    lcd.setCursor(0, 1);
    lcd.print(temp);
    //lcd.print(" ");
    //lcd.print("wsew");
    
    
    delay(1000);
 */
 delay(1000);

}

void write_command(int command)
/* sends 8 bit command on DQ output, least sig bit first */ 
{
  int n, bit;
  
  for(n=0;n<8;n++)
  {
    bit = ((command >> n) & (0x01));
    out_bit(bit);
  }
}

int read_raw_data(void)
{
  int bit,n;
  int raw_data=0;

  pinMode(dqPin,INPUT);
  
     /* jam the dq lead high to use as input */
  for(n=0;n<9;n++)
  {
     clk_low();
     bit=(digitalRead(dqPin));
     clk_high();
     raw_data = raw_data | (bit <<  n);
  }
  pinMode(dqPin, OUTPUT);
  return(raw_data);
}

void out_bit(int bit) 
{
  digitalWrite(dqPin, bit);  /* set up the data */
  clk_low();             /* and then provide a clock pulse */   
  clk_high();
}

void clk_high(void)
{
  digitalWrite(clkPin,HIGH);
}

void clk_low(void)
{
  digitalWrite(clkPin,LOW);
}

void rst_high(void)
{
   digitalWrite(rstPin,HIGH);
}

void rst_low(void)
{
   digitalWrite(rstPin,LOW);
}


