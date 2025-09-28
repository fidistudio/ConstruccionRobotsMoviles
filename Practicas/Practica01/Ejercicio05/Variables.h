#ifndef VARIABLES_H
#define VARIABLES_H

// Analog pin where the sensor is connected
const int SENSOR_PIN = A0;

// Sampling interval (ms)
const unsigned long SAMPLE_INTERVAL = 500;

// Global variable for timing
unsigned long lastSampleTime = 0;

#endif
