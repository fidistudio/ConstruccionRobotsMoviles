
#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Función para leer el valor del LDR
void leerLDR() {
  valorLDR = analogRead(pinLDR);
  voltajeLDR = (valorLDR * 5.0) / 1023.0;
}

// Función para mostrar valores en Serial
void mostrarLDR() {
  //Serial.print("Valor ADC: ");
  Serial.println(valorLDR);
  //Serial.print("  Voltaje: ");
  //Serial.print(voltajeLDR);
  //Serial.println(" V");
}

// Función para controlar el LED según la luz detectada
void controlarLED() {
  if (valorLDR < UMBRAL_LUZ) {
    digitalWrite(pinLED, HIGH); // Encender LED (hay poca luz)
  } else {
    digitalWrite(pinLED, LOW);  // Apagar LED (hay suficiente luz)
  }
}

#endif
