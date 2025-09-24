#ifndef VARIABLES_H
#define VARIABLES_H

// Entrada digital desde la salida del LM358N
const int pinComparador = 2;

// Salida PWM que genera el voltaje de referencia
const int pinPWMReferencia = 5; // Pin PWM de Arduino UNO

// Salida para indicar resultado del comparador
const int pinLED = 9;

// Estado leído del comparador
int estadoComparador = 0;

// Valor fijo del PWM para generar referencia (0-255)
const int referenciaPWM = 100; // ~2.5V con filtro RC

#endif
