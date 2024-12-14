void setupConfig(){
  SPIFFS.begin(true);
  checkConfig();
  delay(2000);
}

void createConfig(){
  config["name"] = "Hydroponic IOT";
  config["version"] = "1.0.0";
  config["configured"] = false;
  config["type"] = "leafy";  //leafy, fruit, vegitable
  config["state"] = "initial"; //initial, growth
  config["temp"] = 25.0;
  config["tds"] = 0.0;
  config["ph"] = 0.0;
  config["startDosing"] = false;

  String json;
  serializeJson(config, json);
  writeFile(SPIFFS, filePath, json.c_str());
}

void checkConfig(){
  Serial.println("checking for config file...");
  
  String data = readFile(SPIFFS, filePath);
  if(!SPIFFS.exists(filePath) || data == ""){
    Serial.println("Config File not found!");
    createConfig();
  }
  else if(data != ""){
    Serial.println("Config Data Found...");
    String value = data;
    deserializeJson(config, value);
  }  

  if(config["configured"]) Serial.println("System Configured...");
  else Serial.println("System Not Configured!");
}

void updateConfig(JsonDocument data){
  JsonObject obj = data.as<JsonObject>();
  
  for(JsonPair itr: obj){
    config[itr.key()] = itr.value();
  }   
  String json;
  serializeJson(config, json); 
  writeFile(SPIFFS, filePath, json.c_str()); 
}

void printConfig(){
  String json;
  serializeJsonPretty(config, json);
  Serial.println(json.c_str());
  
}

