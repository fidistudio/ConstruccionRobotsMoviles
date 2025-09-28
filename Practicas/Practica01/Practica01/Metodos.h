#ifndef METHODS_H
#define METHODS_H

#include "Variables.h"

// Function to read and print button state
void readButton() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    Serial.println("1");
  } else {
    Serial.println("0");   // Prints 0 when button is not pressed
  }

  delay(200); // Prevents flooding the serial monitor
}

#endif
