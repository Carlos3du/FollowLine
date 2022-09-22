/* Andrew Kennedy
 * 19/08/22
 * Leitura do sensor QTR-8A.
 * Calibração automática e movimentação por motores
*/

#include <QTRSensors.h>
QTRSensors qtr;

//Array de 8 sensores:
const byte sensorCount = 8;
int sensor[sensorCount];

//Shield para motores:
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENA 9
#define ENB 10
byte velocidade = 150;
byte velocidade2 = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  qtr.setTypeAnalog();           //Pinos do QTR-8A
  qtr.setSensorPins((const byte[]) {
    A0, A1, A2, A3, A4, A5, A6, A7
  }, sensorCount);
  qtr.setEmitterPin(3); //Pino do IR do array

  forcaMotor(-100, 100); //Girar para a esquerda
  for (byte i = 0; i < 40; i++) { //2s
    qtr.calibrate();//25ms
  }

  forcaMotor(100, -100); //Girar para a direita
  for (byte i = 0; i < 80; i++) { //4s
    qtr.calibrate();//25ms
  }
  forcaMotor(-100, 100);
  delay(2000);//2s

  forcaMotor(0, 0);
  delay(700);
}

void loop() {
  //0 = esquerda; 5000 direita; 2500 = linha centralizada.
  unsigned int leitura = qtr.readLineBlack(sensor);

  if (leitura > 2300 and leitura < 2700) {
    forcaMotor(velocidade, velocidade);
  } else if (leitura <= 2300) { //Girar para a esquerda
    velocidade2 = map(leitura, 0, 2300, 0, velocidade);
    forcaMotor(velocidade, velocidade2);
  } else if (leitura >= 2700) { //Girar para a direita
    velocidade2 = map(leitura, 0, 2300, velocidade, 0);
    forcaMotor(velocidade2, velocidade);
  }
}
