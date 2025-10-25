
#include <Arduino.h>
#include "MotorPWM.h"
#include "IRSensor.h"
#include "DifferentialDrive.h"

// === Pines ===
constexpr int ENCODER_LEFT_PIN  = 2;
constexpr int ENCODER_RIGHT_PIN = 3;

constexpr int LEFT_SPEED_PIN  = 5;
constexpr int LEFT_DIR_PIN    = 7;
constexpr int RIGHT_SPEED_PIN = 6;
constexpr int RIGHT_DIR_PIN   = 8;

constexpr int IR_LEFT_PIN = A0;
constexpr int IR_RIGHT_PIN = A1;
constexpr int IR_LEFT_THRESHOLD = 300;
constexpr int IR_RIGHT_THRESHOLD = 300;

// === Sensores IR ===
IRSensor irLeft(IR_LEFT_PIN, IR_LEFT_THRESHOLD);
IRSensor irRight(IR_RIGHT_PIN, IR_RIGHT_THRESHOLD);

// === Motores ===
MotorPWM leftMotor(LEFT_SPEED_PIN, LEFT_DIR_PIN);
MotorPWM rightMotor(RIGHT_SPEED_PIN, RIGHT_DIR_PIN);

// === Drive ===
DifferentialDrive::Params P{
  .wheelRadiusLeft  = 0.04269f / 2.0f,
  .wheelRadiusRight = 0.04415f / 2.0f,
  .wheelBase        = 0.09790f,
  .ticksPerRev      = 700,
  .duty             = 80
};

DifferentialDrive drive(leftMotor, rightMotor, P);

// === ISR trampolines ===
void onLeftEncoderTick()  { drive.onLeftTick(); }
void onRightEncoderTick() { drive.onRightTick(); }

// === Sensor handler ===
float shs(char* /*sensor*/, int num) {
  bool obs = false;
  if (num == 1) {
    irLeft.update();
    obs = irLeft.isObstacleDetected();
  } else {
    irRight.update();
    obs = irRight.isObstacleDetected();
  }
  return obs ? 1.0f : 0.0f;
}

// === Macros de movimiento ===
float AVANCE = 0.10f;  // Metros
float GIRO   = 45;     // Grados

#define ADELANTE  drive.moveRobot( AVANCE,  0.0f)
#define ATRAS     drive.moveRobot(-AVANCE,  0.0f)
#define GIRO_IZQ  drive.moveRobot( 0.0f,   +GIRO)
#define GIRO_DER  drive.moveRobot( 0.0f,   -GIRO)
#define ALTO      drive.stop()

// === Setup ===
void setup() {
  Serial.begin(9600);
  drive.begin();

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_PIN),  onLeftEncoderTick,  RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_PIN), onRightEncoderTick, RISING);

  // drive.setDebug(true);
  Serial.println(F("FSM + DifferentialDrive listos."));
}

// === Loop principal ===
void loop() {
  static int estado = 0;

  float Si = shs((char*)"contact", 1);
  float Sd = shs((char*)"contact", 2);

  switch (estado) {
    case 0:
      if (Si == 0 && Sd == 0)       { estado = 0;  ADELANTE;  Serial.println("ADELANTE"); }
      else if (Si == 0 && Sd == 1)  { estado = 1;  ALTO;      Serial.println("ALTO"); }
      else if (Si == 1 && Sd == 0)  { estado = 3;  ALTO;      Serial.println("ALTO"); }
      else                          { estado = 5;  ALTO;      Serial.println("ALTO"); }
      break;

    case 1:  estado = 2;  ATRAS;     Serial.println("ATRAS");     break;
    case 2:  estado = 0;  GIRO_IZQ;  Serial.println("IZQUIERDA"); break;
    case 3:  estado = 4;  ATRAS;     Serial.println("ATRAS");     break;
    case 4:  estado = 0;  GIRO_DER;  Serial.println("DERECHA");   break;
    case 5:  estado = 6;  ATRAS;     Serial.println("ATRAS");     break;
    case 6:  estado = 7;  GIRO_IZQ;  Serial.println("IZQUIERDA"); break;
    case 7:  estado = 8;  GIRO_IZQ;  Serial.println("IZQUIERDA"); break;
    case 8:  estado = 9;  ADELANTE;  Serial.println("ADELANTE");  break;
    case 9:  estado = 10; ADELANTE;  Serial.println("ADELANTE");  break;
    case 10: estado = 11; GIRO_DER;  Serial.println("DERECHA");   break;
    case 11: estado = 0;  GIRO_DER;  Serial.println("DERECHA");   break;
  }

  delay(40);
}
