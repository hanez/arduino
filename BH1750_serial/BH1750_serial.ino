// Written 2015 by Johannes Findeisen <you@hanez.org>

#include <Wire.h>
#include <BH1750FVI.h>

BH1750FVI LightSensor;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  LightSensor.begin();
  LightSensor.SetAddress(Device_Address_L);
  LightSensor.SetMode(Continuous_H_resolution_Mode);
}

void loop() {
  uint16_t lux = LightSensor.GetLightIntensity(); // Get Lux value
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(800);
}
