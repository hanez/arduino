#ifndef RealTimeClock_DCF_h
#define RealTimeClock_DCF_h

#include <Arduino.h>
#include "DateTime.h"
#include "config/RTC_DCF_config.h"

#if RTC_DCF_COMMUNICATION == 0x00
#include "../modSoftSerial/modSoftwareSerial.h"
#define RTC_DCF_ALARM_INT_PIN         11
#define RTC_DCF_PER_INT_PIN           12
#define RTC_DCF_DCF77_INT_PIN         10
#endif

#if RTC_DCF_COMMUNICATION == 0x01
#include "../SPI/SPI.h"
#define RTC_DCF_ALARM_INT_PIN         2
#define RTC_DCF_PER_INT_PIN           18
#define RTC_DCF_DCF77_INT_PIN         19
#endif

#if RTC_DCF_COMMUNICATION == 0x02
#include "../Wire/Wire.h"
#define RTC_DCF_ALARM_INT_PIN         11
#define RTC_DCF_PER_INT_PIN           12
#define RTC_DCF_DCF77_INT_PIN         10
#endif

#define SPI_SLAVE_SELECT_PIN          10

typedef enum
{
  SPI_BURST_WRITE   = 0x00,
  SPI_SINGLE_WRITE  = 0x80,
  SPI_BURST_READ    = 0x40,
  SPI_SINGLE_READ   = 0xc0
} SPITransferFormat_t;

typedef enum
{
  RTC_DCF_REG_SECOND   = 0x20,
  RTC_DCF_REG_MINUTE,
  RTC_DCF_REG_HOUR,
  RTC_DCF_REG_WEEKDAY,
  RTC_DCF_REG_DAY,
  RTC_DCF_REG_MONTH,
  RTC_DCF_REG_YEAR,
  RTC_DCF_REG_ALARM_MINUTE,
  RTC_DCF_REG_ALARM_HOUR,
  RTC_DCF_REG_ALARM_WEEKDAY,
  RTC_DCF_REG_PERIODIC_INTERRUPT,
  RTC_DCF_REG_ALARM_CONFIG,
  RTC_DCF_REG_PER_INT_CONFIG,
  RTC_DCF_REG_DCF77_CONFIG,
  RTC_DCF_REG_STATUS,
  RTC_DCF_REG_RESERVED
} RTCRegister_t;

typedef enum
{
  RTC_PERIODIC_INT_PULSE_1_HZ         = 0x00,
  RTC_PERIODIC_INT_PULSE_2_HZ         = 0x01,
  RTC_PERIODIC_INT_LEVEL_EVERY_SECOND = 0x02,
  RTC_PERIODIC_INT_LEVEL_EVERY_MINUTE = 0x03,
  RTC_PERIODIC_INT_LEVEL_EVERY_HOUR   = 0x04,
  RTC_PERIODIC_INT_LEVEL_EVERY_DAY    = 0x05,
  RTC_PERIODIC_INT_LEVEL_EVERY_MONTH  = 0x06
} RTCPeriodicInterruptMode_t;

typedef enum
{
  RTC_ALARM_CONFIG_REGISTER_AIE         = 0x02,   // Alarm-Interrupt Enable
  RTC_ALARM_CONFIG_REGISTER_AILED       = 0x04    // LED-Signalisation at Alarm-Interrupt Enable
} RTCAlarmConfigRegisterBits_t;

typedef enum
{
  RTC_PER_INT_CONFIG_REGISTER_PIE       = 0x02,   // Periodic-Interrupt Enable
  RTC_PER_INT_CONFIG_REGISTER_PILED     = 0x04    // LED-Signalisation at Periodic-Interrupt Enable
} RTCPeriodicInterruptConfigRegisterBits_t;

typedef enum
{
  RTC_DCF77_CONFIG_REGISTER_DCFE        = 0x01,   // DCF77 Enable
  RTC_DCF77_CONFIG_REGISTER_DCFIE       = 0x02,   // DCF77-Interrupt Enable
  RTC_DCF77_CONFIG_REGISTER_DCFLED      = 0x04    // LED-Signalisation at DCF77-Interrupt Enable
} RTCDCF77ConfigRegisterBits_t;

typedef enum
{
  RTC_STATUS_DCFIF      = 0x01,   // DCF77-Interrupt Flag
  RTC_STATUS_PIF        = 0x02,   // Periodic-Interrupt Flag
  RTC_STATUS_AIF        = 0x04    // Alarm-Interrupt Flag
} RTCStatusRegisterBits_t;

typedef enum
{
  RTC_ALARM_WEEKDAYS_NONE           = 0x00,
  RTC_ALARM_WEEKDAYS_MON            = 0x01,
  RTC_ALARM_WEEKDAYS_TUE            = 0x02,
  RTC_ALARM_WEEKDAYS_WED            = 0x04,
  RTC_ALARM_WEEKDAYS_THU            = 0x08,
  RTC_ALARM_WEEKDAYS_FRI            = 0x10,
  RTC_ALARM_WEEKDAYS_SAT            = 0x20,
  RTC_ALARM_WEEKDAYS_SUN            = 0x40,
  RTC_ALARM_WEEKDAYS_MON_TO_FRI     = 0x1f,
  RTC_ALARM_WEEKDAYS_SAT_TO_SUN     = 0x60,
  RTC_ALARM_WEEKDAYS_ALL            = 0x7f
} RTCAlarmWeekdays_t;


/**********************************************************
Klasse RealTimeClock_DCF
**********************************************************/
class RealTimeClock_DCF
{
private:

	// Schreiben bzw. Lesen der Register
	void writeRegister(RTCRegister_t, uint8_t*, uint8_t);
	void readRegister(RTCRegister_t, uint8_t, uint8_t*);

	// Konvertierung BCD zu Dezimal bzw. Dezimal zu BCD
	uint8_t decimalToBCD(uint8_t);
	uint8_t BCDToDecimal(uint8_t);

#if RTC_DCF_COMMUNICATION == 0x00
  modSoftwareSerial softSerial;
#endif

public:
	RealTimeClock_DCF();

	// Systemstart
	void begin(void);

	// Zeiteinstellung
	void setDateTime(DateTime*);
	void getDateTime(DateTime*);
	
	// Alarm
  void setAlarmTime(RTCAlarmWeekdays_t, uint8_t, uint8_t);
  void getAlarmTime(RTCAlarmWeekdays_t*, uint8_t*, uint8_t*);
  void enableAlarmInterrupt(void);
	void disableAlarmInterrupt(void);
	void resetAlarmInterrupt(void);
  void enableAlarmLED(void);
  void disableAlarmLED(void);

	// Periodic Interrupt
  void setPeriodicInterruptMode(RTCPeriodicInterruptMode_t);
  void enablePeriodicInterrupt(void);
	void disablePeriodicInterrupt(void);
  void resetPeriodicInterrupt(void);
  void enablePeriodicInterruptLED(void);
  void disablePeriodicInterruptLED(void);

  // DCF77
  void enableDCF77Reception(void);
	void disableDCF77Reception(void);
  void enableDCF77Interrupt(void);
	void disableDCF77Interrupt(void);
  void resetDCF77Interrupt(void);
  void enableDCF77LED(void);
  void disableDCF77LED(void);
};

extern RealTimeClock_DCF RTC_DCF;

#endif /* RealTimeClock_DCF_h */
