#ifndef METHODS_H
#define METHODS_H

#include "Variables.h"

// Read comparator state (0 = low light, 1 = bright light)
void readComparator() {
  lightState = digitalRead(COMPARATOR_PIN);
}

// Print light state to Serial
void printLightState() {
  if (lightState == HIGH) {
    Serial.println("1");
  } else {
    Serial.println("0");
  }
}

// Control LED based on comparator state
void controlLED() {
  if (lightState == HIGH) {
    digitalWrite(LED_PIN, HIGH);  // Turn LED on if bright
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn LED off if dark
  }
}

#endif
