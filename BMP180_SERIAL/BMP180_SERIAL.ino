#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup(void) {
  Serial.begin(9600);
  Serial.println("Arduino BMP180 Pressure Sensor");
  Serial.println("");
  bmp.begin();
}

void loop(void) {
  sensors_event_t event;
  bmp.getEvent(&event);
  if (event.pressure)
  {
    Serial.print("Pressure: ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
  }
  else
  {
    Serial.println("Sensor error");
  }
  delay(1000);
}
