void setupConfig(){
  SPIFFS.begin(true);
  
  deleteFile(SPIFFS, filePath);
  listDir(SPIFFS, "/",1);
  delay(2000);
  checkConfig();
}

void createJson(){
  doc["name"] = "Hydroponic IOT";
  doc["version"] = "1.0.0";
  doc["configured"] = false;
  doc["type"] = "leafy";  //leafy, fruit, vegitable
  doc["state"] = "initial"; //initial, growth
  doc["temp"] = 25.0;
  doc["tds"] = 0.0;
  doc["ph"] = 0.0;
  doc["startDosing"] = false;

  String json;
  serializeJson(doc, json);
  writeFile(SPIFFS, filePath, json.c_str());
}

void checkConfig(){
  Serial.println("checking for config file...");
  
  String data = readFile(SPIFFS, filePath);
  if(!SPIFFS.exists(filePath) || data == ""){
    Serial.println("Config File not found!");
    createJson();
  }
  else if(data != ""){
    Serial.println("Config Data Found...");
    String value = data;
    deserializeJson(doc, value);
  }  

  if(doc["configured"]) Serial.println("System Configured...");
  else Serial.println("System Not Configured!");
}

void updateJson(JsonDocument data){
  JsonObject obj = data.as<JsonObject>();
  
  for(JsonPair itr: obj){
    doc[itr.key()] = itr.value();
  }   
  String json;
  serializeJson(doc, json); 
  writeFile(SPIFFS, filePath, json.c_str()); 
}

void printJson(){
  String json;
  serializeJsonPretty(doc, json);
  Serial.println(json.c_str());
  
}

