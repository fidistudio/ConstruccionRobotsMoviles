#include "Variables.h"
#include "Methods.h"

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);   // Button with external pulldown resistor
}

void loop() {
  readButton();   // Method defined in Methods.h
}
