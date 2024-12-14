
void startDosing(){
  digitalWrite(PUMP_PIN, HIGH);
  delay(1000);
  digitalWrite(PUMP_PIN, LOW);
}