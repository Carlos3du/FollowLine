//Andrew Kennedy
//15/09/22
//Leitura do sensor de refletância QTR-8RC, array de 8 sensores.

#include <QTRSensors.h>
QTRSensors qtr;
const byte sensorCount = 8;
int sensor[sensorCount];

void setup() {
  Serial.begin(9600);
  qtr.setTypeAnalog();           //Pinos analógicos do seguidor de linha
  qtr.setSensorPins((const byte[]){A0,A1,A2,A3,A4,A5,A6,A7}, sensorCount);
  qtr.setEmitterPin(3); //Pino do IR emissor
}

void loop() {
  //Leitura dos sensores e atribuição ao array
  qtr.read(sensor); 

  //0 = claro; 
  //1023 = escuro;
  for(byte i=0; i<sensorCount;i++) {
    Serial.print(sensor[i]);
    Serial.print('\t');
  }
  Serial.println();
  delay(300);
}
