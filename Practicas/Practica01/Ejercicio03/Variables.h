#ifndef VARIABLES_H
#define VARIABLES_H

// Analog pin for the LDR
const int LDR_PIN = A0;

// Digital pin for the LED
const int LED_PIN = 13;

// Global variables
int ldrValue = 0;
float ldrVoltage = 0.0;

// Threshold to turn the LED on (adjust as needed)
const int LIGHT_THRESHOLD = 900;

#endif
