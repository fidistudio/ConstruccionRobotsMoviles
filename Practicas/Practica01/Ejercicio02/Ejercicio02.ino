#include "Variables.h"
#include "Methods.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  readTemperature();
  printTemperature();
  delay(1000); // Wait 1 second between readings
}
