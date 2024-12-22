//*********************************************************************************
//***********************Webserver EFIS page handling******************************
//*********************************************************************************

// ***** WebServer Functions *****
void onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");

    // Create a JSON document with sufficient size
    StaticJsonDocument<4096> jsonDoc;  // Adjust size as needed

    // ***** WiFi Configuration *****
    jsonDoc["SSID"] = wifi.SSID;
    jsonDoc["Password"] = wifi.Password;
    jsonDoc["StaticIP"] = wifi.StaticIP;
    jsonDoc["Gateway"] = wifi.Gateway;
    jsonDoc["Subnet"] = wifi.Subnet;

    // ***** EFIS Variables *****
    jsonDoc["pitch"] = int(efis.pitch);
    jsonDoc["roll"] = int(efis.roll);
    jsonDoc["heading"] = int(efis.heading);
    jsonDoc["airspeed"] = int(efis.airspeed);
    jsonDoc["groundSpeed"] = int(efis.groundSpeed);
    jsonDoc["altitude"] = int(efis.altitude);
    jsonDoc["verticalSpeed"] = int(efis.verticalSpeed);
    jsonDoc["slip"] = int(efis.slip);
    jsonDoc["rpm"] = int(efis.rpm);
    jsonDoc["aoa"] = int(efis.aoa);
    jsonDoc["efisFreq"] = efis.efisFreq;
    jsonDoc["imuFreq"] = efis.imuFreq;
    jsonDoc["gForce"] = efis.gForce;

    // ***** EIS Variables *****
    jsonDoc["vVolt"] = int(eis.vVolt);
    jsonDoc["vCurrent"] = eis.vCurrent;
    jsonDoc["vWTemp"] = int(eis.vWTemp);
    jsonDoc["vOPressure"] = int(eis.vOPressure);
    jsonDoc["vFPressure"] = int(eis.vFPressure);
    jsonDoc["vOTemp"] = int(eis.vOTemp);
    jsonDoc["vCTemp"] = int(eis.vCTemp);
    jsonDoc["vFuelLevel"] = int(eis.vFuelLevel);
    jsonDoc["hours"] = eis.hours;
    jsonDoc["minutes"] = eis.minutes;
    jsonDoc["eisFreq"] = eis.eisFreq;

    // ***** VS Variables *****
    jsonDoc["headingBug"] = vs.headingBug;
    jsonDoc["aoaStallVal"] = vs.aoaStallVal;
    jsonDoc["airspeedBug"] = vs.airspeedBug;
    jsonDoc["airspeedMax"] = vs.airspeedMax;
    jsonDoc["airspeedYellowMin"] = vs.airspeedYellowMin;
    jsonDoc["airspeedYellowMax"] = vs.airspeedYellowMax;
    jsonDoc["airspeedRedMin"] = vs.airspeedRedMin;
    jsonDoc["airspeedRedMax"] = vs.airspeedRedMax;
    jsonDoc["vsiScaleVal"] = vs.vsiScaleVal;
    jsonDoc["vsiSegments"] = vs.vsiSegments;
    jsonDoc["altitudeStep"] = vs.altitudeStep;
    jsonDoc["altitudeBug"] = vs.altitudeBug;
    jsonDoc["altimeterSetting"] = vs.altimeterSetting;
    jsonDoc["rpmMax"] = vs.rpmMax;
    jsonDoc["rpmYellow"] = vs.rpmYellow;
    jsonDoc["rpmRed"] = vs.rpmRed;
    jsonDoc["apEngage"] = vs.apEngage;
    jsonDoc["apAltitudeHold"] = vs.apAltitudeHold;
    jsonDoc["apWingLeveler"] = vs.apWingLeveler;
    jsonDoc["maxVertical"] = vs.maxVertical;
    jsonDoc["maxPitch"] = vs.maxPitch;
    jsonDoc["maxRoll"] = vs.maxRoll;
    jsonDoc["apHeadingKp"] = vs.apHeadingKp;
    jsonDoc["apHeadingKd"] = vs.apHeadingKd;
    jsonDoc["apAltitudeKp"] = vs.apAltitudeKp;
    jsonDoc["apAltitudeKd"] = vs.apAltitudeKd;
    jsonDoc["servoMin"] = vs.servoMin;
    jsonDoc["servoMax"] = vs.servoMax;
    jsonDoc["servoFreq"] = vs.servoFreq;
    jsonDoc["apServoAdjustmentRate"] = vs.apServoAdjustmentRate;

    jsonDoc["sensor1Label"] = String(vs.sensor1Label);
    jsonDoc["sensor1MinConfig"] = vs.sensor1Min;
    jsonDoc["sensor1MaxConfig"] = vs.sensor1Max;
    jsonDoc["sensor1YellowMin"] = vs.sensor1YellowMin;
    jsonDoc["sensor1YellowMax"] = vs.sensor1YellowMax;
    jsonDoc["sensor1RedMin"] = vs.sensor1RedMin;
    jsonDoc["sensor1RedMax"] = vs.sensor1RedMax;
    jsonDoc["sensor1Visible"] = vs.sensor1Visible;

    // ***** Sensor2 *****
    jsonDoc["sensor2Label"] = String(vs.sensor2Label);
    jsonDoc["sensor2MinConfig"] = vs.sensor2Min;
    jsonDoc["sensor2MaxConfig"] = vs.sensor2Max;
    jsonDoc["sensor2YellowMin"] = vs.sensor2YellowMin;
    jsonDoc["sensor2YellowMax"] = vs.sensor2YellowMax;
    jsonDoc["sensor2RedMin"] = vs.sensor2RedMin;
    jsonDoc["sensor2RedMax"] = vs.sensor2RedMax;
    jsonDoc["sensor2Visible"] = vs.sensor2Visible;

    // ***** Sensor3 *****
    jsonDoc["sensor3Label"] = String(vs.sensor3Label);
    jsonDoc["sensor3MinConfig"] = vs.sensor3Min;
    jsonDoc["sensor3MaxConfig"] = vs.sensor3Max;
    jsonDoc["sensor3YellowMin"] = vs.sensor3YellowMin;
    jsonDoc["sensor3YellowMax"] = vs.sensor3YellowMax;
    jsonDoc["sensor3RedMin"] = vs.sensor3RedMin;
    jsonDoc["sensor3RedMax"] = vs.sensor3RedMax;
    jsonDoc["sensor3Visible"] = vs.sensor3Visible;

    // ***** Sensor4 *****
    jsonDoc["sensor4Label"] = String(vs.sensor4Label);
    jsonDoc["sensor4MinConfig"] = vs.sensor4Min;
    jsonDoc["sensor4MaxConfig"] = vs.sensor4Max;
    jsonDoc["sensor4YellowMin"] = vs.sensor4YellowMin;
    jsonDoc["sensor4YellowMax"] = vs.sensor4YellowMax;
    jsonDoc["sensor4RedMin"] = vs.sensor4RedMin;
    jsonDoc["sensor4RedMax"] = vs.sensor4RedMax;
    jsonDoc["sensor4Visible"] = vs.sensor4Visible;

    // ***** Sensor5 *****
    jsonDoc["sensor5Label"] = String(vs.sensor5Label);
    jsonDoc["sensor5MinConfig"] = vs.sensor5Min;
    jsonDoc["sensor5MaxConfig"] = vs.sensor5Max;
    jsonDoc["sensor5YellowMin"] = vs.sensor5YellowMin;
    jsonDoc["sensor5YellowMax"] = vs.sensor5YellowMax;
    jsonDoc["sensor5RedMin"] = vs.sensor5RedMin;
    jsonDoc["sensor5RedMax"] = vs.sensor5RedMax;
    jsonDoc["sensor5Visible"] = vs.sensor5Visible;

    // ***** Sensor6 *****
    jsonDoc["sensor6Label"] = String(vs.sensor6Label);
    jsonDoc["sensor6MinConfig"] = vs.sensor6Min;
    jsonDoc["sensor6MaxConfig"] = vs.sensor6Max;
    jsonDoc["sensor6YellowMin"] = vs.sensor6YellowMin;
    jsonDoc["sensor6YellowMax"] = vs.sensor6YellowMax;
    jsonDoc["sensor6RedMin"] = vs.sensor6RedMin;
    jsonDoc["sensor6RedMax"] = vs.sensor6RedMax;
    jsonDoc["sensor6Visible"] = vs.sensor6Visible;

    // ***** Sensor7 *****
    jsonDoc["sensor7Label"] = String(vs.sensor7Label);
    jsonDoc["sensor7MinConfig"] = vs.sensor7Min;
    jsonDoc["sensor7MaxConfig"] = vs.sensor7Max;
    jsonDoc["sensor7YellowMin"] = vs.sensor7YellowMin;
    jsonDoc["sensor7YellowMax"] = vs.sensor7YellowMax;
    jsonDoc["sensor7RedMin"] = vs.sensor7RedMin;
    jsonDoc["sensor7RedMax"] = vs.sensor7RedMax;
    jsonDoc["sensor7Visible"] = vs.sensor7Visible;

    // ***** Sensor8 *****
    jsonDoc["sensor8Label"] = String(vs.sensor8Label);
    jsonDoc["sensor8MinConfig"] = vs.sensor8Min;
    jsonDoc["sensor8MaxConfig"] = vs.sensor8Max;
    jsonDoc["sensor8YellowMin"] = vs.sensor8YellowMin;
    jsonDoc["sensor8YellowMax"] = vs.sensor8YellowMax;
    jsonDoc["sensor8RedMin"] = vs.sensor8RedMin;
    jsonDoc["sensor8RedMax"] = vs.sensor8RedMax;
    jsonDoc["sensor8Visible"] = vs.sensor8Visible;

    // ***** Debug Variables *****
    jsonDoc["debugFreq"] = vs.debugFreq;

    // ***** Trim
    jsonDoc["pitchTrim"] = vs.pitchTrim;
    jsonDoc["rollTrim"] = vs.rollTrim;
    jsonDoc["trimMin"] = vs.trimMin;
    jsonDoc["trimMax"] = vs.trimMax;

    // **** Stratux Settings
    jsonDoc["scPitchRoll"] = vs.scPitchRoll;
    jsonDoc["scHeading"] = vs.scHeading;
    jsonDoc["scSlip"] = vs.scSlip;

    // Serialize JSON to string
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    client->text(jsonString);

  } else if (type == WS_EVT_DATA) {
    // Parse incoming data
    String msg;
    for (size_t i = 0; i < len; i++) {
      msg += (char)data[i];
    }
    Serial.println("Received from client: " + msg);

    // Deserialize the incoming JSON
    StaticJsonDocument<4096> doc;  // Adjust size as needed
    DeserializationError error = deserializeJson(doc, msg);
    if (error) {
      Serial.println("Invalid JSON received.");
      return;
    }

    // Flag to check if any setting was updated
    bool updated = false;

    // ***** WiFi Configuration *****
    if (doc.containsKey("SSID")) {
      wifi.SSID = doc["SSID"].as<String>();
      updated = true;
    }
    if (doc.containsKey("Password")) {
      wifi.Password = doc["Password"].as<String>();
      updated = true;
    }
    if (doc.containsKey("StaticIP")) {
      wifi.StaticIP = doc["StaticIP"].as<String>();
      updated = true;
    }
    if (doc.containsKey("Gateway")) {
      wifi.Gateway = doc["Gateway"].as<String>();
      updated = true;
    }
    if (doc.containsKey("Subnet")) {
      wifi.Subnet = doc["Subnet"].as<String>();
      updated = true;
    }

    // ***** EFIS Variables *****
    if (doc.containsKey("efisFreq")) {
      efis.efisFreq = doc["efisFreq"].as<int>();
      updated = true;
    }
    if (doc.containsKey("imuFreq")) {
      efis.imuFreq = doc["imuFreq"].as<int>();
      updated = true;
    }

    // ***** EIS Variables *****
    if (doc.containsKey("eisFreq")) {
      eis.eisFreq = doc["eisFreq"].as<int>();
      updated = true;
    }

    // ***** VS Variables *****
    if (doc.containsKey("pitchCageOffset")) {
      vs.pitchCageOffset = doc["pitchCageOffset"].as<float>();
      updated = true;
    }
    if (doc.containsKey("rollCageOffset")) {
      vs.rollCageOffset = doc["rollCageOffset"].as<float>();
      updated = true;
    }
    if (doc.containsKey("headingBug")) {
      vs.headingBug = doc["headingBug"].as<int>();
      updated = true;
    }
    if (doc.containsKey("aoaStallVal")) {
      vs.aoaStallVal = doc["aoaStallVal"].as<int>();
      updated = true;
    }
    if (doc.containsKey("airspeedBug")) {
      vs.airspeedBug = doc["airspeedBug"].as<int>();
      updated = true;
    }
    if (doc.containsKey("airspeedMax")) {
      vs.airspeedMax = doc["airspeedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("airspeedYellowMin")) {
      vs.airspeedYellowMin = doc["airspeedYellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("airspeedYellowMax")) {
      vs.airspeedYellowMax = doc["airspeedYellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("airspeedRedMin")) {
      vs.airspeedRedMin = doc["airspeedRedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("airspeedRedMax")) {
      vs.airspeedRedMax = doc["airspeedRedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("vsiScaleVal")) {
      vs.vsiScaleVal = doc["vsiScaleVal"].as<int>();
      updated = true;
    }
    if (doc.containsKey("vsiSegments")) {
      vs.vsiSegments = doc["vsiSegments"].as<int>();
      updated = true;
    }
    if (doc.containsKey("altitudeStep")) {
      vs.altitudeStep = doc["altitudeStep"].as<int>();
      updated = true;
    }
    if (doc.containsKey("altitudeBug")) {
      vs.altitudeBug = doc["altitudeBug"].as<int>();
      updated = true;
    }
    if (doc.containsKey("altimeterSetting")) {
      vs.altimeterSetting = doc["altimeterSetting"].as<float>();
      updated = true;
    }
    if (doc.containsKey("rpmMax")) {
      vs.rpmMax = doc["rpmMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("rpmYellow")) {
      vs.rpmYellow = doc["rpmYellow"].as<int>();
      updated = true;
    }
    if (doc.containsKey("rpmRed")) {
      vs.rpmRed = doc["rpmRed"].as<int>();
      updated = true;
    }
    if (doc.containsKey("apEngage")) {
      vs.apEngage = doc["apEngage"].as<bool>();
      updated = true;
    }
    if (doc.containsKey("apAltitudeHold")) {
      vs.apAltitudeHold = doc["apAltitudeHold"].as<bool>();
      updated = true;
    }
    if (doc.containsKey("apWingLeveler")) {
      vs.apWingLeveler = doc["apWingLeveler"].as<bool>();
      updated = true;
    }
    if (doc.containsKey("maxVertical")) {
      vs.maxVertical = doc["maxVertical"].as<float>();
      updated = true;
    }
    if (doc.containsKey("maxPitch")) {
      vs.maxPitch = doc["maxPitch"].as<float>();
      updated = true;
    }
    if (doc.containsKey("maxRoll")) {
      vs.maxRoll = doc["maxRoll"].as<float>();
      updated = true;
    }
    if (doc.containsKey("apHeadingKp")) {
      vs.apHeadingKp = doc["apHeadingKp"].as<float>();
      updated = true;
    }
    if (doc.containsKey("apHeadingKd")) {
      vs.apHeadingKd = doc["apHeadingKd"].as<float>();
      updated = true;
    }
    if (doc.containsKey("apAltitudeKp")) {
      vs.apAltitudeKp = doc["apAltitudeKp"].as<float>();
      updated = true;
    }
    if (doc.containsKey("apAltitudeKd")) {
      vs.apAltitudeKd = doc["apAltitudeKd"].as<float>();
      updated = true;
    }
    if (doc.containsKey("servoMin")) {
      vs.servoMin = doc["servoMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("servoMax")) {
      vs.servoMax = doc["servoMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("servoFreq")) {
      vs.servoFreq = doc["servoFreq"].as<int>();
      updated = true;
    }
    if (doc.containsKey("apServoAdjustmentRate")) {
      vs.apServoAdjustmentRate = doc["apServoAdjustmentRate"].as<float>();
      updated = true;
    }

    // ***** Sensor Labels and Configurations *****
    // Sensor1
    if (doc.containsKey("sensor1Label")) {
      copySensorLabel(vs.sensor1Label, sizeof(vs.sensor1Label), doc["sensor1Label"].as<const char*>());
      updated = true;
    }
    if (doc.containsKey("sensor1MinConfig")) {
      vs.sensor1Min = doc["sensor1MinConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor1MaxConfig")) {
      vs.sensor1Max = doc["sensor1MaxConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor1YellowMin")) {
      vs.sensor1YellowMin = doc["sensor1YellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor1YellowMax")) {
      vs.sensor1YellowMax = doc["sensor1YellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor1RedMin")) {
      vs.sensor1RedMin = doc["sensor1RedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor1RedMax")) {
      vs.sensor1RedMax = doc["sensor1RedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor1Visible")) {
      vs.sensor1Visible = doc["sensor1Visible"].as<bool>();
      updated = true;
    }

    // ***** Sensor2 *****
    if (doc.containsKey("sensor2Label")) {
      copySensorLabel(vs.sensor2Label, sizeof(vs.sensor2Label), doc["sensor2Label"].as<const char*>());
      updated = true;
    }
    if (doc.containsKey("sensor2MinConfig")) {
      vs.sensor2Min = doc["sensor2MinConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor2MaxConfig")) {
      vs.sensor2Max = doc["sensor2MaxConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor2YellowMin")) {
      vs.sensor2YellowMin = doc["sensor2YellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor2YellowMax")) {
      vs.sensor2YellowMax = doc["sensor2YellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor2RedMin")) {
      vs.sensor2RedMin = doc["sensor2RedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor2RedMax")) {
      vs.sensor2RedMax = doc["sensor2RedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor2Visible")) {
      vs.sensor2Visible = doc["sensor2Visible"].as<bool>();
      updated = true;
    }

    // ***** Repeat for Sensor3 to Sensor8 *****
    // Sensor3
    if (doc.containsKey("sensor3Label")) {
      copySensorLabel(vs.sensor3Label, sizeof(vs.sensor3Label), doc["sensor3Label"].as<const char*>());
      updated = true;
    }
    if (doc.containsKey("sensor3MinConfig")) {
      vs.sensor3Min = doc["sensor3MinConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor3MaxConfig")) {
      vs.sensor3Max = doc["sensor3MaxConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor3YellowMin")) {
      vs.sensor3YellowMin = doc["sensor3YellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor3YellowMax")) {
      vs.sensor3YellowMax = doc["sensor3YellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor3RedMin")) {
      vs.sensor3RedMin = doc["sensor3RedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor3RedMax")) {
      vs.sensor3RedMax = doc["sensor3RedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor3Visible")) {
      vs.sensor3Visible = doc["sensor3Visible"].as<bool>();
      updated = true;
    }

    // Sensor4
    if (doc.containsKey("sensor4Label")) {
      copySensorLabel(vs.sensor4Label, sizeof(vs.sensor4Label), doc["sensor4Label"].as<const char*>());
      updated = true;
    }
    if (doc.containsKey("sensor4MinConfig")) {
      vs.sensor4Min = doc["sensor4MinConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor4MaxConfig")) {
      vs.sensor4Max = doc["sensor4MaxConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor4YellowMin")) {
      vs.sensor4YellowMin = doc["sensor4YellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor4YellowMax")) {
      vs.sensor4YellowMax = doc["sensor4YellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor4RedMin")) {
      vs.sensor4RedMin = doc["sensor4RedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor4RedMax")) {
      vs.sensor4RedMax = doc["sensor4RedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor4Visible")) {
      vs.sensor4Visible = doc["sensor4Visible"].as<bool>();
      updated = true;
    }

    // Sensor5
    if (doc.containsKey("sensor5Label")) {
      copySensorLabel(vs.sensor5Label, sizeof(vs.sensor5Label), doc["sensor5Label"].as<const char*>());
      updated = true;
    }
    if (doc.containsKey("sensor5MinConfig")) {
      vs.sensor5Min = doc["sensor5MinConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor5MaxConfig")) {
      vs.sensor5Max = doc["sensor5MaxConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor5YellowMin")) {
      vs.sensor5YellowMin = doc["sensor5YellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor5YellowMax")) {
      vs.sensor5YellowMax = doc["sensor5YellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor5RedMin")) {
      vs.sensor5RedMin = doc["sensor5RedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor5RedMax")) {
      vs.sensor5RedMax = doc["sensor5RedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor5Visible")) {
      vs.sensor5Visible = doc["sensor5Visible"].as<bool>();
      updated = true;
    }

    // Sensor6
    if (doc.containsKey("sensor6Label")) {
      copySensorLabel(vs.sensor6Label, sizeof(vs.sensor6Label), doc["sensor6Label"].as<const char*>());
      updated = true;
    }
    if (doc.containsKey("sensor6MinConfig")) {
      vs.sensor6Min = doc["sensor6MinConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor6MaxConfig")) {
      vs.sensor6Max = doc["sensor6MaxConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor6YellowMin")) {
      vs.sensor6YellowMin = doc["sensor6YellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor6YellowMax")) {
      vs.sensor6YellowMax = doc["sensor6YellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor6RedMin")) {
      vs.sensor6RedMin = doc["sensor6RedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor6RedMax")) {
      vs.sensor6RedMax = doc["sensor6RedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor6Visible")) {
      vs.sensor6Visible = doc["sensor6Visible"].as<bool>();
      updated = true;
    }

    // Sensor7
    if (doc.containsKey("sensor7Label")) {
      copySensorLabel(vs.sensor7Label, sizeof(vs.sensor7Label), doc["sensor7Label"].as<const char*>());
      updated = true;
    }
    if (doc.containsKey("sensor7MinConfig")) {
      vs.sensor7Min = doc["sensor7MinConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor7MaxConfig")) {
      vs.sensor7Max = doc["sensor7MaxConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor7YellowMin")) {
      vs.sensor7YellowMin = doc["sensor7YellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor7YellowMax")) {
      vs.sensor7YellowMax = doc["sensor7YellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor7RedMin")) {
      vs.sensor7RedMin = doc["sensor7RedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor7RedMax")) {
      vs.sensor7RedMax = doc["sensor7RedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor7Visible")) {
      vs.sensor7Visible = doc["sensor7Visible"].as<bool>();
      updated = true;
    }

    // Sensor8
    if (doc.containsKey("sensor8Label")) {
      copySensorLabel(vs.sensor8Label, sizeof(vs.sensor8Label), doc["sensor8Label"].as<const char*>());
      updated = true;
    }
    if (doc.containsKey("sensor8MinConfig")) {
      vs.sensor8Min = doc["sensor8MinConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor8MaxConfig")) {
      vs.sensor8Max = doc["sensor8MaxConfig"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor8YellowMin")) {
      vs.sensor8YellowMin = doc["sensor8YellowMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor8YellowMax")) {
      vs.sensor8YellowMax = doc["sensor8YellowMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor8RedMin")) {
      vs.sensor8RedMin = doc["sensor8RedMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor8RedMax")) {
      vs.sensor8RedMax = doc["sensor8RedMax"].as<int>();
      updated = true;
    }
    if (doc.containsKey("sensor8Visible")) {
      vs.sensor8Visible = doc["sensor8Visible"].as<bool>();
      updated = true;
    }

    // ***** Hobbs *****
    if (doc.containsKey("hobbs")) {
      vs.hobbs = doc["hobbs"].as<float>();
      updated = true;
    }

    // ***** Trim *****
    if (doc.containsKey("pitchTrim")) {
      vs.pitchTrim = doc["pitchTrim"].as<int>();
      updated = true;
    }
    if (doc.containsKey("rollTrim")) {
      vs.rollTrim = doc["rollTrim"].as<int>();
      updated = true;
    }
    if (doc.containsKey("trimMin")) {
      vs.trimMin = doc["trimMin"].as<int>();
      updated = true;
    }
    if (doc.containsKey("trimMax")) {
      vs.trimMax = doc["trimMax"].as<int>();
      updated = true;
    }

    // ***** Debug Variables *****
    if (doc.containsKey("debugFreq")) {
      vs.debugFreq = doc["debugFreq"].as<int>();
      updated = true;
    }

    //*****Cage Action
    if (doc.containsKey("action")) {
      if (doc["action"] = "cagePFD") {
        cagePFD();
      }
    }

    //*****Stratux Action
    if (doc.containsKey("stratux")) {
      stratuxData.sEnabled = doc["stratux"].as<bool>();
      if (stratuxData.sEnabled) {
        connectToStratuxWifi();
      }
    }

    //*****Stratux Settings
    if (doc.containsKey("scPitchRoll")) {
      vs.scPitchRoll = doc["scPitchRoll"].as<bool>();
      updated = true;
    }
    if (doc.containsKey("scHeading")) {
      vs.scHeading = doc["scHeading"].as<bool>();
      updated = true;
    }
    if (doc.containsKey("scSlip")) {
      vs.scSlip = doc["scSlip"].as<bool>();
      updated = true;
    }

    // ***** Save Settings if Updated *****
    if (updated) {
      if (saveSettings()) {
        // Broadcast the updated settings to all clients
        ws.textAll(msg);
        Serial.println("Settings updated and saved.");
      } else {
        Serial.println("Failed to save settings.");
      }
    }
  }
}




void sendKeyVal(const char* key, float value) {
  String msg = "{\"";
  msg += key;
  msg += "\":";
  msg += value;
  msg += "}";
  ws.textAll(msg);
}
