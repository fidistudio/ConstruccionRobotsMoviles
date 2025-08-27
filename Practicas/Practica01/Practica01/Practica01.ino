#include "Variables.h"
#include "Metodos.h"

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BOTON, INPUT);   // Botón con resistencia en pulldown externa
}

void loop() {
  leerBoton();   // Método separado en metodos.h
}
