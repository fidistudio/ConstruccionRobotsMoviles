
const int EncoderA1 = 2; 
const int EncoderA2 = 3; 

volatile int contadorA1 = 0; 
volatile int contadorA2 = 0; 

void setup(){
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(EncoderA1), ContadorA1, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderA2), ContadorA2, RISING);
}

void loop(){
  Serial.print("A1: ");
  Serial.println(contadorA1);
  Serial.print("A2: "); 
  Serial.println(contadorA2);
  delay(100); // agrega un pequeño delay para no saturar el Serial
}

// Las funciones de interrupción deben ser lo más cortas posible
void ContadorA1(){
  contadorA1++;
}

void ContadorA2(){
  contadorA2++;
}
