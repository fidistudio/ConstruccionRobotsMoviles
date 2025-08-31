#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Función para leer el valor del LDR
void leerLDR() {
  // Leer valor analógico (0 - 1023)
  valorLDR = analogRead(pinLDR);

  // Convertir a voltaje (usando referencia de 5V)
  voltajeLDR = (valorLDR * 5.0) / 1023.0;
}

// Función para mostrar en el Monitor Serial
void mostrarLDR() {
  Serial.print("Valor ADC: ");
  Serial.print(valorLDR);
  Serial.print("  Voltaje: ");
  Serial.print(voltajeLDR);
  Serial.println(" V");
}

#endif
