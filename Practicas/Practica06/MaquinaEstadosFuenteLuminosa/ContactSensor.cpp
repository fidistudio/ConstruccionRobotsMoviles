
#include "ContactSensor.h"

ContactSensor::ContactSensor(uint8_t pin, bool inverted,
                             unsigned long debounceMs)
    : pin_(pin), inverted_(inverted), debounceMs_(debounceMs),
      obstacleState_(false), lastRawState_(HIGH), lastChangeMs_(0) {}

void ContactSensor::begin() {
  pinMode(pin_, INPUT_PULLUP);
  lastRawState_ = digitalRead(pin_);
  obstacleState_ = inverted_ ? !lastRawState_ : lastRawState_;
  lastChangeMs_ = millis();
}

void ContactSensor::update() {
  bool rawState = digitalRead(pin_);
  unsigned long now = millis();

  if (rawState != lastRawState_) {
    if (now - lastChangeMs_ >= debounceMs_) {
      lastRawState_ = rawState;
      obstacleState_ = inverted_ ? !rawState : rawState;
      lastChangeMs_ = now;
    }
  } else {
    lastChangeMs_ = now;
  }
}

bool ContactSensor::isObstacleDetected() const { return obstacleState_; }
