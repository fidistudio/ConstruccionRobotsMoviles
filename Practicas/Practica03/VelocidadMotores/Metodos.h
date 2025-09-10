#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Inicializa pines
void inicializarMotores() {
  pinMode(A1_EN, OUTPUT);
  pinMode(A1_IN1, OUTPUT);
  pinMode(A1_IN2, OUTPUT);

  pinMode(A2_EN, OUTPUT);
  pinMode(A2_IN1, OUTPUT);
  pinMode(A2_IN2, OUTPUT);
}

// Controla velocidad y dirección de un motor
void controlarMotor(const String& motor, int velocidad) {
  int in1, in2, en;

  // Selección de motor
  if (motor == "A1") {
    in1 = A1_IN1;
    in2 = A1_IN2;
    en  = A1_EN;
  } else if (motor == "A2") {
    in1 = A2_IN1;
    in2 = A2_IN2;
    en  = A2_EN;
  } else {
    Serial.println("Error: Motor desconocido");
    return;
  }

  // Dirección y magnitud
  if (velocidad > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(en, map(velocidad, 0, 127, 0, 255));
  } else if (velocidad < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(en, map(-velocidad, 0, 127, 0, 255));
  } else {
    // Motor apagado
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(en, 0);
  }
}

// Procesa comando "A1 speed 57"
void procesarComando(const String& comando) {
  String motor, palabra, valorStr;
  int primerEspacio = comando.indexOf(' ');
  int segundoEspacio = comando.indexOf(' ', primerEspacio + 1);

  if (primerEspacio == -1 || segundoEspacio == -1) return;

  motor = comando.substring(0, primerEspacio);
  palabra = comando.substring(primerEspacio + 1, segundoEspacio);
  valorStr = comando.substring(segundoEspacio + 1);

  palabra.toLowerCase();

  if (palabra == "speed") {
    int velocidad = valorStr.toInt();
    if (velocidad >= -127 && velocidad <= 127) {
      controlarMotor(motor, velocidad);
    } else {
      Serial.println("Error: Velocidad fuera de rango (-127 a 127)");
    }
  } else {
    Serial.println("Error: Comando inválido");
  }
}

#endif
