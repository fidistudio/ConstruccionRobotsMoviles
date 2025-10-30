
#include "IRSensor.h"

// Crear instancias de sensores
IRSensor sensorDerecho(A2, 300);
IRSensor sensorIzquierdo(A0, 300);
IRSensor sensorFrontal(A1, 400);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Actualizar cada sensor
  sensorDerecho.update();
  sensorIzquierdo.update();
  sensorFrontal.update();

  // Revisar banderas
  if (sensorFrontal.isObstacleDetected()){
    Serial.println("Obstáculo frontal detectado!");
  }

  //Serial.print("SensorIzquierdo: ");
  //Serial.println(sensorIzquierdo.rawValue);
  //Serial.print("SensorDerecho: ");
  //Serial.println(sensorDerecho.rawValue);
  Serial.print("SensorFrontal: ");
  Serial.println(sensorFrontal.rawValue);
  
  delay(200);
}
