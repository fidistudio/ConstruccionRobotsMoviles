#include <Arduino.h>
#include "MotorPWM.h"
#include "DifferentialDrive.h"
#include "LightSensorArray.h"

// === Pines ===
constexpr int ENCODER_LEFT_PIN  = 2;
constexpr int ENCODER_RIGHT_PIN = 3;

constexpr int LEFT_SPEED_PIN  = 5;
constexpr int LEFT_DIR_PIN    = 4;
constexpr int RIGHT_SPEED_PIN = 6;
constexpr int RIGHT_DIR_PIN   = 7;

constexpr int LEFT_CONTACT_PIN = 9;
constexpr int RIGHT_CONTACT_PIN = 8;

constexpr int LIGHT_THRESHOLD = 800;

// === Sensores Contacto ===
ContactSensor contactLeft(LEFT_CONTACT_PIN, false);
ContactSensor contactRight(RIGHT_CONTACT_PIN, false);

// === Motores ===
MotorPWM leftMotor(LEFT_SPEED_PIN, LEFT_DIR_PIN);
MotorPWM rightMotor(RIGHT_SPEED_PIN, RIGHT_DIR_PIN);

// === Sensores de luz ===
LightSensorArray sensorArray(LIGHT_THRESHOLD);

// === Drive ===
DifferentialDrive::Params P{
  .wheelRadiusLeft  = 0.04269f / 2.0f,
  .wheelRadiusRight = 0.04415f / 2.0f,
  .wheelBase        = 0.09790f,
  .ticksPerRev      = 700,
  .duty             = 100
};

DifferentialDrive drive(leftMotor, rightMotor, contactLeft, contactRight, P);

// ISR
void onLeftEncoderTick()  { drive.onLeftTick(); }
void onRightEncoderTick() { drive.onRightTick(); }

// === Macros de movimiento ===
float AVANCE = 0.05;  // Metros
float GIRO   = 45;    // Grados

#define ADELANTE  drive.moveRobot( AVANCE,  0.0f)
#define ATRAS     drive.moveRobot(-AVANCE,  0.0f)
#define GIRO_IZQ  drive.moveRobot( 0.0f,   +GIRO)
#define GIRO_DER  drive.moveRobot( 0.0f,   -GIRO)
#define ALTO      drive.stop()

void setup() {
  Serial.begin(9600);
  drive.begin();
  sensorArray.begin();

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_PIN),  onLeftEncoderTick,  RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_PIN), onRightEncoderTick, RISING);

  Serial.println(F("FSM + DifferentialDrive listos."));
}

void loop() {
  sensorArray.readSectors();
  static int estado = 0;
  uint8_t brightest = sensorArray.getBrightestSector();

  switch (estado) {

    case 0:
      if (sensorArray.hasArrivedToDestination()) {
        estado = 0;
        ALTO;
        Serial.println("ALTO");
      } 
      else {
        estado = 1;
        ADELANTE;
        Serial.println("ADELANTE");
      }
      break;


    case 1:
      if (brightest == 3) {
        estado = 3;
        ADELANTE;
        Serial.println("ADELANTE");
      } 
      else if (brightest == 2) {
        estado = 2;
        ADELANTE;
        Serial.println("ADELANTE");
      } 
      else if (brightest == 1) {
        estado = 3;
        GIRO_IZQ;
        Serial.println("GIRO IZQUIERDA");
      } 
      else if (brightest == 0) {
        estado = 2;
        GIRO_DER;
        Serial.println("GIRO DERECHA");
      }
      break;


    case 2:
      estado = 0;
      GIRO_DER;
      Serial.println("GIRO DERECHA");
      break;

    case 3:
      estado = 0;
      GIRO_IZQ;
      Serial.println("GIRO IZQUIERDA");
      break;

    default:
      estado = 0;
      ALTO;
      Serial.println("ESTADO INVALIDO, DETENIENDO");
      break;
  }
}
