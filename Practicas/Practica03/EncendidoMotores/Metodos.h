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

  digitalWrite(A1_EN, HIGH);
  digitalWrite(A2_EN, HIGH);
}

// Controla un motor específico
void controlarMotor(const String& motor, EstadoMotor estado, DireccionMotor direccion) {
  int in1, in2;

  if (motor == "A1") {
    in1 = A1_IN1;
    in2 = A1_IN2;
  } else if (motor == "A2") {
    in1 = A2_IN1;
    in2 = A2_IN2;
  } else {
    Serial.println("Error: Motor desconocido");
    return;
  }

  if (estado == OFF) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    return;
  }

  if (direccion == LEFT) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (direccion == RIGHT) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

// Procesa un comando en formato texto
void procesarComando(const String& comando) {
  String motor, accion, direccion;
  int primerEspacio = comando.indexOf(' ');
  int segundoEspacio = comando.indexOf(' ', primerEspacio + 1);

  if (primerEspacio == -1) return;

  motor = comando.substring(0, primerEspacio);
  accion = (segundoEspacio == -1) ? comando.substring(primerEspacio + 1) 
                                  : comando.substring(primerEspacio + 1, segundoEspacio);
  direccion = (segundoEspacio == -1) ? "" : comando.substring(segundoEspacio + 1);

  accion.toLowerCase();
  direccion.toLowerCase();

  if (accion == "off") {
    controlarMotor(motor, OFF, STOP);
  } else if (accion == "on") {
    if (direccion == "left") {
      controlarMotor(motor, ON, LEFT);
    } else if (direccion == "right") {
      controlarMotor(motor, ON, RIGHT);
    } else {
      Serial.println("Error: Dirección inválida");
    }
  } else {
    Serial.println("Error: Acción inválida");
  }
}

#endif
