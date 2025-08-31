#include "Variables.h"
#include "Metodos.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  leerLDR();
  mostrarLDR();
  delay(1000); // 1 segundo entre lecturas
}
