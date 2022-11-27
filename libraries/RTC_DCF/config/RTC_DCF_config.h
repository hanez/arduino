#ifndef RTC_DCF_config_h
#define RTC_DCF_config_h

/******************************************************************************
Definitionen
******************************************************************************/
/* Wahl der Kommunikationsart
   mögliche Werte:  0x00  UART
                    0x01  SPI
                    Ox02  I2C */
#define RTC_DCF_COMMUNICATION     0x02

/* eingestellte I2C-Adresse des RTC-DCF (wird nur bei I2C-Kommunikation benötigt) */
#define RTC_DCF_I2C_ADDRESS       0x01

/* eingestellte Baudrate des RTC-DCF (wird nur bei UART-Kommunikation benötigt) */
#define RTC_DCF_UART_BAUDRATE     4800

#endif /* RTC_DCF_config_h */

