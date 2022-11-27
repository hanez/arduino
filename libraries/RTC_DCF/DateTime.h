#ifndef DateTime_h
#define DateTime_h

/**********************************************************
Klasse DateTime
**********************************************************/
class DateTime
{
private:
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char weekday;
	unsigned char day;
	unsigned char month;
	unsigned char year;

public:
	enum weekday {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};

	DateTime();

	DateTime(	unsigned char year, unsigned char month, unsigned char day, unsigned char weekday,
				unsigned char hour, unsigned char minute, unsigned char second);

	
  // Schreiben bzw. Lesen der Sekunde
  unsigned char getSecond(void)		          { return second; }
	void setSecond(unsigned char value)	      { second = value; }

  // Schreiben bzw. Lesen der Minute
	unsigned char getMinute(void)	            { return minute; }
	void setMinute(unsigned char value)       { minute = value; }

  // Schreiben bzw. Lesen der Stunde
	unsigned char getHour(void)					      { return hour; }
	void setHour(unsigned char value)			    { hour = value; }

  // Schreiben bzw. Lesen des Wochentags
	unsigned char getWeekday(void)				    { return weekday; }
	void setWeekday(unsigned char value)		  { weekday = value; }

  // Schreiben bzw. Lesen des Tags
	unsigned char getDay(void)					      { return day; }
	void setDay(unsigned char value)			    { day = value; }

  // Schreiben bzw. Lesen des Monats
	unsigned char getMonth(void)				      { return month; }
	void setMonth(unsigned char value)			  { month = value; }

  // Schreiben bzw. Lesen des Jahres
	unsigned char getYear(void)					      { return year; }
	void setYear(unsigned char value)			    { year = value; }

  // Weiterzählen der Sekunden
	void addSecond(void);

  // Anzahl Tage im Monat
	unsigned char daysInMonth(unsigned char month, unsigned char year);

  // Kontrolle, ob Schaltjahr
	unsigned char isLeapyear(unsigned char year);

  // Datum und/oder Uhrzeit als Zeichenkette
	void getDateTimeString(char* dateTimeString);
	void getDateString(char* dateString);
	void getTimeString(char* timeString);
};

#endif