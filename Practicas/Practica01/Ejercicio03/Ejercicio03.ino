#include "Variables.h"
#include "Metodos.h"

void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
}

void loop() {
  leerLDR();
  mostrarLDR();
  controlarLED();
  delay(1000); // 1 segundo entre lecturas
}
