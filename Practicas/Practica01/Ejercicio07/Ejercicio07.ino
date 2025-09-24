#include <Arduino.h>
#include "Variables.h"
#include "Metodos.h"

void setup() {
  pinMode(PIN_PWM, OUTPUT);
  pinMode(PIN_COMPARAR, INPUT);
  Serial.begin(9600);

  // Calibración automática al encender
  calibration();
}

void loop() {
  // Leer si llega un comando por Serial
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim(); // eliminar espacios y saltos de línea

    if (comando == "shs calibration") {
      calibration();
    }else if(comando == "shs photord"){
      // Reporte del estado comparador cada 500 ms
  reportarEstado();
    }
  }
  delay(500);
}
