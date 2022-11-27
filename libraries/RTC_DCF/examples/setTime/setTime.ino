/******************************************************************************
Beispiel:      setTime

Beschreibung:  Dieses Beispiel zeigt das Schreiben und Lesen der Uhrzeit aus
               dem RTC-DCF.
               
Hinweis:       Zur Einstellung des Kommunikationswegs (UART, SPI oder I2C) zum
               RTC-DCF enthält die Library die Datei RTC_DCF_config.h im
               Unterordner \libraries\RTC_DCF\config\. Innerhalb dieser Datei
               kann der Kommunikationsweg umgestellt werden.
******************************************************************************/
#include <stdio.h>
#include "DateTime.h"
#include "RealTimeClock_DCF.h"

/* leider setzt die Arduino-IDE voraus, dass alle in einem Projekt verwendeten
   Klassen auch ins Sketch übernommen werden. Wird dieses nicht berücksichtigt,
   kommt es zu Fehlern beim Linken des Programms. Daher muss an dieser Stelle
   die Headerdatei zu der jeweils verwendeten Kommunikationsklasse eingefügt
   werden. Die beiden jeweils nicht verwendeten Header müssen auskommentiert
   werden. */

/* für die Kommunikation über UART die modSoftwareSerial.h verwenden */
//#include "modSoftwareSerial.h"

/* für die Kommunikation über SPI die SPI.h verwenden */
//#include "SPI.h"

/* für die Kommunikation über Wire die Wire.h verwenden */
#include "Wire.h"

/******************************************************************************
globale Variablen
******************************************************************************/
/* einzustellende Uhrzeit */
DateTime dateTime = DateTime(0, 1, 1, DateTime::SATURDAY, 0, 0, 0);

/******************************************************************************
Funktionen
******************************************************************************/
void setup()
{
  /* der RTC-DCF benötigt ca. 1,5 Sekunden bis er Daten empfangen kann */
  delay(1500); 
  
  /* RTC-DCF initialisieren */  
  RTC_DCF.begin();

  /* Uhrzeit im RTC-DCF setzen */
  RTC_DCF.setDateTime(&dateTime);

  /* die serielle Ausgabe initialisieren */
  Serial.begin(115200);  
}

void loop()
{
  /* ca. jede Sekunde wird die Uhrzeit ausgelesen und über die serielle Schnittstelle 
     ausgegeben. */
  delay(1000);
  
  RTC_DCF.getDateTime(&dateTime);
  
  printClock();
}

void printClock(void)
{
  char clockString[30];
  
  sprintf(clockString, "Es ist %02u:%02u:%02u am %02u.%02u.%02u", dateTime.getHour(), dateTime.getMinute(), dateTime.getSecond(), dateTime.getDay(), dateTime.getMonth(), dateTime.getYear());
  
  Serial.println(clockString);   
}
