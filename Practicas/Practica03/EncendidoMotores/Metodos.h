#ifndef METHODS_H
#define METHODS_H

#include "Variables.h"

// Initialize motor pins
void initMotors() {
  pinMode(A1_EN, OUTPUT);
  pinMode(A1_IN1, OUTPUT);
  pinMode(A1_IN2, OUTPUT);

  pinMode(A2_EN, OUTPUT);
  pinMode(A2_IN1, OUTPUT);
  pinMode(A2_IN2, OUTPUT);

  digitalWrite(A1_EN, HIGH);
  digitalWrite(A2_EN, HIGH);
}

// Control a specific motor
void controlMotor(const String& motor, MotorState state, MotorDirection direction) {
  int in1, in2;

  if (motor == "A1") {
    in1 = A1_IN1;
    in2 = A1_IN2;
  } else if (motor == "A2") {
    in1 = A2_IN1;
    in2 = A2_IN2;
  } else {
    Serial.println("Error: Unknown motor");
    return;
  }

  if (state == OFF) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    return;
  }

  if (direction == LEFT) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (direction == RIGHT) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

// Process a text-based command
void processCommand(const String& command) {
  String motor, action, direction;
  int firstSpace = command.indexOf(' ');
  int secondSpace = command.indexOf(' ', firstSpace + 1);

  if (firstSpace == -1) return;

  motor = command.substring(0, firstSpace);
  action = (secondSpace == -1) ? command.substring(firstSpace + 1) 
                               : command.substring(firstSpace + 1, secondSpace);
  direction = (secondSpace == -1) ? "" : command.substring(secondSpace + 1);

  action.toLowerCase();
  direction.toLowerCase();

  if (action == "off") {
    controlMotor(motor, OFF, STOP);
  } else if (action == "on") {
    if (direction == "left") {
      controlMotor(motor, ON, LEFT);
    } else if (direction == "right") {
      controlMotor(motor, ON, RIGHT);
    } else {
      Serial.println("Error: Invalid direction");
    }
  } else {
    Serial.println("Error: Invalid action");
  }
}

#endif
