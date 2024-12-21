void startDosing(){
  digitalWrite(PUMP_PIN, HIGH);
  delay(1000);  //assuming 1000ms pumps 5ml dose
  digitalWrite(PUMP_PIN, LOW);
}

