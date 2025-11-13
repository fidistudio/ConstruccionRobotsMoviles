
#ifndef LIGHT_SENSOR_ARRAY_H
#define LIGHT_SENSOR_ARRAY_H

#include "Adafruit_MCP3008.h"
#include <Arduino.h>

class LightSensorArray {
public:
  static const uint8_t NUM_SECTORS = 4;

  // Constructor: receives threshold value
  LightSensorArray(float lightThreshold);

  // Initializes MCP3008
  void begin();

  // Reads and updates sector values
  void readSectors();

  // Returns index of sector with highest light intensity
  uint8_t getBrightestSector() const;

  // Returns true if brightest sector meets or exceeds threshold
  bool hasArrivedToDestination() const;

  // Returns last read intensity value for a given sector
  float getSectorValue(uint8_t sectorIndex) const;

private:
  Adafruit_MCP3008 adc;
  float sectorValues[NUM_SECTORS];
  float threshold;

  // MCP3008 channel mapping (each sector uses 2 channels)
  static const uint8_t sectorChannels[NUM_SECTORS][2];
};

#endif
