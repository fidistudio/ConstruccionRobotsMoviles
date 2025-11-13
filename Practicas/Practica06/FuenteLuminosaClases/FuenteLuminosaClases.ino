#include "LightSensorArray.h"

// Configure threshold here
LightSensorArray sensorArray(800.0);

void setup() {
    Serial.begin(9600);
    while (!Serial);

    Serial.println("Light Source Quadrant Detection System (OOP Version)");

    sensorArray.begin();
}

void loop() {
    sensorArray.readSectors();
    
    uint8_t brightest = sensorArray.getBrightestSector();

    // Print readings
    Serial.print("Sectors: ");
    for (uint8_t i = 0; i < LightSensorArray::NUM_SECTORS; i++) {
        Serial.print("S");
        Serial.print(i);
        Serial.print(": ");
        Serial.print(sensorArray.getSectorValue(i));
        Serial.print("  ");
    }

    Serial.print("| Brightest: S");
    Serial.print(brightest);

    if (sensorArray.hasArrivedToDestination()) {
        Serial.print("  --> ARRIVED TO DESTINY!!");
    }

    Serial.println();
    delay(1000);
}
