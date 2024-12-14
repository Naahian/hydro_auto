const char* ssid = "HYDRO_AUTO";      // Network SSID
const char* password = "12345678"; 

void handleJSONRequest() {

  String json;
  serializeJson(status, json);

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

  status["Temp"] = 30;
  status["EC"] = 2.2;
  status["PH"] = 1.1;
  status["Watt"] = 400;


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