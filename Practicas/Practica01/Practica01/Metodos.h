#ifndef METODOS_H
#define METODOS_H

#include "Variables.h"

// Función para leer y mostrar estado del botón
void leerBoton() {
  estadoBoton = digitalRead(PIN_BOTON);

  if (estadoBoton == HIGH) {
    Serial.println("Botón presionado");
  } else {
    Serial.println("0");   // Muestra 0 si no hay señal
  }

  delay(200); // Para evitar saturar el monitor serial
}

#endif
