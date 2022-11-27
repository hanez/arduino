#include "DateTime.h"

/**********************************************************
Konstruktor
**********************************************************/
DateTime::DateTime()
{}


/*---------------------------------------------------------
Name:           DateTime

Beschreibung:   Konstruktor mit Übergabe der Datum und Uhrzeit            
 
Eingänge:       unsigned char year
                   Jahr

                unsigned char month
                   Monat

                unsigned char day
                   Tag

                unsigned char weekday
                   Wochentag (0: Sonntag, 1: Montag ...)

                unsigned char hour
                   Stunde

                unsigned char minute
                   Minute

                unsigned char second
                   Sekunde

Ausgang:        void
---------------------------------------------------------*/
DateTime::DateTime(	unsigned char year, unsigned char month, unsigned char day, unsigned char weekday,
					unsigned char hour, unsigned char minute, unsigned char second)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->weekday = weekday;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

/**********************************************************
öffentliche Methoden
**********************************************************/

/*---------------------------------------------------------
Name:           addSecond

Beschreibung:   addiert eine Sekunde auf die aktuell
                gespeicherte Zeit inkl. Auswertung aller
                Überträge
 
Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void DateTime::addSecond(void)
{
	this->second++;

	if(this->second >= 60)
	{
		this->second = 0;
		this->minute++;

		if(this->minute >= 60)
		{
			this->minute = 0;
			this->hour++;

			if(this->hour >= 24)
			{
				this->hour = 0;
				this->day++;

				this->weekday = (this->weekday + 1) % 7;

				if(this->day >= daysInMonth(month, year))
				{
					this->day = 1;
					this->month++;

					if(this->month > 12)
					{
						this->month = 1;
						this->year++;
					}
				}
			}
		}
	}
}

/*---------------------------------------------------------
Name:           daysInMonth

Beschreibung:   gibt die Anzahl der Tages eines Monats zurück
 
Eingänge:       unsigned char month
                  Monat für den die Anzahl der Tage gesucht wird

                unsigned char year
                  Jahr in dem sich der Monat befindet
                  (wird bei der Entscheidung benötigt, ob
                  der Februar 28 oder 29 Tage hat)

Ausgang:        unsigned char
                  Anzahl der Monatstage
---------------------------------------------------------*/
unsigned char DateTime::daysInMonth(unsigned char month, unsigned char year)
{
	unsigned char days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	unsigned char daysInMonth = days[month];

	if(month == 2 && isLeapyear(year))
	{
		daysInMonth = 29;
	}	

	return daysInMonth;
}

/*---------------------------------------------------------
Name:           isLeapyear

Beschreibung:   gibt zurück ob das übergebene Jahr ein Schaltjahr ist
                
                Hinweis:
                Bei der Auswertung wird nur kontrolliert, ob das Jahr
                durch 4 teilbar ist. 
 
Eingänge:       unsigned char year
                  Jahr, das auf Schaltjahr geprüft werden soll
                  (Angabe als 2stelliger Wert)

Ausgang:        unsigned char
                  Jahr ist ein Schaltjahr?

                  0: kein Schaltjahr
                  1: Schaltjahr
---------------------------------------------------------*/
unsigned char DateTime::isLeapyear(unsigned char year)
{
	unsigned char leapyear = 0;

	if(year & 0x03 == 0)
	{
		leapyear = 1;
	}

	return leapyear;
}

/*---------------------------------------------------------
Name:           getDateTimeString

Beschreibung:   gibt die gespeicherte Zeit als Zeichenkette
                zurück
 
Eingänge:       char* dateTimeString
                  enthält am Ende der Funktion die gespeicherte
                  Zeit (Datum und Uhrzeit)

                  Mindestgröße: 18 Byte

                  Ausgabeformat: dd.MM.yy-hh:mm:ss

Ausgang:        void
---------------------------------------------------------*/
void DateTime::getDateTimeString(char* dateTimeString)
{
	getDateString(dateTimeString);

	dateTimeString[8] = '-';

	getTimeString(dateTimeString + 9);
}

/*---------------------------------------------------------
Name:           getDateString

Beschreibung:   gibt das gespeicherte Datum als Zeichenkette
                zurück
 
Eingänge:       char* dateString
                  enthält am Ende der Funktion das gespeicherte
                  Datum

                  Mindestgröße: 9 Byte

                  Ausgabeformat: dd.MM.yy

Ausgang:        void
---------------------------------------------------------*/
void DateTime::getDateString(char* dateString)
{
	dateString[0] = (this->day / 10) + '0';	
	dateString[1] = (this->day % 10) + '0';
	dateString[2] = '.';
	dateString[3] = (this->month / 10) + '0';	
	dateString[4] = (this->month % 10) + '0';
	dateString[5] = '.';
	dateString[6] = (this->year / 10) + '0';	
	dateString[7] = (this->year % 10) + '0';
	dateString[8] = '\n';
}

/*---------------------------------------------------------
Name:           getTimeString

Beschreibung:   gibt die gespeicherte Uhrzeit als Zeichenkette
                zurück
 
Eingänge:       char* timeString
                  enthält am Ende der Funktion die gespeicherte
                  Uhrzeit

                  Mindestgröße: 9 Byte

                  Ausgabeformat: hh:mm:ss

Ausgang:        void
---------------------------------------------------------*/
void DateTime::getTimeString(char* timeString)
{
	timeString[0] = (this->hour / 10) + '0';	
	timeString[1] = (this->hour % 10) + '0';
	timeString[2] = ':';
	timeString[3] = (this->minute / 10) + '0';	
	timeString[4] = (this->minute % 10) + '0';
	timeString[5] = ':';
	timeString[6] = (this->second / 10) + '0';	
	timeString[7] = (this->second % 10) + '0';
	timeString[8] = '\n';
}
