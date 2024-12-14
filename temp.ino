OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);

void setupTemp()
{
  tempSensor.begin();
}

void readTemp(){ 
  tempSensor.requestTemperatures();
  Temp =  tempSensor.getTempCByIndex(0);
  // doc["temp"] = Temp;
}

void printTemp(){
  Serial.print("Celsius temperature: ");
  Serial.println(Temp); 
}
