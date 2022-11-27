/******************************************************************************
Beispiel:      periodicInterrupt

Beschreibung:  Dieses Beispiel zeigt die Verwendung des periodischen Interrupts
               innerhalb des RTC-DCF.
               
Hinweis:       Zur Einstellung des Kommunikationswegs (UART, SPI oder I2C) zum
               RTC-DCF enthält die Library die Datei RTC_DCF_config.h im
               Unterordner \libraries\RTC_DCF\config\. Innerhalb dieser Datei
               kann der Kommunikationsweg umgestellt werden.
               
               Bei Verwendung der UART-Schnittstelle wird ein Objekt der Klasse
               modSoftSerial angelegt. Diese Klasse entspricht einer 
               modifizierten SoftSerial-Klasse. Innerhalb der modifizierten
               Klasse wird nur der PinChange-Interrupt für den Port D (PCINT2_vect)
               angelegt, anstatt alle PinChange-Interrupts anzulegen. Ohne diese
               Modifizierung wäre eine Verwendung von SoftSerial und PinChangeInt
               nicht parallel möglich.
               
               Die modifizierte SoftSerial-Klasse ist Teil der RTC-DCF-Library.
               
               Die PinChangeInt-Klasse ist nicht Teil der RTC-DCF-Library, kann
               aber auf folgender Internetseite heruntergeladen werden:
               http://arduino.cc/playground/Main/PinChangeInt
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
#include "modSoftwareSerial.h"

/* für die Kommunikation über SPI die SPI.h verwenden */
//#include "SPI.h"

/* für die Kommunikation über Wire die Wire.h verwenden */
//#include "Wire.h"

/******************************************************************************
Definitionen
******************************************************************************/
/* für die Kommunikation über UART wird ein Objekt der Klasse modSoftwareSerial 
   benötigt. Da diese Klasse den Pin Change Interrupt am Port D blockiert, muss
   dieser für die Klasse PinChangeInt deaktiviert werden. */
#if RTC_DCF_COMMUNICATION == 0x00
  #define NO_PORTD_PINCHANGES
#endif

#include "PinChangeInt.h"

/******************************************************************************
globale Variablen
******************************************************************************/
/* aktuelle Uhrzeit */
DateTime dateTime;

/* Flag zur Anzeige eines periodischen Interrupts */
volatile uint8_t periodicInterruptFlag = 0; 

/******************************************************************************
Funktionen
******************************************************************************/

void setup()
{
  /* der RTC-DCF benötigt ca. 1,5 Sekunden bis er Daten empfangen kann */
  delay(1500);  
  
  /* den Pin für den periodischen Interrupt als Eingang und als externe
     Interrupt-Quelle definieren */
  pinMode(RTC_DCF_PER_INT_PIN, INPUT);
  PCintPort::attachInterrupt(RTC_DCF_PER_INT_PIN, &periodicInterrupt, FALLING);
  
  /* RTC-DCF initialisieren */  
  RTC_DCF.begin();

  /* den periodischen Interrupt auf 1 Hz einstellen */
  RTC_DCF.setPeriodicInterruptMode(RTC_PERIODIC_INT_PULSE_1_HZ);
  
  /* den periodischen Interrupt des RTC-DCF aktivieren */
  RTC_DCF.enablePeriodicInterrupt();
  
  /* die serielle Ausgabe initialisieren */
  Serial.begin(115200);

  /* Interrupts einschalten */  
  interrupts();
}

void loop()
{
  /* wenn das Flag für den periodischen Interrupt gesetzt wird die Uhrzeit aus dem
     RTC-DCF auslesen und über die serielle Schnittstelle */  
  if(periodicInterruptFlag == 1)
  {
    RTC_DCF.getDateTime(&dateTime);
    
    printClock();
 
    periodicInterruptFlag = 0;
  }
}

void periodicInterrupt(void)
{
  periodicInterruptFlag = 1;
}

void printClock(void)
{
  char clockString[30];
  
  sprintf(clockString, "Es ist %02u:%02u:%02u am %02u.%02u.%02u", dateTime.getHour(), dateTime.getMinute(), dateTime.getSecond(), dateTime.getDay(), dateTime.getMonth(), dateTime.getYear());
  
  Serial.println(clockString);   
}