#ifndef VARIABLES_H
#define VARIABLES_H

// --- Pines ---
const int PIN_CONTACT = 2;         // Botón / Sensor de contacto
const int PIN_PHOTO_ANALOG = A0;   // Fotoresistencia analógica
const int PIN_PHOTO_DIGITAL = 3;  // Fotoresistencia digital (umbral)
const int PIN_TEMP = A2;           // LM35
const int PIN_INFRARED = A3;        // Sensor infrarrojo digital

// --- Umbrales ---
const int PHOTO_THRESHOLD = 512;   // Para convertir fotoresistencia a digital

// --- Variables globales ---
int estadoContact = 0;
int estadoPhotoDigital = 0;
int valorPhotoAnalog = 0;
int valorPhotoDigital = 0;
float temperaturaC = 0;
int estadoInfrared = 0;
float distancia = 0;

#endif
