#include "Variables.h"
#include "Metodos.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  leerTemperatura();
  mostrarTemperatura();
  delay(1000); // Espera 1 segundo entre lecturas
}
