// // INA291 I2C Address (Check your datasheet or setup)
// #define INA291_I2C_ADDRESS 0x40 

// // Register addresses (refer to the INA291 datasheet)
// #define CONFIG_REGISTER 0x00
// #define CURRENT_REGISTER 0x04
// #define CALIBRATION_REGISTER 0x05

// // Variables for I2C communication
// float shunt_resistance = 0.01; // Shunt resistor value in ohms (10 mΩ)
// float current_lsb = 0.001;     // Current LSB in Amperes (1 mA)
// float voltage = 12.0; 

// // Function to initialize the INA291
// void setupINA() {
//   Wire.begin(); // Start I2C communication

//   // Optional: Configure the INA291 settings via registers
//   configureINA291();

//   Serial.println("INA291 DC Power Measurement Initialized");
// }

// // Function to configure the INA291 registers
// void configureINA291() {
//   Wire.beginTransmission(INA291_I2C_ADDRESS);
//   Wire.write(CONFIG_REGISTER);  // Point to the config register
//   Wire.write(0x00);             // MSB (default configuration example)
//   Wire.write(0x01);             // LSB
//   Wire.endTransmission();

//   // Set the calibration register (optional for scaling)
//   Wire.beginTransmission(INA291_I2C_ADDRESS);
//   Wire.write(CALIBRATION_REGISTER);
//   Wire.write(0x00);             // MSB (example value, configure as needed)
//   Wire.write(0x80);             // LSB
//   Wire.endTransmission();
// }

// // Function to read the current value from INA291
// float readINA() {
//   Wire.beginTransmission(INA291_I2C_ADDRESS);
//   Wire.write(CURRENT_REGISTER); // Point to the current register
//   Wire.endTransmission();
  
//   Wire.requestFrom(INA291_I2C_ADDRESS, 2); // Request 2 bytes
//   if (Wire.available() == 2) {
//     uint16_t rawData = (Wire.read() << 8) | Wire.read(); // Combine MSB and LSB
//     float current = rawData * current_lsb; // Calculate current (Amperes)
//     return current;
//   } else {
//     Serial.println("Error: Could not read data");
//     return 0.0;
//   }
// }

// // Function to calculate power in watts
// float calculatePower(float current) {
//   return current * voltage; // Power = Current * Voltage
// }
