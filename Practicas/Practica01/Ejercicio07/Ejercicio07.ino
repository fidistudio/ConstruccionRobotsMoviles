#include "Variables.h"
#include "Metodos.h"

void setup() {
    Serial.begin(9600);

    pinMode(pinComparador, INPUT);
    //pinMode(pinLED, OUTPUT);
    pinMode(pinPWMReferencia, OUTPUT);

    inicializarPWMReferencia();
}

void loop() {
    leerComparador();
    mostrarEstadoComparador();
    controlarLED();
    delay(100);
}
