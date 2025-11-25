
#include "ContactSensor.h"

ContactSensor leftSensor(9, false);
ContactSensor rightSensor(8, false);


void setup() {
  Serial.begin(9600);
  leftSensor.begin();
  rightSensor.begin();
}

void loop() {
  leftSensor.update();
  rightSensor.update();

  if (rightSensor.isObstacleDetected()) Serial.println("Obstáculo Derecho");
  if (leftSensor.isObstacleDetected()) Serial.println("Obstáculo Izquierdo");

  delay(60); // muestreo frecuente, el debounce maneja filtrado
}
