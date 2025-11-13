#include "Adafruit_MCP3008.h"

Adafruit_MCP3008 adc;

// Number of light-sensing sectors
const uint8_t NUM_SECTORS = 4;

// MCP3008 channel pairs for each sector (each sector averages 2 channels)
const uint8_t sectorChannels[NUM_SECTORS][2] = {
  {4, 5},  // Sector 0
  {2, 3},  // Sector 1
  {6, 7},  // Sector 2
  {0, 1}   // Sector 3
};

// Current averaged readings for each sector
float sectorValues[NUM_SECTORS] = {0};

// Light threshold to detect arrival
const float LIGHT_THRESHOLD = 800.0;

/**
 * Reads the MCP3008 channels corresponding to each sector and averages them.
 */
void readSectors() {
  for (uint8_t i = 0; i < NUM_SECTORS; i++) {
    uint16_t readingA = adc.readADC(sectorChannels[i][0]);
    uint16_t readingB = adc.readADC(sectorChannels[i][1]);
    sectorValues[i] = (readingA + readingB) / 2.0;
  }
}

/**
 * Returns the index of the sector with the highest light intensity.
 */
int getBrightestSector() {
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

/**
 * Checks if the brightest sector exceeds the defined LIGHT_THRESHOLD.
 * Prints arrival message if the condition is met.
 */
void checkArrival(int brightestSector) {
  if (sectorValues[brightestSector] >= LIGHT_THRESHOLD) {
    Serial.println("ARRIVED TO DESTINY!!");
  }
}

/**
 * Prints all sector readings to the Serial monitor.
 */
void printSectorReadings(int brightestSector) {
  Serial.print("Sector values: ");
  for (uint8_t i = 0; i < NUM_SECTORS; i++) {
    Serial.print("S");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(sectorValues[i]);
    Serial.print("   ");
  }

  Serial.print(" | Brightest: S");
  Serial.println(brightestSector);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Light Source Quadrant Detection System");
  adc.begin();
}

void loop() {
  readSectors();
  int brightestSector = getBrightestSector();
  printSectorReadings(brightestSector);
  checkArrival(brightestSector);
  
  delay(1000);
}
