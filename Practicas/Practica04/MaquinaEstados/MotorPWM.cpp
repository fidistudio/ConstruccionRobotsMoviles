
#include "MotorPWM.h"

MotorPWM::MotorPWM(int speedPin, int directionPin)
    : _speedPin(speedPin), _directionPin(directionPin) {}

void MotorPWM::begin() {
  pinMode(_speedPin, OUTPUT);
  pinMode(_directionPin, OUTPUT);
}

void MotorPWM::setSpeed(int speedValue) {
  if (!isValidSpeed(speedValue)) {
    Serial.println("Invalid speed value. Range: -255 to 255");
    return;
  }

  int pwmValue = abs(speedValue);
  bool direction = (speedValue >= 0);

  analogWrite(_speedPin, pwmValue);
  digitalWrite(_directionPin, direction ? HIGH : LOW);
}

bool MotorPWM::isValidSpeed(int speedValue) const {
  return (speedValue >= -255 && speedValue <= 255);
}
