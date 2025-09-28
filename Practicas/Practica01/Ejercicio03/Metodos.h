#ifndef METHODS_H
#define METHODS_H

#include "Variables.h"

// Read the LDR value
void readLDR() {
  ldrValue = analogRead(LDR_PIN);
  ldrVoltage = (ldrValue * 5.0) / 1023.0;
}

// Print LDR value to Serial
void printLDR() {
  Serial.println(ldrValue);
}

// Control LED based on light level
void controlLED() {
  if (ldrValue < LIGHT_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH); // Turn LED on (low light)
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn LED off (enough light)
  }
}

#endif
