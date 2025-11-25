
#include "LightSensorArray.h"

// Channel pairs for each sector
const uint8_t LightSensorArray::sectorChannels[NUM_SECTORS][2] = {
    {4, 5}, // Sector 0
    {2, 3}, // Sector 1
    {6, 7}, // Sector 2
    {0, 1}  // Sector 3
};

LightSensorArray::LightSensorArray(float lightThreshold)
    : threshold(lightThreshold) {
  // Initialize sector values
  for (uint8_t i = 0; i < NUM_SECTORS; i++) {
    sectorValues[i] = 0;
  }
}

void LightSensorArray::begin() { adc.begin(); }

void LightSensorArray::readSectors() {
  for (uint8_t i = 0; i < NUM_SECTORS; i++) {
    uint16_t a = adc.readADC(sectorChannels[i][0]);
    uint16_t b = adc.readADC(sectorChannels[i][1]);
    sectorValues[i] = (a + b) / 2.0;
  }
}

uint8_t LightSensorArray::getBrightestSector() const {
  uint8_t brightest = 0;
  float maxValue = sectorValues[0];

  for (uint8_t i = 1; i < NUM_SECTORS; i++) {
    if (sectorValues[i] > maxValue) {
      maxValue = sectorValues[i];
      brightest = i;
    }
  }

  return brightest;
}

bool LightSensorArray::hasArrivedToDestination() const {
  uint8_t brightest = getBrightestSector();
  return sectorValues[brightest] >= threshold;
}

float LightSensorArray::getSectorValue(uint8_t sectorIndex) const {
  if (sectorIndex >= NUM_SECTORS) {
    return -1; // invalid index
  }
  return sectorValues[sectorIndex];
}
