#include "Variables.h"
#include "Methods.h"

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  readLDR();
  printLDR();
  controlLED();
  delay(1000); // 1 second between readings
}
