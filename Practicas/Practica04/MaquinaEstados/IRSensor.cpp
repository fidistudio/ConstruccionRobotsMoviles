
#include "IRSensor.h"

// Constructor
IRSensor::IRSensor(int sensorPin, int threshold) {
  pin = sensorPin;
  umbral = threshold;
  obstacle = false;
}

// Leer sensor y actualizar bandera
void IRSensor::update() {
  int rawValue = analogRead(pin);
  obstacle = (rawValue > umbral);
}

// Obtener la bandera
bool IRSensor::isObstacleDetected() const { return obstacle; }
