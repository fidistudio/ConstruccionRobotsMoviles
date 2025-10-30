
#include "IRSensor.h"

// Constructor
IRSensor::IRSensor(int sensorPin, int threshold) {
  pin = sensorPin;
  umbral = threshold;
  obstacle = false;
}

// Leer sensor y actualizar bandera
void IRSensor::update() {
  rawValue = analogRead(pin);
  obstacle = (rawValue > umbral);
}

// Obtener la bandera
bool IRSensor::isObstacleDetected() const { return obstacle; }

void IRSensor::printRawValue(){
  Serial.print("Raw value: ");
  Serial.println(rawValue); 
}
