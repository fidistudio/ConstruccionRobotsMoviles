
#include "IRSensor.h"

// Crear instancias de sensores
IRSensor sensorDerecho(A1, 300);
IRSensor sensorIzquierdo(A0, 300);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Actualizar cada sensor
  sensorDerecho.update();
  sensorIzquierdo.update();

  // Revisar banderas
  if (sensorDerecho.isObstacleDetected()) {
    Serial.println("Obstáculo derecho detectado!");
  }

  if (sensorIzquierdo.isObstacleDetected()) {
    Serial.println("Obstáculo izquierdo detectado!");
  }

  delay(200);
}
