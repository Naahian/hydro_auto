#include "FS.h"
#include "SPIFFS.h"
#include "ArduinoJson.h"
#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP32Servo.h>


//DEFINE PINS
#define SERVO_PIN 23
#define configStatusLed 12
#define dosingLed 13
#define SERVO_PIN 9
#define TDS_PIN 13
#define PH_PIN 12
#define TEMP_PIN 14 
#define PUMP_PIN 34

//CONSTANTS
#define VREF 3.3           
#define ADC_RESOLUTION 4095 
#define filePath "/data.json"
JsonDocument config;  // to store configuration for specific plant
JsonDocument status;  // to send status data of sensor to webserver
WebServer server(80);
Servo myServo;


//Variables
float Temp = 0;
float pH = 0; 
float tds = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 2000;

void setup() {
  setupHardware();  
  setupConfig();
  setupWifiSTA("NahianGalaxy", "tree1234");  
  // setupWifiAP();
  // setupTDS();
  // setupTemp();
  //ph setup not needed

  printConfig();
  delay(2000);
}

void loop() {
  // unsigned long currentMillis = millis();
  
  // // read sensors      //sense for 5 seconds after every 5 seconds
  // myServo.write(90);   //servo with sensor board down
  // readTemp();
  // readTDS();
  // delay(1000);
  // // createRandomStatus();
  // myServo.write(0);   //servo with sensor board up

  // // take action
  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis;
  
   server.handleClient(); // Handle requests every 2 seconds, without blocking
  // }
  
  createRandomStatus();
//  createRandom
// log data
// printStatus();

  delay(500);
}


void setupHardware() {
  Serial.begin(9600);
  Serial.println("Setting up hardware...");

  myServo.attach(SERVO_PIN);
  pinMode(TDS_PIN, INPUT);
  pinMode(PH_PIN, INPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(configStatusLed, OUTPUT);
  pinMode(dosingLed, OUTPUT);
}





//---------------- for testing ----------------------

void printStatus(){
  String json;
  serializeJsonPretty(status, json);
  Serial.println(json.c_str());
}

void createRandomStatus(){
  status["Watt"] = random(300);
  status["PH"] = random(14);
  status["EC"] = random(10);
  status["Temp"] = random(50);
}

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

