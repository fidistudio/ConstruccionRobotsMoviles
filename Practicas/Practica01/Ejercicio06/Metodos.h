#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"
#include <Arduino.h>

// --- Contacto ---
int leerContact() {
    estadoContact = digitalRead(PIN_CONTACT);
    return estadoContact;
}

// --- Fotoresistencia analógica ---
int leerPhotoRA() {
    valorPhotoAnalog = analogRead(PIN_PHOTO_ANALOG);
    return valorPhotoAnalog;
}

// --- Fotoresistencia digital ---
int leerPhotoRD() {
    estadoPhotoDigital = digitalRead(PIN_PHOTO_DIGITAL);
    return estadoPhotoDigital;
}

// --- LM35 ---
float leerTemp() {
    int val = analogRead(PIN_TEMP);
    float voltaje = (val * 5.0) / 1023.0;
    temperaturaC = voltaje * 100.0;
    return temperaturaC;
}

// --- Infrarrojo ---
int leerInfrared() {
    estadoInfrared = analogRead(PIN_INFRARED);
    return estadoInfrared;
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

// --- Procesar comando Serial ---
void procesarComando(String command) {
    command.trim();

    if (!command.startsWith("shs ")) {
        Serial.println("Comando inválido");
        return;
    }

    String sensor = command.substring(4);

    if (sensor == "contact") {
        Serial.println(leerContact());
    } else if (sensor == "photora") {
        Serial.println(leerPhotoRA());
    } else if (sensor == "photord") {
        Serial.println(leerPhotoRD());
    } else if (sensor == "temp") {
        Serial.println(leerTemp());
    } else if (sensor == "infrared") {
        Serial.println(distancia = calcularDistancia(leerInfrared()));
    } else {
        Serial.println("Sensor no reconocido");
    }
}

#endif
