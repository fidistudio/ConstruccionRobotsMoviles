#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Inicializar PWM de referencia
void inicializarPWMReferencia() {
    analogWrite(pinPWMReferencia, referenciaPWM);
}

// Leer salida digital del comparador
void leerComparador() {
    estadoComparador = digitalRead(pinComparador);
}

// Mostrar estado en el monitor serial
void mostrarEstadoComparador() {
    Serial.print("Comparador: ");
    Serial.println(estadoComparador == HIGH ? "1" : "0");
}

// Controlar LED según salida del comparador
void controlarLED() {
    digitalWrite(pinLED, estadoComparador);
}

#endif
