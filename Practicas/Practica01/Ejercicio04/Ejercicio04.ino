#include "Variables.h"
#include "Metodos.h"

void setup() {
  Serial.begin(9600);
  pinMode(pinComparador, INPUT);
  pinMode(pinLED, OUTPUT);
}

void loop() {
  leerComparador();
  mostrarEstadoLuz();
  //controlarLED();
  delay(500); // medio segundo entre lecturas
}