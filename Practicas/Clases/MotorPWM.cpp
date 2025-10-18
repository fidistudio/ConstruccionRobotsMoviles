
#include "MotorPWM.h"

MotorPWM::MotorPWM(uint8_t en, uint8_t in1, uint8_t in2)
  : pinEN(en), pinIN1(in1), pinIN2(in2), speed(0), direction(STOP) {}

void MotorPWM::begin() {
  pinMode(pinEN, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  stop();
}

void MotorPWM::setSpeed(uint8_t pwmValue) {
  speed = constrain(pwmValue, 0, 255);
  analogWrite(pinEN, speed);
}

void MotorPWM::setDirection(MotorDirection dir) {
  direction = dir;
  switch (direction) {
    case FORWARD:
      digitalWrite(pinIN1, HIGH);
      digitalWrite(pinIN2, LOW);
      break;
    case BACKWARD:
      digitalWrite(pinIN1, LOW);
      digitalWrite(pinIN2, HIGH);
      break;
    case STOP:
    default:
      digitalWrite(pinIN1, LOW);
      digitalWrite(pinIN2, LOW);
      break;
  }
}

void MotorPWM::forward(uint8_t pwmValue) {
  setDirection(FORWARD);
  setSpeed(pwmValue);
}

void MotorPWM::backward(uint8_t pwmValue) {
  setDirection(BACKWARD);
  setSpeed(pwmValue);
}

void MotorPWM::stop() {
  setDirection(STOP);
  setSpeed(0);
}

void MotorPWM::printStatus() {
  Serial.print("Motor pins [EN, IN1, IN2]: ");
  Serial.print(pinEN);
  Serial.print(", ");
  Serial.print(pinIN1);
  Serial.print(", ");
  Serial.print(pinIN2);
  Serial.print(" | Direction: ");
  switch (direction) {
    case FORWARD: Serial.print("FORWARD"); break;
    case BACKWARD: Serial.print("BACKWARD"); break;
    case STOP: Serial.print("STOP"); break;
  }
  Serial.print(" | Speed: ");
  Serial.println(speed);
}
