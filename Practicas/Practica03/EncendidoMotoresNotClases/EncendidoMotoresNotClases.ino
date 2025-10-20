
#include "MotorPWM.h"

MotorPWM motorA1(5, 7);
MotorPWM motorA2(6, 8);

String serialCommand = "";

void setup() {
Serial.begin(9600);

motorA1.begin();
motorA2.begin();

Serial.println("System ready. Enter commands:");
Serial.println("Example: A1 speed 255");
Serial.println("         A2 speed -255");

}

void loop() {
handleSerial();
}

void handleSerial() {
if (!Serial.available()) return;

char c = Serial.read();
if (c == '\n' || c == '\r') {
    serialCommand.trim();
    if (serialCommand.length() > 0) {
        processCommand(serialCommand);
    }
    serialCommand = "";
} else {
    serialCommand += c;
}

}

void processCommand(const String& command) {
int firstSpace = command.indexOf(' ');
int secondSpace = command.indexOf(' ', firstSpace + 1);

if (firstSpace == -1 || secondSpace == -1) {
    Serial.println("Error: invalid command format.");
    return;
}

String motorID = command.substring(0, firstSpace);
String keyword = command.substring(firstSpace + 1, secondSpace);
String valueStr = command.substring(secondSpace + 1);
valueStr.trim();

int speedValue = valueStr.toInt();
motorID.toUpperCase();

if (motorID == "A1") {
    motorA1.setSpeed(speedValue);
} else if (motorID == "A2") {
    motorA2.setSpeed(speedValue);
} else {
    Serial.println("Unknown motor ID. Use A1 or A2.");
}

}
