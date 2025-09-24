#ifndef VARIABLES_H
#define VARIABLES_H

// Pin definitions for motor A1
const int A1_EN = 1;    // Enable pin A1 (SN754410, pin 1)
const int A1_IN1 = 2;   // Input 1A (SN754410 pin 2)
const int A1_IN2 = 3;   // Input 2A (SN754410 pin 7)

// Pin definitions for motor A2
const int A2_EN = 9;    // Enable pin A2 (SN754410, pin 9)
const int A2_IN1 = 10;  // Input 3A (SN754410 pin 10)
const int A2_IN2 = 11;  // Input 4A (SN754410 pin 15)

// Motor constants
enum MotorState {OFF, ON};
enum MotorDirection {LEFT, RIGHT, STOP};

#endif
