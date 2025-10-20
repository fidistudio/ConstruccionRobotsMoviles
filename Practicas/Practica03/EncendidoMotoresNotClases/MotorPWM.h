
#ifndef MOTOR_PWM_H
#define MOTOR_PWM_H

#include <Arduino.h>

class MotorPWM {
public:
  MotorPWM(int speedPin, int directionPin);
  void begin();
  void setSpeed(int speedValue);

private:
  int _speedPin;
  int _directionPin;

  bool isValidSpeed(int speedValue) const;
};

#endif
