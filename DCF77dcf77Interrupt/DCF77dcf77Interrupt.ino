#include <stdio.h>
#include "DateTime.h"
#include "RealTimeClock_DCF.h"
#include "Wire.h"
#include "PinChangeInt.h"

DateTime readDateTime;
volatile uint8_t perInterruptFlag = 0; 
volatile uint8_t dcf77InterruptFlag = 0;

void setup()
{

  delay(1500);  
  pinMode(RTC_DCF_PER_INT_PIN, INPUT);
  PCintPort::attachInterrupt(RTC_DCF_PER_INT_PIN, &periodicInterrupt, FALLING);
  pinMode(RTC_DCF_DCF77_INT_PIN, INPUT);
  PCintPort::attachInterrupt(RTC_DCF_DCF77_INT_PIN, &dcf77Interrupt, FALLING);
  RTC_DCF.begin();
  RTC_DCF.enableDCF77Reception();
  RTC_DCF.enableDCF77Interrupt();
  RTC_DCF.setPeriodicInterruptMode(RTC_PERIODIC_INT_PULSE_1_HZ);
  RTC_DCF.enablePeriodicInterrupt();
  Serial.begin(115200);
  interrupts(); 
}

void loop()
{
  if(perInterruptFlag == 1)
  {
    RTC_DCF.getDateTime(&readDateTime);
    printClock();
    perInterruptFlag = 0;
  }
  
  if(dcf77InterruptFlag == 1)
  {
    Serial.println("DCF77 empfangen");
    RTC_DCF.resetDCF77Interrupt();
    dcf77InterruptFlag = 0;
  }
}

void periodicInterrupt(void)
{
  perInterruptFlag = 1;
}

void dcf77Interrupt(void)
{
  dcf77InterruptFlag = 1;
}

void printClock(void)
{
  char clockString[30];
  sprintf(clockString, "Es ist %02u:%02u:%02u am %02u.%02u.%02u", readDateTime.getHour(), readDateTime.getMinute(), readDateTime.getSecond(), readDateTime.getDay(), readDateTime.getMonth(), readDateTime.getYear());
  Serial.println(clockString);   
}
