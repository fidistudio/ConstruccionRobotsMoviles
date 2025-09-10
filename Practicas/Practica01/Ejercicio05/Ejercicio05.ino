#include "Variables.h"
#include "Metodos.h"

void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
}

void loop() {
    unsigned long currentTime = millis();

    if (currentTime - lastSampleTime >= SAMPLE_INTERVAL) {
        lastSampleTime = currentTime;

        int rawValue = leerValorSensor();
        float distancia = calcularDistancia(rawValue);
        mostrarDistancia(distancia);
    }
}
