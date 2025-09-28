#ifndef VARIABLES_H
#define VARIABLES_H

// --- Pins ---
const int PIN_CONTACT = 2;        // Button / Contact sensor
const int PIN_PHOTO_ANALOG = A0;  // Photoresistor (analog)
const int PIN_PHOTO_DIGITAL = 3;  // Photoresistor (digital threshold)
const int PIN_TEMP = A2;          // LM35
const int PIN_INFRARED = A3;      // Infrared sensor

// --- Thresholds ---
const int PHOTO_THRESHOLD = 512;  // For analog photoresistor thresholding

// --- Global variables ---
int contactState = 0;
int photoDigitalState = 0;
int photoAnalogValue = 0;
float temperatureC = 0;
int infraredRaw = 0;
float distance = 0;

#endif
