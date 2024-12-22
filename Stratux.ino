//**********************************************************************
//********************Stratux Functions*********************************
//**********************************************************************


void connectToStratuxWifi() {
  Serial.println("Attempting to connect to Stratux WiFi...");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA); 
  WiFi.config(staticIP,gateway,subnet);
  WiFi.begin("Stratux", "");
  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 10000) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to Stratux WiFi");
    Serial.println("IP: " + WiFi.localIP().toString());
  } else {
    Serial.println("\nCould not connect to Stratux WiFi. Setting up Access Point...");
    WiFi.softAPConfig(staticIP,gateway,subnet);
    WiFi.softAP("Rebel_AP");
    Serial.print("Access Point IP address: ");
    Serial.println(WiFi.softAPIP());
    stratuxData.sEnabled = false;
    StaticJsonDocument<512> doc;
    doc["stratux"] = stratuxData.sEnabled;
    String jsonString;
    serializeJson(doc, jsonString);
    ws.textAll(jsonString);
  }
}


void fetchStratuxData() {
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to Stratux WiFi. Cannot fetch data.");
    return;
  }

  HTTPClient http;
  http.begin("http://192.168.10.1/getSituation");
  int httpCode = http.GET();
  
  if (httpCode == 200) {
    String payload = http.getString();

    // Allocate JSON doc. Adjust size as needed; 2048 is a guess.
    StaticJsonDocument<2048> doc; 
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      http.end();
      return;
    }

    // Extract Stratux values
    float gpsGroundSpeed = doc["GPSGroundSpeed"] | 0.0;
    float pitch = doc["AHRSPitch"] | 0.0;
    float roll = doc["AHRSRoll"] | 0.0;
    float heading = doc["AHRSGyroHeading"] | NAN;
    float slip = doc["AHRSSlipSkid"] | 0.0;
    float gForce = doc["AHRSGLoad"] | 0.0;

    // Check for invalid values (Stratux uses 3276.7 as invalid)
    if (pitch == 3276.7f) pitch = 0.0;
    if (roll == 3276.7f) roll = 0.0;
    if (heading == 3276.7f) heading = 0.0;
    if (slip == 3276.7f) slip = 0.0;
    if (gForce == 3276.7f) gForce = 0.0;

    // Assign to global struct
    stratuxData.sPitch = pitch;
    stratuxData.sRoll = roll;
    stratuxData.sHeading = isnan(heading) ? NAN : fmod(heading, 360.0);
    stratuxData.sGroundspeed = gpsGroundSpeed;
    stratuxData.sSlip = slip;
    stratuxData.sGForce = gForce;

  } else {
    Serial.print("Failed to fetch Stratux data, HTTP code: ");
    Serial.println(httpCode);
  }

  http.end();
}
