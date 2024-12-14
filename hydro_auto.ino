#include "FS.h"
#include "SPIFFS.h"
#include "ArduinoJson.h"
#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// #include <ESP32Servo.h> // Include the ESP32Servo library


//DEFINE PINS
#define SERVO_PIN 23
#define configStatusLed 12
#define dosingLed 13
#define TDS_PIN 18 
#define PH_PIN 5
#define TEMP_PIN 15
#define PUMP_PIN 34

//CONSTANTS
#define VREF 3.3           
#define ADC_RESOLUTION 4095 
const char* filePath = "/data.json";
// Servo myServo;
JsonDocument config;
JsonDocument status;
WebServer server(80);


//Variables
float Temp = 0;

void setup() {
    // myServo.attach(SERVO_PIN); // Attach the servo object to the defined pin
  setupHardware();  
  setupConfig();
  setupWifiAP();  
  
  printConfig();
  delay(2000);
}

void loop() {
  // read sensors
  // readTemp();

  // take action
  server.handleClient();
 
  //log data
  status["Watt"] = random(300);
  status["PH"] = random(14);
  status["EC"] = random(10);
  status["Temp"] = random(50);

  delay(500);
}


void setupHardware() {
  Serial.begin(9600);
  Serial.println("Setting up hardware...");

  pinMode(TDS_PIN, INPUT);
  pinMode(PH_PIN, INPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(configStatusLed, OUTPUT);
  pinMode(dosingLed, OUTPUT);
}

//---------------- others functions ----------------------


void fromInput(){
    if(Serial.available()){
    JsonDocument inputDoc;
    String input = Serial.readStringUntil('\n');
    
    if(input == "DELETE FILE") deleteFile(SPIFFS, filePath);
    else{
      deserializeJson(inputDoc, input);
      updateConfig(inputDoc);
    }
  } 

}

