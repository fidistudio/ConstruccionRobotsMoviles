#ifndef VARIABLES_H
#define VARIABLES_H

// Definición de pines para motor A1
const int A1_EN = 1;    // Pin habilitación A1 (SN754410, pin 1)
const int A1_IN1 = 2;   // Entrada 1A (pin 2 SN754410)
const int A1_IN2 = 3;   // Entrada 2A (pin 7 SN754410)

// Definición de pines para motor A2
const int A2_EN = 9;    // Pin habilitación A2 (SN754410, pin 9)
const int A2_IN1 = 10;  // Entrada 3A (pin 10 SN754410)
const int A2_IN2 = 11;  // Entrada 4A (pin 15 SN754410)

// Constantes de motores
enum EstadoMotor {OFF, ON};
enum DireccionMotor {LEFT, RIGHT, STOP};

#endif
