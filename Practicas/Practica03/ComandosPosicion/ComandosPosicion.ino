
#include "MotorPWM.h"

// ------------------- CONSTANTS -------------------
constexpr int ENCODER_LEFT_PIN = 2;
constexpr int ENCODER_RIGHT_PIN = 3;

constexpr int LEFT_SPEED_PIN = 5;
constexpr int LEFT_DIR_PIN = 7;
constexpr int RIGHT_SPEED_PIN = 6;
constexpr int RIGHT_DIR_PIN = 8;

constexpr int DUTY_CYCLE = 100;
constexpr float WHEEL_RADIUS_RIGHT = 0.04415/2; // meters
constexpr float WHEEL_RADIUS_LEFT = 0.04269/2;  // meters
constexpr float WHEEL_BASE = 0.09790;          // distance between wheels (m)
constexpr int TICKS_PER_REV = 700;


// ------------------- GLOBAL VARIABLES -------------------
volatile long leftEncoderCount = 0;
volatile long rightEncoderCount = 0;

// Último tiempo de tick (microsegundos)
volatile unsigned long lastLeftTickTime = 0;
volatile unsigned long lastRightTickTime = 0;

MotorPWM leftMotor(LEFT_SPEED_PIN, LEFT_DIR_PIN);
MotorPWM rightMotor(RIGHT_SPEED_PIN, RIGHT_DIR_PIN);

String serialCommand = "";

// ------------------- INTERRUPTS -------------------
void onLeftEncoderTick() {
    leftEncoderCount++;
}

void onRightEncoderTick() {
    rightEncoderCount++;
}

// ------------------- SETUP -------------------
void setup() {
  Serial.begin(9600);
  leftMotor.begin();
  rightMotor.begin();

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_PIN), onLeftEncoderTick, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_PIN), onRightEncoderTick, RISING);

  Serial.println("System ready. Enter commands:");
  Serial.println("Example: mv linear 0.1");
  Serial.println("         mv angular 45");
}

// ------------------- MAIN LOOP -------------------
void loop() {
  handleSerialInput();
}

// ------------------- SERIAL HANDLER -------------------
void handleSerialInput() {
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

// ------------------- COMMAND PROCESSOR -------------------
void processCommand(const String& command) {
  int firstSpace = command.indexOf(' ');
  int secondSpace = command.indexOf(' ', firstSpace + 1);

  if (firstSpace == -1 || secondSpace == -1) {
    Serial.println("Error: invalid command format.");
    return;
  }

  String keyword = command.substring(0, firstSpace);
  String motionType = command.substring(firstSpace + 1, secondSpace);
  motionType.toLowerCase();

  String valueStr = command.substring(secondSpace + 1);
  valueStr.trim();

  if (motionType == "linear") {
    moveLinear(valueStr.toFloat());
  } else if (motionType == "angular") {
    moveAngular(valueStr.toFloat());
  } else {
    Serial.println("Error: invalid motion type. Use 'linear' or 'angular'.");
  }
}

// ------------------- MOTION FUNCTIONS -------------------
void moveLinear(float distanceMeters) {
  resetEncoders();

  float goalTicksLeft = (abs(distanceMeters) * TICKS_PER_REV) / (2 * PI * WHEEL_RADIUS_LEFT);
  float goalTicksRight = (abs(distanceMeters) * TICKS_PER_REV) / (2 * PI * WHEEL_RADIUS_RIGHT);
  int direction = (distanceMeters >= 0) ? 1 : -1;

  Serial.println("----- LINEAR MOVE -----");
  Serial.print("Distancia (m): "); Serial.println(distanceMeters, 4);
  Serial.print("Ticks objetivo izquierda: "); Serial.println(goalTicksLeft, 2);
  Serial.print("Ticks objetivo derecha: "); Serial.println(goalTicksRight, 2);
  Serial.println("-----------------------");

  leftMotor.setSpeed(DUTY_CYCLE * direction);
  rightMotor.setSpeed(DUTY_CYCLE * direction);

  while (leftEncoderCount < goalTicksLeft && rightEncoderCount < goalTicksRight) {
    Serial.print("L: "); Serial.print(leftEncoderCount);
    Serial.print(" / "); Serial.print(goalTicksLeft);
    Serial.print(" | R: "); Serial.print(rightEncoderCount);
    Serial.print(" / "); Serial.println(goalTicksRight);
    delay(200); // Debug cada 200 ms
  }

  stopMotors();
  Serial.println("Movimiento lineal completado.");
}

void moveAngular(float angleDegrees) {
  resetEncoders();

  float angleRadians = abs(angleDegrees) * PI / 180.0f;
  float arcLength = (WHEEL_BASE / 2.0f) * angleRadians;

  float goalTicksLeft = (arcLength * TICKS_PER_REV) / (2 * PI * WHEEL_RADIUS_LEFT);
  float goalTicksRight = (arcLength * TICKS_PER_REV) / (2 * PI * WHEEL_RADIUS_RIGHT);
  int direction = (angleDegrees >= 0) ? 1 : -1;

  Serial.println("----- ANGULAR MOVE -----");
  Serial.print("Ángulo (°): "); Serial.println(angleDegrees, 2);
  Serial.print("Longitud de arco (m): "); Serial.println(arcLength, 4);
  Serial.print("Ticks objetivo izquierda: "); Serial.println(goalTicksLeft, 2);
  Serial.print("Ticks objetivo derecha: "); Serial.println(goalTicksRight, 2);
  Serial.println("-------------------------");

  leftMotor.setSpeed(DUTY_CYCLE * direction);
  rightMotor.setSpeed(-DUTY_CYCLE * direction);

  while (leftEncoderCount < goalTicksLeft && rightEncoderCount < goalTicksRight) {
    Serial.print("L: "); Serial.print(leftEncoderCount);
    Serial.print(" / "); Serial.print(goalTicksLeft);
    Serial.print(" | R: "); Serial.print(rightEncoderCount);
    Serial.print(" / "); Serial.println(goalTicksRight);
    delay(200);
  }

  stopMotors();
  Serial.println("Rotación completada.");
}

// ------------------- UTILITY FUNCTIONS -------------------
void resetEncoders() {
  noInterrupts();
  leftEncoderCount = 0;
  rightEncoderCount = 0;
  lastLeftTickTime = 0;
  lastRightTickTime = 0;
  interrupts();
}

void stopMotors() {
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
}
