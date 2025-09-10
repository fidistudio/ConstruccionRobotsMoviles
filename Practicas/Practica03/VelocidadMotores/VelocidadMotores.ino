#include "Variables.h"
#include "Metodos.h"

String comando = "";

void setup() {
  Serial.begin(9600);
  inicializarMotores();
  Serial.println("Sistema listo. Use: A1 speed 57 o A2 speed -82");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      comando.trim();
      if (comando.length() > 0) {
        procesarComando(comando);
      }
      comando = "";
    } else {
      comando += c;
    }
  }
}
