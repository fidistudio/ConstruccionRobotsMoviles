#include "Variables.h"
#include "Metodos.h"

String command = "";

void setup() {
  Serial.begin(9600);
  initMotors();
  Serial.println("System ready. Enter commands.");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      command.trim();
      if (command.length() > 0) {
        processCommand(command);
      }
      command = "";
    } else {
      command += c;
    }
  }
}
