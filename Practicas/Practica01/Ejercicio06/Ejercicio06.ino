#include <Arduino.h>
#include "Variables.h"
#include "Methods.h"

void setup() {
    Serial.begin(9600);

    // Digital pins
    pinMode(PIN_CONTACT, INPUT);
    pinMode(PIN_PHOTO_DIGITAL, INPUT);
    pinMode(PIN_INFRARED, INPUT);
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        processCommand(command);
    }
}
