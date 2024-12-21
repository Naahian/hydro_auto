#define ADC_RESOLUTION 4095 // ESP32 ADC resolution (12-bit)
#define VREF 3.3 // Reference phVoltage for ESP32 ADC
#define PH_NEUTRAL_VOLTAGE 2.5 // Voltage at pH 7 (calibrated value)
#define PH_SCALE -3.0 // Voltage change per pH unit (approximation)

float phVoltage;

void readPH() {
  int rawValue = analogRead(PH_PIN); // Read sensor voltage
  phVoltage = rawValue * (VREF / ADC_RESOLUTION);
  pH = 7.0 + ((PH_NEUTRAL_VOLTAGE - phVoltage) / PH_SCALE); // Calculate pH

  //change status
  status["PH"] = pH;
}
 

void printPH(){
  Serial.print("Raw Value: "); 
  Serial.println(analogRead(PH_PIN)); 
  
  Serial.print("V: ");
  Serial.print(phVoltage, 2);
  Serial.print(" V, ");

  Serial.print("pH: ");
  Serial.println(pH, 2);   

}