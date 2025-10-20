#include <MotorPWM.h>

// Pines para cada motor
const uint8_t A1_EN  = 5;  // PWM
const uint8_t A1_IN1 = 8;
const uint8_t A1_IN2 = 3;

const uint8_t A2_EN  = 6;  // PWM
const uint8_t A2_IN1 = 4;
const uint8_t A2_IN2 = 7;

// Instancias
MotorPWM motorA1(A1_EN, A1_IN1, A1_IN2);
MotorPWM motorA2(A2_EN, A2_IN1, A2_IN2);

String serialCommand = "";

// ====================================================
//  SETUP
// ====================================================
void setup() {
  Serial.begin(9600);
  motorA1.begin();
  motorA2.begin();
  Serial.println("Sistema listo. Ingresa comandos:");
  Serial.println("Ejemplo:  A1 forward 200");
  Serial.println("          A2 stop");
}

// ====================================================
//  LOOP
// ====================================================
void loop() {
  HandleSerial();
}

// ====================================================
//  FUNCION: HandleSerial
// ====================================================
void HandleSerial() {
  if (Serial.available()) {
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
}

// ====================================================
//  FUNCION: processCommand
// ====================================================
void processCommand(const String& command) {
  String motorID, action, speedStr;
  int firstSpace = command.indexOf(' ');
  int secondSpace = command.indexOf(' ', firstSpace + 1);

  if (firstSpace == -1) {
    Serial.println("Error: comando inválido.");
    return;
  }

  motorID = command.substring(0, firstSpace);
  action = (secondSpace == -1) ? command.substring(firstSpace + 1)
                               : command.substring(firstSpace + 1, secondSpace);
  speedStr = (secondSpace == -1) ? "" : command.substring(secondSpace + 1);

  action.toLowerCase();
  motorID.toUpperCase();

  int speed = speedStr.length() > 0 ? speedStr.toInt() : 0;
  speed = constrain(speed, 0, 255);

  // Seleccionar motor
  MotorPWM* motor = nullptr;
  if (motorID == "A1") motor = &motorA1;
  else if (motorID == "A2") motor = &motorA2;
  else {
    Serial.println("Error: motor desconocido (usa A1 o A2).");
    return;
  }

  // Ejecutar acción
  if (action == "forward") {
    motor->forward(speed);
    Serial.print(motorID); Serial.print(" → FORWARD "); Serial.println(speed);
  }
  else if (action == "backward") {
    motor->backward(speed);
    Serial.print(motorID); Serial.print(" → BACKWARD "); Serial.println(speed);
  }
  else if (action == "stop") {
    motor->stop();
    Serial.print(motorID); Serial.println(" → STOP");
  }
  else {
    Serial.println("Error: acción inválida (usa forward, backward o stop).");
  }
}
