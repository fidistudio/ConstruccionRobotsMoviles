const int VelocidadA1 = 5; //ENA1
const int VelocidadA2 = 6; //ENA2 
const int DireccionA1 = 3;
const int DireccionA2 = 4;
String serialCommand = "";

void setup(){
  Serial.begin(9600);
  pinMode(VelocidadA1, OUTPUT);
  pinMode(VelocidadA2, OUTPUT); 
  pinMode(DireccionA1, OUTPUT); 
  pinMode(DireccionA2, OUTPUT);
  Serial.println("Sistema listo. Ingresa comandos:");
  Serial.println("Mensaje tipo: A1 speed 255"); 
  Serial.println("A2 speed -255");

}

void loop(){
  HandleSerial();
}

void HandleSerial(){
  if(Serial.available()){
    char c = Serial.read(); 

    if (c == '\n' || c == '\r'){
      serialCommand.trim();
      if (serialCommand.length() > 0){
        processCommand(serialCommand);
      }
      serialCommand = "";
    } else {
      serialCommand += c;
    }
  }
}

void processCommand(const String& command){
  String motorID, keyword, value; 
  int firstSpace = command.indexOf(' '); 
  int secondSpace = command.indexOf(' ', firstSpace + 1);

  if (firstSpace == -1 || secondSpace == -1){
    Serial.println("Error: comando inválido");
    return;
  }

  motorID = command.substring(0, firstSpace);
  motorID.toUpperCase();
  keyword = command.substring(firstSpace + 1, secondSpace);
  value = command.substring(secondSpace + 1);
  value.trim();

  int speedValue = value.toInt();

  ApplyPWM(motorID, speedValue);
}

void ApplyPWM(const String& motorID, int speedValue){
  if (motorID == "A1"){
    if (speedValue >= 0 && speedValue <= 255){
      analogWrite(VelocidadA1, abs(speedValue)); 
      digitalWrite(DireccionA1, HIGH);
    }else if (speedValue < 0 && speedValue >= -255){
      analogWrite(VelocidadA1, abs(speedValue)); 
      digitalWrite(DireccionA1, LOW);
    }else{
      Serial.println("Invalid speed value, -255<speed<255");
    }
  }else if(motorID == "A2"){ 
    if (speedValue >= 0 && speedValue <= 255){
      analogWrite(VelocidadA2, abs(speedValue)); 
      digitalWrite(DireccionA2, HIGH);
    }else if (speedValue < 0 && speedValue >= -255){
      analogWrite(VelocidadA2, abs(speedValue)); 
      digitalWrite(DireccionA2, LOW);
    }else{
      Serial.println("Invalid speed value, -255<speed<255");
    }
  }else {
    Serial.println("Unknown motorID, please type A1 or A2"); 
  }
}
