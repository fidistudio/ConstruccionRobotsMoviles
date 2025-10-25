#ifndef DIFFERENTIAL_DRIVE_H
#define DIFFERENTIAL_DRIVE_H

#include "MotorPWM.h"
#include <Arduino.h>

class DifferentialDrive {
public:
  struct Params {
    float wheelRadiusLeft;  // m
    float wheelRadiusRight; // m
    float wheelBase;        // m (distancia entre ruedas)
    long ticksPerRev;       // ticks por vuelta de encoder
    int duty;               // 0..255
  };

  DifferentialDrive(MotorPWM &left, MotorPWM &right, const Params &p);

  void begin();

  // Encoders: el .ino define las ISR y sólo llama a estos métodos.
  void onLeftTick();
  void onRightTick();

  // Control de movimiento (idéntico a tu primer .ino)
  void moveLinear(float distanceMeters);
  void moveAngular(float angleDegrees);
  void moveRobot(float linearMeters,
                 float angularDegrees); // gira y luego avanza
  void stop();

  // Utilidades
  void resetEncoders();
  long leftCount() const { return _leftCount; }
  long rightCount() const { return _rightCount; }

  // (Opcional) logging por puerto serie
  void setDebug(bool enabled) { _debug = enabled; }

private:
  MotorPWM &_leftMotor;
  MotorPWM &_rightMotor;
  Params _p;

  volatile long _leftCount = 0;
  volatile long _rightCount = 0;

  bool _debug = false;

  inline long ticksFromMetersLeft(float m) const;
  inline long ticksFromMetersRight(float m) const;
  void driveUntilTicks(long goalLeft, long goalRight, int leftCmd, int rightCmd,
                       const __FlashStringHelper *tag);
};

#endif
