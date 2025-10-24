
#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <Arduino.h>

class IRSensor {
private:
  int pin;       // Pin analógico del sensor
  int umbral;    // Valor de ADC para detectar obstáculo
  bool obstacle; // Bandera interna

public:
  // Constructor
  IRSensor(int sensorPin, int threshold);

  // Leer el sensor y actualizar la bandera
  void update();

  // Obtener la bandera
  bool isObstacleDetected() const;
};

#endif
