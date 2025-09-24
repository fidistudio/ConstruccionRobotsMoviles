#ifndef METODOS_H
#define METODOS_H

#include <Arduino.h>
#include "Variables.h"

// Leer el estado digital del comparador
int leerComparador() {
  return digitalRead(PIN_COMPARAR);  // HIGH si LDR > PWM, LOW si LDR <= PWM
}

// Aplicar PWM al pin de salida
void aplicarPWM(int valor) {
  analogWrite(PIN_PWM, valor);
}

// Calibración automática
void calibration() {

  int pwm = 0;
  aplicarPWM(pwm);

  // Incrementar PWM hasta que el comparador pase a LOW
  while (leerComparador() == HIGH && pwm < 255) {
    pwm++;
    aplicarPWM(pwm);
    delay(5); // pequeño retardo para que el comparador responda
  }

  pwmReferencia = pwm;
  Serial.println("Calibration complete. ");
  //Serial.println(pwmReferencia);
}

// Reporte del estado actual
void reportarEstado() {
  int estado = leerComparador();
  //Serial.print("Estado comparador: ");
  if (estado == HIGH) Serial.println("1");
  else Serial.println("0");
  //Serial.print("PWM referencia: ");
  //Serial.println(pwmReferencia);
}

#endif

