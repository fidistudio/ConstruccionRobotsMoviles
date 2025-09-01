#ifndef VARIABLES_H
#define VARIABLES_H

// Pin analógico donde está conectado el LDR
const int pinLDR = A0;

// Pin digital para el LED
const int pinLED = 13;

// Variables globales
int valorLDR = 0;
float voltajeLDR = 0.0;

// Umbral para prender el LED (ajustable según pruebas)
const int UMBRAL_LUZ = 900;

#endif
