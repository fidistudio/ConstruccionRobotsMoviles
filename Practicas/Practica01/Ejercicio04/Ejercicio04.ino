#include "Variables.h"
#include "Methods.h"

void setup() {
  Serial.begin(9600);
  pinMode(COMPARATOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  readComparator();
  printLightState();
  //controlLED();
  delay(500); // Half a second between readings
}
