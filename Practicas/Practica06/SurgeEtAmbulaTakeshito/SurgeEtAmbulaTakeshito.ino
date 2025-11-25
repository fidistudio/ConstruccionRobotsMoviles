#include <Arduino.h>
#include "MotorPWM.h"
#include "IRSensor.h"
#include "ContactSensor.h"
#include "DifferentialDrive.h"
#include "LightSensorArray.h"

// === Pines ===
constexpr int ENCODER_LEFT_PIN  = 2;
constexpr int ENCODER_RIGHT_PIN = 3;

constexpr int LEFT_SPEED_PIN  = 5;
constexpr int LEFT_DIR_PIN    = 4;
constexpr int RIGHT_SPEED_PIN = 6;
constexpr int RIGHT_DIR_PIN   = 7;

constexpr int IR_LEFT_PIN = A3;
constexpr int IR_RIGHT_PIN = A5;
constexpr int IR_FRONT_PIN = A4;
constexpr int IR_LEFT_THRESHOLD = 500;
constexpr int IR_RIGHT_THRESHOLD = 500;
constexpr int IR_FRONT_THRESHOLD = 600;

constexpr int LEFT_CONTACT_PIN = 9;
constexpr int RIGHT_CONTACT_PIN = 8;

constexpr int LIGHT_THRESHOLD = 800;

// === Sensores IR ===
IRSensor irLeft(IR_LEFT_PIN, IR_LEFT_THRESHOLD);
IRSensor irRight(IR_RIGHT_PIN, IR_RIGHT_THRESHOLD);
IRSensor irFront(IR_FRONT_PIN, IR_FRONT_THRESHOLD);

// === Sensores Contacto ===
ContactSensor contactLeft(LEFT_CONTACT_PIN, false);
ContactSensor contactRight(RIGHT_CONTACT_PIN, false);

// === Motores ===
MotorPWM leftMotor(LEFT_SPEED_PIN, LEFT_DIR_PIN);
MotorPWM rightMotor(RIGHT_SPEED_PIN, RIGHT_DIR_PIN);

// === Sensor de luz ===
LightSensorArray sensorArray(LIGHT_THRESHOLD);

// === Drive ===
DifferentialDrive::Params P{
  .wheelRadiusLeft  = 0.04269f / 2.0f,
  .wheelRadiusRight = 0.04415f / 2.0f,
  .wheelBase        = 0.09790f,
  .ticksPerRev      = 700,
  .duty             = 100
};

DifferentialDrive drive(leftMotor, rightMotor,contactLeft, contactRight, P);

// === ISR trampolines ===
void onLeftEncoderTick()  { drive.onLeftTick(); }
void onRightEncoderTick() { drive.onRightTick(); }

// === Sensor handler ===
float shs(char* /*sensor*/, int num) {
  bool obs = false;
  if (num == 1) {
    irLeft.update();
    contactLeft.update();
    obs = irLeft.isObstacleDetected() || contactLeft.isObstacleDetected();
  } else if (num ==2) {
    irRight.update();
    contactRight.update();
    obs = irRight.isObstacleDetected() || contactRight.isObstacleDetected();
  } else {
    irFront.update();
    obs = irFront.isObstacleDetected();
  }
  return obs ? 1.0f : 0.0f;
}

// === Macros de movimiento ===
float AVANCE = 0.05;  // Metros
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
  sensorArray.begin();

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_PIN),  onLeftEncoderTick,  RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_PIN), onRightEncoderTick, RISING);

  // drive.setDebug(true);
  Serial.println(F("FSM + DifferentialDrive listos."));
}

// === Loop principal ===
void loop() {
sensorArray.readSectors();
  static int estado = 1;
  uint8_t brightest = sensorArray.getBrightestSector();

  float Si = shs((char*)"contact", 1);
  float Sd = shs((char*)"contact", 2);
  float Sf = shs((char*)"contact", 3);

  int obstacle = 0;
  if (Sf == 1) obstacle = 3;
  if (Si == 1 && Sd == 0) obstacle = 2; 
  if (Sd == 1 && Si == 0) obstacle = 1;
  
  switch (estado) {
    
    case 1:
      if (sensorArray.hasArrivedToDestination()) {
        estado = 1; 
        ALTO; 
        Serial.println("ALTO");
      }
      else {
        estado = 2; 
        ADELANTE; 
        Serial.println("ADELANTE"); 
      }
    break; 

    case 2:
      if (obstacle == 3)            { estado = 7;  ALTO;      Serial.println("ALTO"); }
      else if (obstacle == 2)       { estado = 5;  ALTO;  Serial.println("ALTO"); }
      else if (obstacle == 1)       { estado = 3;  ALTO;      Serial.println("ALTO"); }
      else if (obstacle == 0)       { estado = 14;  ADELANTE;      Serial.println("ADELANTE"); }
      break;


    case 3:  estado = 4;  ATRAS;     Serial.println("ATRAS");     break;
    case 4:  estado = 1;  GIRO_IZQ;  Serial.println("IZQUIERDA"); break;
    case 5:  estado = 6;  ATRAS;     Serial.println("ATRAS");     break;
    case 6:  estado = 1;  GIRO_DER;  Serial.println("DERECHA");   break;
    case 7:  estado = 8;  ATRAS;     Serial.println("ATRAS");     break;
    case 8:  estado = 9;  GIRO_IZQ;  Serial.println("IZQUIERDA"); break;
    case 9:  estado = 10; GIRO_IZQ;  Serial.println("IZQUIERDA"); break;
    case 10: estado = 11; ADELANTE;  Serial.println("ADELANTE");  break;
    case 11: estado = 12; ADELANTE;  Serial.println("ADELANTE");  break;
    case 12: estado = 13; GIRO_DER;  Serial.println("DERECHA");   break;
    case 13: estado = 1;  GIRO_DER;  Serial.println("DERECHA");   break;

    case 14:
      if (brightest == 3) {
        estado = 4;
        ADELANTE;
        Serial.println("ADELANTE");
      } 
      else if (brightest == 2) {
        estado = 6;
        ADELANTE;
        Serial.println("ADELANTE");
      } 
      else if (brightest == 1) {
        estado = 4;
        GIRO_IZQ;
        Serial.println("GIRO IZQUIERDA");
      } 
      else if (brightest == 0) {
        estado = 6;
        GIRO_DER;
        Serial.println("GIRO DERECHA");
      }
      break;
  }

  delay(40);
}
