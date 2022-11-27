/******************************************************************************
Beispiel:      alarmInterrupt

Beschreibung:  Dieses Beispiel zeigt die Verwendung des Alarms innerhalb des
               RTC-DCF.
               
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
//#include "modSoftwareSerial.h"

/* für die Kommunikation über SPI die SPI.h verwenden */
//#include "SPI.h"

/* für die Kommunikation über Wire die Wire.h verwenden */
#include "Wire.h"

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
/* einzustellende Uhrzeit */
DateTime dateTime = DateTime(0, 1, 1, DateTime::SATURDAY, 0, 59, 55);

/* Flag zur Anzeige eines Alarms */
volatile uint8_t alarmFlag = 0;

/******************************************************************************
Funktionen
******************************************************************************/
void setup()
{
  /* der RTC-DCF benötigt ca. 1,5 Sekunden bis er Daten empfangen kann */
  delay(1500);
  
  /* den Pin für den Alarm-Interrupt als Eingang und als externe
     Interrupt-Quelle definieren */
  pinMode(RTC_DCF_ALARM_INT_PIN, INPUT);
  PCintPort::attachInterrupt(RTC_DCF_ALARM_INT_PIN, &alarmInterrupt, FALLING);
  
  /* RTC-DCF initialisieren */  
  RTC_DCF.begin();

  /* Uhrzeit im RTC-DCF setzen */
  RTC_DCF.setDateTime(&dateTime);
  
  /* den Alarm auf 1:00 Uhr (5 Sekunden nach der eingestellten Uhrzeit) setzen */
  RTC_DCF.setAlarmTime(RTC_ALARM_WEEKDAYS_ALL, 1, 0);
  
  /* den Alarm-Interrupt des RTC-DCF aktivieren */
  RTC_DCF.enableAlarmInterrupt();

  /* die serielle Ausgabe initialisieren */
  Serial.begin(115200);
  
  /* Interrupts einschalten */
  interrupts();
}

void loop()
{
  /* "ALARM" über die serielle Schnittstelle ausgeben und den Alarm-Interrupt
     des RTC-DCF zurücksetzen, wenn das Alarm-Flag gesetzt wird  */
  if(alarmFlag == 1)
  {
    Serial.println("ALARM");
    
    RTC_DCF.resetAlarmInterrupt();
    
    alarmFlag = 0;
  }
}

void alarmInterrupt(void)
{
  alarmFlag = 1;
}
