#include "DifferentialDrive.h"

DifferentialDrive::DifferentialDrive(MotorPWM &left, MotorPWM &right, ContactSensor &contactLeft, ContactSensor &contactRight, const Params &p) : _leftMotor(left), _rightMotor(right), _contactLeft(contactLeft), _contactRight(contactRight), _p(p) {}

void DifferentialDrive::begin() {
  _leftMotor.begin();
  _rightMotor.begin();
  _contactLeft.begin();
  _contactRight.begin();
  stop();
}

void DifferentialDrive::onLeftTick() { _leftCount++; }
void DifferentialDrive::onRightTick() { _rightCount++; }

void DifferentialDrive::resetEncoders() {
  noInterrupts();
  _leftCount = 0;
  _rightCount = 0;
  interrupts();
}

inline long DifferentialDrive::ticksFromMetersLeft(float m) const {
  // ticks = m * (TPR / (2πR))
  const float tpm = _p.ticksPerRev / (2.0f * PI * _p.wheelRadiusLeft);
  return lroundf(fabs(m) * tpm);
}

inline long DifferentialDrive::ticksFromMetersRight(float m) const {
  const float tpm = _p.ticksPerRev / (2.0f * PI * _p.wheelRadiusRight);
  return lroundf(fabs(m) * tpm);
}

void DifferentialDrive::driveUntilTicks(long goalLeft, long goalRight,
                                        int leftCmd, int rightCmd,
                                        const __FlashStringHelper *tag) {
  resetEncoders();
  _leftMotor.setSpeed(leftCmd);
  _rightMotor.setSpeed(rightCmd);

  if (_debug) {
    Serial.println(F("----- MOVE -----"));
    Serial.print(F("Goal L: "));
    Serial.println(goalLeft);
    Serial.print(F("Goal R: "));
    Serial.println(goalRight);
    Serial.println(F("----------------"));
  }

  while (_leftCount < goalLeft && _rightCount < goalRight) {
    updateContacts();
    if (_interrupted){
      stop();
      _leftMotor.setSpeed(-_p.duty);
      _rightMotor.setSpeed(-_p.duty);
      delay(300);
      stop();
      break;
    }
    if (_debug) {
      Serial.print(F("L "));
      Serial.print(_leftCount);
      Serial.print(F("/"));
      Serial.print(goalLeft);
      Serial.print(F(" | R "));
      Serial.print(_rightCount);
      Serial.print(F("/"));
      Serial.println(goalRight);
    }
    // sin delay -> respuesta fluida
  }

  stop();
  if (_debug) {
    Serial.print(tag);
    Serial.println(F(" done."));
  }
}

void DifferentialDrive::moveLinear(float distanceMeters) {
  const int dir = (distanceMeters >= 0) ? +1 : -1;
  const long goalL = ticksFromMetersLeft(distanceMeters);
  const long goalR = ticksFromMetersRight(distanceMeters);
  driveUntilTicks(goalL, goalR, _p.duty * dir, _p.duty * dir, F("Linear"));
}

void DifferentialDrive::moveAngular(float angleDegrees) {
  // arco por rueda: s = (B/2) * |θ|
  const float theta = fabs(angleDegrees) * PI / 180.0f;
  const float arc = (_p.wheelBase * 0.5f) * theta;

  const long goalL = ticksFromMetersLeft(arc);
  const long goalR = ticksFromMetersRight(arc);

  // Convención idéntica a tu .ino: +θ => L avanza, R retrocede (o viceversa)
  const int dir = (angleDegrees >= 0) ? +1 : -1;
  const int leftCmd = _p.duty * dir;
  const int rightCmd = _p.duty * -dir;

  driveUntilTicks(goalL, goalR, leftCmd, rightCmd, F("Angular"));
}

void DifferentialDrive::moveRobot(float linearMeters, float angularDegrees) {
  // Igual que la práctica: primero giro, luego avance
  if (fabs(angularDegrees) > 1e-6f)
    moveAngular(angularDegrees);
  if (fabs(linearMeters) > 1e-6f)
    moveLinear(linearMeters);
}

void DifferentialDrive::stop() {
  _leftMotor.setSpeed(0);
  _rightMotor.setSpeed(0);
}

void DifferentialDrive::updateContacts(){
  _contactLeft.update();
  _contactRight.update();
  _interrupted = _contactLeft.isObstacleDetected() || _contactRight.isObstacleDetected();
}
