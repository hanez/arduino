#include <stdio.h>
#include "DateTime.h"
#include "RealTimeClock_DCF.h"
#include "Wire.h"

DateTime dateTime;

void setup() {
  delay(1500);
  RTC_DCF.begin();
  RTC_DCF.enableDCF77Reception();
  RTC_DCF.getDateTime(&dateTime);
  Serial.begin(115200);
  printClock();
}

void loop() {
  delay(1000);
  RTC_DCF.getDateTime(&dateTime);
  printClock();
}

void printClock(void) {
  char clockString[30];
  sprintf(clockString, "Es ist %02u:%02u:%02u am %02u.%02u.%02u", dateTime.getHour(), dateTime.getMinute(), dateTime.getSecond(), dateTime.getDay(), dateTime.getMonth(), dateTime.getYear());
  Serial.println(clockString);
}
