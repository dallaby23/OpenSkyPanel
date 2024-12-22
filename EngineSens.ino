//*****************************************************************
//*************************Read EIS Sensors************************
//*****************************************************************
void read_eis() {
  if (millis() - eis.timer >= eis.eisFreq) {
    //Read voltage/current sensor data
    eis.vVoltRaw = ina.getBusVoltage();
    eis.vCurrentRaw = ina.getCurrent();

    //Read analogSensors
    eis.vWTempRaw = readChannel1(ADS1115_COMP_0_GND);
    eis.vWTempRaw = calculateTemperature(eis.vWTempRaw);

    eis.vOPressureRaw = readChannel1(ADS1115_COMP_2_GND);
    eis.vOPressureRaw = readPressure(eis.vOPressureRaw);

    eis.vFPressure = random(0, 10);
    eis.vOTemp = random(0, 250);
    eis.vCTemp = random(0, 250);
    eis.vFuelLevel = random(0, 100);

    //Smooth readings
    eis.vOPressure = eis.vOPressure * 0.9 + eis.vOPressureRaw * 0.1;
    eis.vFPressure = eis.vFPressure * 0.9 + eis.vFPressureRaw * 0.1;
    eis.vOTemp = eis.vOTemp * 0.9 + eis.vOTempRaw * 0.1;
    eis.vWTemp = eis.vWTemp * 0.9 + eis.vWTempRaw * 0.1;
    eis.vCTemp = eis.vCTemp * 0.9 + eis.vCTempRaw * 0.1;
    eis.vVolt = eis.vVolt * 0.9 + eis.vVoltRaw * 0.1;
    eis.vCurrent = eis.vCurrent * 0.9 + eis.vCurrentRaw * 0.1;
    eis.vFuelLevel = eis.vFuelLevel * 0.9 + eis.vFuelLevelRaw * 0.1;

    //Update Hobbs
    if (eis.vOPressure > 0) {
      if (millis() - eis.engineTime >= 20000) {
        eis.engineTime = (millis() - eis.engineTime);
        vs.hobbs += eis.engineTime / 3600000.0;
        eis.engineTime = millis();
      }
    }

    eis.hours = int(vs.hobbs);
    eis.minutes = (int)((vs.hobbs - eis.hours) * 60);

    //Update Webpage
    sendEISData();

    eis.timer = millis();
  }
}

// Function to send EIS data via WebSocket
void sendEISData() {
    // Define the size of the JSON document
    // Adjust the capacity based on the number of variables you include
    StaticJsonDocument<512> doc;

    // Populate the JSON document with EIS variables
    doc["vVolt"] = int(eis.vVolt);
    doc["vCurrent"] = eis.vCurrent;
    doc["vWTemp"] = int(eis.vWTemp);
    doc["vOPressure"] = int(eis.vOPressure);
    doc["vFPressure"] = int(eis.vFPressure);
    doc["vOTemp"] = int(eis.vOTemp);
    doc["vCTemp"] = int(eis.vCTemp);
    doc["VFuelLevel"] = int(eis.vFuelLevel);
    doc["hours"] = eis.hours;
    doc["minutes"] = eis.minutes;
    // Add more variables as needed

    // Serialize JSON to a string
    String jsonString;
    serializeJson(doc, jsonString);

    // Broadcast the JSON string to all connected clients
    ws.textAll(jsonString);
}

