#ifndef VARIABLES_H
#define VARIABLES_H

// Pin analógico donde está conectado el sensor
const int SENSOR_PIN = A0;

// Intervalo de muestreo (ms)
const unsigned long SAMPLE_INTERVAL = 500;

// Variables globales
unsigned long lastSampleTime = 0;

#endif
