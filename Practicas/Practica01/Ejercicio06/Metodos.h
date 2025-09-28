#ifndef METHODS_H
#define METHODS_H

#include "Variables.h"
#include <Arduino.h>

// --- Contact sensor ---
int readContact() {
    contactState = digitalRead(PIN_CONTACT);
    return contactState;
}

// --- Photoresistor analog ---
int readPhotoAnalog() {
    photoAnalogValue = analogRead(PIN_PHOTO_ANALOG);
    return photoAnalogValue;
}

// --- Photoresistor digital ---
int readPhotoDigital() {
    photoDigitalState = digitalRead(PIN_PHOTO_DIGITAL);
    return photoDigitalState;
}

// --- LM35 temperature sensor ---
float readTemperature() {
    int val = analogRead(PIN_TEMP);
    float voltage = (val * 5.0) / 1023.0;
    temperatureC = voltage * 100.0;
    return temperatureC;
}

// --- Infrared sensor ---
int readInfrared() {
    infraredRaw = analogRead(PIN_INFRARED);
    return infraredRaw;
}

// Convert raw ADC to distance (cm)
float calculateDistance(int rawValue) {
    if (rawValue >= 80 && rawValue <= 530) {
        return 2076.0 / (rawValue - 11.0); 
    } else {
        return -1; // Out of range
    }
}

// --- Process Serial command ---
void processCommand(String command) {
    command.trim();

    if (!command.startsWith("shs ")) {
        Serial.println("Invalid command");
        return;
    }

    String sensor = command.substring(4);

    if (sensor == "contact") {
        Serial.println(readContact());
    } else if (sensor == "photora") {
        Serial.println(readPhotoAnalog());
    } else if (sensor == "photord") {
        Serial.println(readPhotoDigital());
    } else if (sensor == "temp") {
        Serial.println(readTemperature());
    } else if (sensor == "infrared") {
        distance = calculateDistance(readInfrared());
        Serial.println(distance);
    } else {
        Serial.println("Unknown sensor");
    }
}

#endif
