
#ifndef CONTACTSENSOR_H
#define CONTACTSENSOR_H

#include <Arduino.h>

class ContactSensor {
public:
  explicit ContactSensor(uint8_t pin, bool inverted = false,
                         unsigned long debounceMs = 50);

  void begin();
  void update();
  bool isObstacleDetected() const;

private:
  const uint8_t pin_;
  const bool inverted_;
  const unsigned long debounceMs_;

  bool obstacleState_;
  bool lastRawState_;
  unsigned long lastChangeMs_;
};

#endif
