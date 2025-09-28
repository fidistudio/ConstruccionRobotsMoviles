#ifndef METHODS_H
#define METHODS_H

#include "Variables.h"

void readTemperature() {
  adcValue = analogRead(LM35_PIN);
  voltage = (adcValue * 5.0) / 1023.0;
  temperatureC = voltage * 100.0; // LM35 formula
}

void printTemperature() {
  Serial.println(temperatureC);
}

#endif

