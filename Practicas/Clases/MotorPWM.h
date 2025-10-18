
#ifndef MOTORPWM_H
#define MOTORPWM_H

#include <Arduino.h>

enum MotorDirection { FORWARD, BACKWARD, STOP };

class MotorPWM {
  private:
    uint8_t pinEN;
    uint8_t pinIN1;
    uint8_t pinIN2;
    uint8_t speed;  // 0–255
    MotorDirection direction;

  public:
    // Constructor
    MotorPWM(uint8_t en, uint8_t in1, uint8_t in2);

    // Inicialización
    void begin();

    // Control de velocidad y dirección
    void setSpeed(uint8_t pwmValue);
    void setDirection(MotorDirection dir);

    // Métodos de movimiento
    void forward(uint8_t pwmValue);
    void backward(uint8_t pwmValue);
    void stop();

    // Depuración opcional
    void printStatus();
};

#endif
