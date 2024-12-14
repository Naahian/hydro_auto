const char* ssid = "ESP32_AP";      // Network SSID
const char* password = "12345678"; 

void handleJSONRequest() {
  // Create a sample JSON object
  String json;
  serializeJson(doc, json);

  // Send JSON response
  server.send(200, "application/json", json);
}

void setupWifiAP(){  
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP()); // Print the IP address of the AP
  // Define the JSON endpoint
  server.on("/data", handleJSONRequest);
  // Start the server
  server.begin();
  Serial.println("Server Started");

}



String sendJson(){
  String val;
  serializeJson(doc, val);
  return val;
}


// void setupWifiSTA(char* ssid, char* password){
//   WiFi.begin(ssid, password);

//   while(WiFi.status() != WL_CONNECTED){
//     delay(1000);
//     Serial.print(".");
//   }

//   Serial.println();
//   Serial.println("WiFi connected..!");
//   Serial.print("Local IP: ");  Serial.println(WiFi.localIP());
//   //TODO: handle error for disconnection, invalid ssid, invalid pass
// }