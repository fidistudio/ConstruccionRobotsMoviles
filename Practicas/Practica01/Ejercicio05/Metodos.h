#ifndef METHODS_H
#define METHODS_H

#include "Variables.h"

// Read raw analog value (ADC)
int readSensor() {
    return analogRead(SENSOR_PIN);
}

// Convert raw ADC value to distance (cm)
float calculateDistance(int rawValue) {
    // Valid sensor range (~80 to 530 ADC)
    if (rawValue >= 80 && rawValue <= 530) {
        return 2076.0 / (rawValue - 11.0); 
    } else {
        return -1; // Out of range
    }
}

// Print measured distance to Serial
void printDistance(float distance) {
    if (distance < 0) {
        Serial.println("Reading error");
    } else {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    }
}

#endif
