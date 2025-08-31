#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Función para leer el valor del sensor TMP36
void leerTemperatura() {
  // Leer el valor analógico (0 - 1023)
  valorADC = analogRead(pinTMP36);

  // Convertir a voltaje (5V referencia)
  voltaje = (valorADC * 5.0) / 1023.0;

  // Convertir a grados centígrados
  // Fórmula: T(°C) = (Vout - 0.5) * 100
  temperaturaC = (voltaje - 0.5) * 100.0;
}

// Función para mostrar los resultados en Serial
void mostrarTemperatura() {
  Serial.print("ADC: ");
  Serial.print(valorADC);
  Serial.print("  Voltaje: ");
  Serial.print(voltaje);
  Serial.print(" V  Temperatura: ");
  Serial.print(temperaturaC);
  Serial.println(" °C");
}

#endif
