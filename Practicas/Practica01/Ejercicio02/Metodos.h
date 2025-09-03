#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Función para leer el valor del sensor TMP36
void leerTemperatura() {
  // Leer el valor analógico (0 - 1023)
  valorADC = analogRead(pinLM35);

  // Convertir a voltaje (5V referencia)
  voltaje = (valorADC * 5.0) / 1023.0;

  // Convertir a grados centígrados
  // Fórmula TMP36: T(°C) = (Vout - 0.5) * 100
  //temperaturaC = (voltaje - 0.5) * 100.0;
  // Fórmula LM35: T(°C) = (Vout ) * 100
  temperaturaC = (voltaje) * 100.0;
}

// Función para mostrar los resultados en Serial
void mostrarTemperatura() {
  //Serial.print("ADC: ");
  //Serial.print(valorADC);
  //Serial.print("  Voltaje: ");
  //Serial.print(voltaje);
  //Serial.print(" V  Temperatura: ");
  Serial.println(temperaturaC);
  //Serial.println(" °C");
}

#endif
