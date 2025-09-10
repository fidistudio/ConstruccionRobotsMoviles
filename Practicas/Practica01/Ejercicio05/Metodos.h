#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Lee el valor analógico (raw ADC)
int leerValorSensor() {
    return analogRead(SENSOR_PIN);
}

// Convierte el valor crudo ADC a distancia (cm)
float calcularDistancia(int rawValue) {
    // Rango válido del sensor (~80 a 530 ADC)
    if (rawValue >= 80 && rawValue <= 530) {
        return 2076.0 / (rawValue - 11.0); 
    } else {
        return -1; // Valor fuera de rango
    }
}

// Muestra la distancia medida por Serial
void mostrarDistancia(float distancia) {
    if (distancia < 0) {
        Serial.println("Error de lectura");
    } else {
        Serial.print("Distancia: ");
        Serial.print(distancia);
        Serial.println(" cm");
    }
}

#endif
