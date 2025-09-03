#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Leer el estado del comparador (0 = poca luz, 1 = mucha luz)
void leerComparador() {
  estadoLuz = digitalRead(pinComparador);
}

// Mostrar en el Monitor Serial
void mostrarEstadoLuz() {
  //Serial.print("Estado de luz: ");
  if (estadoLuz == HIGH) {
    Serial.println("1");
  } else {
    Serial.println("0");
  }
}

// Controlar LED según estado del comparador
void controlarLED() {
  if (estadoLuz == HIGH) {
    digitalWrite(pinLED, HIGH);  // Enciende LED si hay luz
  } else {
    digitalWrite(pinLED, LOW);   // Apaga LED si está oscuro
  }
}

#endif