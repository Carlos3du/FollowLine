void forcaMotor(int motorE, int motorD) {
  analogWrite(ENA, abs(motorE));
  if(motorE >= 0) {
    digitalWrite(IN1, HIGH);
  }else {
    digitalWrite(IN2, LOW);
  }

  analogWrite(ENB, abs(motorD));
  if(motorD >= 0) {
    digitalWrite(IN3, HIGH);
  }else {
    digitalWrite(IN4, LOW);
  }
}
