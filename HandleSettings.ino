//*******************************************************************
//*********************Handle load and save settings to json*********
//*******************************************************************

//Save Settings to /settings.json
bool saveSettings() {
  File file = LittleFS.open("/settings.json", "w");
  if (!file) {
    Serial.println("Failed to open settings file for writing.");
    return false;
  }

  // Create a JSON document with sufficient size
  StaticJsonDocument<4096> jsonDoc;  // Adjust size as needed

  // ***** WiFi Configuration *****
  jsonDoc["SSID"] = wifi.SSID;
  jsonDoc["Password"] = wifi.Password;
  jsonDoc["StaticIP"] = wifi.StaticIP;
  jsonDoc["Gateway"] = wifi.Gateway;
  jsonDoc["Subnet"] = wifi.Subnet;

  // ***** EFIS Variables *****
  jsonDoc["efisFreq"] = efis.efisFreq;
  jsonDoc["imuFreq"] = efis.imuFreq;

  // ***** EIS Variables *****
  jsonDoc["eisFreq"] = eis.eisFreq;  // Renamed to avoid conflict with efis.eisFreq

  // ***** VS Variables *****
  jsonDoc["pitchCageOffset"] = vs.pitchCageOffset;
  jsonDoc["rollCageOffset"] = vs.rollCageOffset;
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

  jsonDoc["sensor2Label"] = String(vs.sensor2Label);
  jsonDoc["sensor2MinConfig"] = vs.sensor2Min;
  jsonDoc["sensor2MaxConfig"] = vs.sensor2Max;
  jsonDoc["sensor2YellowMin"] = vs.sensor2YellowMin;
  jsonDoc["sensor2YellowMax"] = vs.sensor2YellowMax;
  jsonDoc["sensor2RedMin"] = vs.sensor2RedMin;
  jsonDoc["sensor2RedMax"] = vs.sensor2RedMax;
  jsonDoc["sensor2Visible"] = vs.sensor2Visible;

  jsonDoc["sensor3Label"] = String(vs.sensor3Label);
  jsonDoc["sensor3MinConfig"] = vs.sensor3Min;
  jsonDoc["sensor3MaxConfig"] = vs.sensor3Max;
  jsonDoc["sensor3YellowMin"] = vs.sensor3YellowMin;
  jsonDoc["sensor3YellowMax"] = vs.sensor3YellowMax;
  jsonDoc["sensor3RedMin"] = vs.sensor3RedMin;
  jsonDoc["sensor3RedMax"] = vs.sensor3RedMax;
  jsonDoc["sensor3Visible"] = vs.sensor3Visible;

  jsonDoc["sensor4Label"] = String(vs.sensor4Label);
  jsonDoc["sensor4MinConfig"] = vs.sensor4Min;
  jsonDoc["sensor4MaxConfig"] = vs.sensor4Max;
  jsonDoc["sensor4YellowMin"] = vs.sensor4YellowMin;
  jsonDoc["sensor4YellowMax"] = vs.sensor4YellowMax;
  jsonDoc["sensor4RedMin"] = vs.sensor4RedMin;
  jsonDoc["sensor4RedMax"] = vs.sensor4RedMax;
  jsonDoc["sensor4Visible"] = vs.sensor4Visible;

  jsonDoc["sensor5Label"] = String(vs.sensor5Label);
  jsonDoc["sensor5MinConfig"] = vs.sensor5Min;
  jsonDoc["sensor5MaxConfig"] = vs.sensor5Max;
  jsonDoc["sensor5YellowMin"] = vs.sensor5YellowMin;
  jsonDoc["sensor5YellowMax"] = vs.sensor5YellowMax;
  jsonDoc["sensor5RedMin"] = vs.sensor5RedMin;
  jsonDoc["sensor5RedMax"] = vs.sensor5RedMax;
  jsonDoc["sensor5Visible"] = vs.sensor5Visible;

  jsonDoc["sensor6Label"] = String(vs.sensor6Label);
  jsonDoc["sensor6MinConfig"] = vs.sensor6Min;
  jsonDoc["sensor6MaxConfig"] = vs.sensor6Max;
  jsonDoc["sensor6YellowMin"] = vs.sensor6YellowMin;
  jsonDoc["sensor6YellowMax"] = vs.sensor6YellowMax;
  jsonDoc["sensor6RedMin"] = vs.sensor6RedMin;
  jsonDoc["sensor6RedMax"] = vs.sensor6RedMax;
  jsonDoc["sensor6Visible"] = vs.sensor6Visible;

  jsonDoc["sensor7Label"] = String(vs.sensor7Label);
  jsonDoc["sensor7MinConfig"] = vs.sensor7Min;
  jsonDoc["sensor7MaxConfig"] = vs.sensor7Max;
  jsonDoc["sensor7YellowMin"] = vs.sensor7YellowMin;
  jsonDoc["sensor7YellowMax"] = vs.sensor7YellowMax;
  jsonDoc["sensor7RedMin"] = vs.sensor7RedMin;
  jsonDoc["sensor7RedMax"] = vs.sensor7RedMax;
  jsonDoc["sensor7Visible"] = vs.sensor7Visible;

  jsonDoc["sensor8Label"] = String(vs.sensor8Label);
  jsonDoc["sensor8MinConfig"] = vs.sensor8Min;
  jsonDoc["sensor8MaxConfig"] = vs.sensor8Max;
  jsonDoc["sensor8YellowMin"] = vs.sensor8YellowMin;
  jsonDoc["sensor8YellowMax"] = vs.sensor8YellowMax;
  jsonDoc["sensor8RedMin"] = vs.sensor8RedMin;
  jsonDoc["sensor8RedMax"] = vs.sensor8RedMax;
  jsonDoc["sensor8Visible"] = vs.sensor8Visible;

  jsonDoc["hobbs"] = vs.hobbs;

  jsonDoc["pitchTrim"] = vs.pitchTrim;
  jsonDoc["rollTrim"] = vs.rollTrim;
  jsonDoc["trimMin"] = vs.trimMin;
  jsonDoc["trimMax"] = vs.trimMax;

  jsonDoc["scPitchRoll"] = vs.scPitchRoll;
  jsonDoc["scHeading"] = vs.scHeading;
  jsonDoc["scSlip"] = vs.scSlip;


  // ***** Debug Variables *****
  jsonDoc["debugFreq"] = vs.debugFreq;

  // Serialize JSON to file
  if (serializeJson(jsonDoc, file) == 0) {
    Serial.println("Failed to write settings to file.");
    file.close();
    return false;
  }

  file.close();

  return true;
}




//Load Settings from /settings.json
bool loadSettings() {
  if (!LittleFS.exists("/settings.json")) {
    Serial.println("No settings file found. Using defaults.");
    return false;
  }

  File file = LittleFS.open("/settings.json", "r");
  if (!file) {
    Serial.println("Failed to open settings file for reading.");
    return false;
  }

  StaticJsonDocument<4096> jsonDoc;  // Adjust size as needed
  DeserializationError error = deserializeJson(jsonDoc, file);
  file.close();

  if (error) {
    Serial.println("Failed to parse settings file. Using defaults.");
    return false;
  }

  // ***** WiFi Configuration *****
  if (jsonDoc.containsKey("SSID")) {
    wifi.SSID = jsonDoc["SSID"].as<String>();
  }
  if (jsonDoc.containsKey("Password")) {
    wifi.Password = jsonDoc["Password"].as<String>();
  }
  if (jsonDoc.containsKey("StaticIP")) {
    wifi.StaticIP = jsonDoc["StaticIP"].as<String>();
  }
  if (jsonDoc.containsKey("Gateway")) {
    wifi.Gateway = jsonDoc["Gateway"].as<String>();
  }
  if (jsonDoc.containsKey("Subnet")) {
    wifi.Subnet = jsonDoc["Subnet"].as<String>();
  }

  // ***** EFIS Variables *****
  if (jsonDoc.containsKey("efisFreq")) {
    efis.efisFreq = jsonDoc["efisFreq"].as<int>();
  }
  if (jsonDoc.containsKey("imuFreq")) {
    efis.imuFreq = jsonDoc["imuFreq"].as<int>();
  }

  // ***** EIS Variables *****
  if (jsonDoc.containsKey("eisFreq")) {
    eis.eisFreq = jsonDoc["eisFreq"].as<int>();
  }

  // ***** VS Variables *****
  if (jsonDoc.containsKey("pitchCageOffset")) {
    vs.pitchCageOffset = jsonDoc["pitchCageOffset"].as<float>();
  }
  if (jsonDoc.containsKey("rollCageOffset")) {
    vs.rollCageOffset = jsonDoc["rollCageOffset"].as<float>();
  }
  if (jsonDoc.containsKey("headingBug")) {
    vs.headingBug = jsonDoc["headingBug"].as<int>();
  }
  if (jsonDoc.containsKey("aoaStallVal")) {
    vs.aoaStallVal = jsonDoc["aoaStallVal"].as<int>();
  }
  if (jsonDoc.containsKey("airspeedBug")) {
    vs.airspeedBug = jsonDoc["airspeedBug"].as<int>();
  }
  if (jsonDoc.containsKey("airspeedMax")) {
    vs.airspeedMax = jsonDoc["airspeedMax"].as<int>();
  }
  if (jsonDoc.containsKey("airspeedYellowMin")) {
    vs.airspeedYellowMin = jsonDoc["airspeedYellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("airspeedYellowMax")) {
    vs.airspeedYellowMax = jsonDoc["airspeedYellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("airspeedRedMin")) {
    vs.airspeedRedMin = jsonDoc["airspeedRedMin"].as<int>();
  }
  if (jsonDoc.containsKey("airspeedRedMax")) {
    vs.airspeedRedMax = jsonDoc["airspeedRedMax"].as<int>();
  }
  if (jsonDoc.containsKey("vsiScaleVal")) {
    vs.vsiScaleVal = jsonDoc["vsiScaleVal"].as<int>();
  }
  if (jsonDoc.containsKey("vsiSegments")) {
    vs.vsiSegments = jsonDoc["vsiSegments"].as<int>();
  }
  if (jsonDoc.containsKey("altitudeStep")) {
    vs.altitudeStep = jsonDoc["altitudeStep"].as<int>();
  }
  if (jsonDoc.containsKey("altitudeBug")) {
    vs.altitudeBug = jsonDoc["altitudeBug"].as<int>();
  }
  if (jsonDoc.containsKey("altimeterSetting")) {
    vs.altimeterSetting = jsonDoc["altimeterSetting"].as<float>();
  }
  if (jsonDoc.containsKey("rpmMax")) {
    vs.rpmMax = jsonDoc["rpmMax"].as<int>();
  }
  if (jsonDoc.containsKey("rpmYellow")) {
    vs.rpmYellow = jsonDoc["rpmYellow"].as<int>();
  }
  if (jsonDoc.containsKey("rpmRed")) {
    vs.rpmRed = jsonDoc["rpmRed"].as<int>();
  }
  if (jsonDoc.containsKey("apAltitudeHold")) {
    vs.apAltitudeHold = jsonDoc["apAltitudeHold"].as<bool>();
  }
  if (jsonDoc.containsKey("apWingLeveler")) {
    vs.apWingLeveler = jsonDoc["apWingLeveler"].as<bool>();
  }
  if (jsonDoc.containsKey("maxVertical")) {
    vs.maxVertical = jsonDoc["maxVertical"].as<float>();
  }
  if (jsonDoc.containsKey("maxPitch")) {
    vs.maxPitch = jsonDoc["maxPitch"].as<float>();
  }
  if (jsonDoc.containsKey("maxRoll")) {
    vs.maxRoll = jsonDoc["maxRoll"].as<float>();
  }
  if (jsonDoc.containsKey("apHeadingKp")) {
    vs.apHeadingKp = jsonDoc["apHeadingKp"].as<float>();
  }
  if (jsonDoc.containsKey("apHeadingKd")) {
    vs.apHeadingKd = jsonDoc["apHeadingKd"].as<float>();
  }
  if (jsonDoc.containsKey("apAltitudeKp")) {
    vs.apAltitudeKp = jsonDoc["apAltitudeKp"].as<float>();
  }
  if (jsonDoc.containsKey("apAltitudeKd")) {
    vs.apAltitudeKd = jsonDoc["apAltitudeKd"].as<float>();
  }
  if (jsonDoc.containsKey("servoMin")) {
    vs.servoMin = jsonDoc["servoMin"].as<int>();
  }
  if (jsonDoc.containsKey("servoMax")) {
    vs.servoMax = jsonDoc["servoMax"].as<int>();
  }
  if (jsonDoc.containsKey("servoFreq")) {
    vs.servoFreq = jsonDoc["servoFreq"].as<int>();
  }
  if (jsonDoc.containsKey("apServoAdjustmentRate")) {
    vs.apServoAdjustmentRate = jsonDoc["apServoAdjustmentRate"].as<float>();
  }

  // ***** Sensor Labels and Configurations *****
  // Sensor1
  if (jsonDoc.containsKey("sensor1Label")) {
    copySensorLabel(vs.sensor1Label, sizeof(vs.sensor1Label), jsonDoc["sensor1Label"].as<const char*>());
  }
  if (jsonDoc.containsKey("sensor1MinConfig")) {
    vs.sensor1Min = jsonDoc["sensor1MinConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor1MaxConfig")) {
    vs.sensor1Max = jsonDoc["sensor1MaxConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor1YellowMin")) {
    vs.sensor1YellowMin = jsonDoc["sensor1YellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor1YellowMax")) {
    vs.sensor1YellowMax = jsonDoc["sensor1YellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor1RedMin")) {
    vs.sensor1RedMin = jsonDoc["sensor1RedMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor1RedMax")) {
    vs.sensor1RedMax = jsonDoc["sensor1RedMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor1Visible")) {
    vs.sensor1Visible = jsonDoc["sensor1Visible"].as<bool>();
  }

  // Sensor2
  if (jsonDoc.containsKey("sensor2Label")) {
    copySensorLabel(vs.sensor2Label, sizeof(vs.sensor2Label), jsonDoc["sensor2Label"].as<const char*>());
  }
  if (jsonDoc.containsKey("sensor2MinConfig")) {
    vs.sensor2Min = jsonDoc["sensor2MinConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor2MaxConfig")) {
    vs.sensor2Max = jsonDoc["sensor2MaxConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor2YellowMin")) {
    vs.sensor2YellowMin = jsonDoc["sensor2YellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor2YellowMax")) {
    vs.sensor2YellowMax = jsonDoc["sensor2YellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor2RedMin")) {
    vs.sensor2RedMin = jsonDoc["sensor2RedMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor2RedMax")) {
    vs.sensor2RedMax = jsonDoc["sensor2RedMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor2Visible")) {
    vs.sensor2Visible = jsonDoc["sensor2Visible"].as<bool>();
  }

  // Sensor3
  if (jsonDoc.containsKey("sensor3Label")) {
    copySensorLabel(vs.sensor3Label, sizeof(vs.sensor3Label), jsonDoc["sensor3Label"].as<const char*>());
  }
  if (jsonDoc.containsKey("sensor3MinConfig")) {
    vs.sensor3Min = jsonDoc["sensor3MinConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor3MaxConfig")) {
    vs.sensor3Max = jsonDoc["sensor3MaxConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor3YellowMin")) {
    vs.sensor3YellowMin = jsonDoc["sensor3YellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor3YellowMax")) {
    vs.sensor3YellowMax = jsonDoc["sensorYellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor3RedMin")) {
    vs.sensor3RedMin = jsonDoc["sensor3RedMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor3RedMax")) {
    vs.sensor3RedMax = jsonDoc["sensor3RedMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor3Visible")) {
    vs.sensor3Visible = jsonDoc["sensor3Visible"].as<bool>();
  }

  // Sensor4
  if (jsonDoc.containsKey("sensor4Label")) {
    copySensorLabel(vs.sensor4Label, sizeof(vs.sensor4Label), jsonDoc["sensor4Label"].as<const char*>());
  }
  if (jsonDoc.containsKey("sensor4MinConfig")) {
    vs.sensor4Min = jsonDoc["sensor4MinConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor4MaxConfig")) {
    vs.sensor4Max = jsonDoc["sensor4MaxConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor4YellowMin")) {
    vs.sensor4YellowMin = jsonDoc["sensor4YellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor4YellowMax")) {
    vs.sensor4YellowMax = jsonDoc["sensor4YellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor4RedMin")) {
    vs.sensor4RedMin = jsonDoc["sensor4RedMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor4RedMax")) {
    vs.sensor4RedMax = jsonDoc["sensor4RedMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor4Visible")) {
    vs.sensor4Visible = jsonDoc["sensor4Visible"].as<bool>();
  }

  // Sensor5
  if (jsonDoc.containsKey("sensor5Label")) {
    copySensorLabel(vs.sensor5Label, sizeof(vs.sensor5Label), jsonDoc["sensor5Label"].as<const char*>());
  }
  if (jsonDoc.containsKey("sensor5MinConfig")) {
    vs.sensor5Min = jsonDoc["sensor5MinConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor5MaxConfig")) {
    vs.sensor5Max = jsonDoc["sensor5MaxConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor5YellowMin")) {
    vs.sensor5YellowMin = jsonDoc["sensor5YellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor5YellowMax")) {
    vs.sensor5YellowMax = jsonDoc["sensor5YellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor5RedMin")) {
    vs.sensor5RedMin = jsonDoc["sensor5RedMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor5RedMax")) {
    vs.sensor5RedMax = jsonDoc["sensor5RedMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor5Visible")) {
    vs.sensor5Visible = jsonDoc["sensor5Visible"].as<bool>();
  }

  // Sensor6
  if (jsonDoc.containsKey("sensor6Label")) {
    copySensorLabel(vs.sensor6Label, sizeof(vs.sensor6Label), jsonDoc["sensor6Label"].as<const char*>());
  }
  if (jsonDoc.containsKey("sensor6MinConfig")) {
    vs.sensor6Min = jsonDoc["sensor6MinConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor6MaxConfig")) {
    vs.sensor6Max = jsonDoc["sensor6MaxConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor6YellowMin")) {
    vs.sensor6YellowMin = jsonDoc["sensor6YellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor6YellowMax")) {
    vs.sensor6YellowMax = jsonDoc["sensor6YellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor6RedMin")) {
    vs.sensor6RedMin = jsonDoc["sensor6RedMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor6RedMax")) {
    vs.sensor6RedMax = jsonDoc["sensor6RedMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor6Visible")) {
    vs.sensor6Visible = jsonDoc["sensor6Visible"].as<bool>();
  }

  // Sensor7
  if (jsonDoc.containsKey("sensor7Label")) {
    copySensorLabel(vs.sensor7Label, sizeof(vs.sensor7Label), jsonDoc["sensor7Label"].as<const char*>());
  }
  if (jsonDoc.containsKey("sensor7MinConfig")) {
    vs.sensor7Min = jsonDoc["sensor7MinConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor7MaxConfig")) {
    vs.sensor7Max = jsonDoc["sensor7MaxConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor7YellowMin")) {
    vs.sensor7YellowMin = jsonDoc["sensor7YellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor7YellowMax")) {
    vs.sensor7YellowMax = jsonDoc["sensor7YellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor7RedMin")) {
    vs.sensor7RedMin = jsonDoc["sensor7RedMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor7RedMax")) {
    vs.sensor7RedMax = jsonDoc["sensor7RedMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor7Visible")) {
    vs.sensor7Visible = jsonDoc["sensor7Visible"].as<bool>();
  }

  // Sensor8
  if (jsonDoc.containsKey("sensor8Label")) {
    copySensorLabel(vs.sensor8Label, sizeof(vs.sensor8Label), jsonDoc["sensor8Label"].as<const char*>());
  }
  if (jsonDoc.containsKey("sensor8MinConfig")) {
    vs.sensor8Min = jsonDoc["sensor8MinConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor8MaxConfig")) {
    vs.sensor8Max = jsonDoc["sensor8MaxConfig"].as<int>();
  }
  if (jsonDoc.containsKey("sensor8YellowMin")) {
    vs.sensor8YellowMin = jsonDoc["sensor8YellowMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor8YellowMax")) {
    vs.sensor8YellowMax = jsonDoc["sensor8YellowMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor8RedMin")) {
    vs.sensor8RedMin = jsonDoc["sensor8RedMin"].as<int>();
  }
  if (jsonDoc.containsKey("sensor8RedMax")) {
    vs.sensor8RedMax = jsonDoc["sensor8RedMax"].as<int>();
  }
  if (jsonDoc.containsKey("sensor8Visible")) {
    vs.sensor8Visible = jsonDoc["sensor8Visible"].as<bool>();
  }

  // ***** Hobbs *****
  if (jsonDoc.containsKey("hobbs")) {
    vs.hobbs = jsonDoc["hobbs"].as<float>();
  }

  // ***** Trim *****
  if (jsonDoc.containsKey("pitchTrim")) {
    vs.pitchTrim = jsonDoc["pitchTrim"].as<int>();
  }
  if (jsonDoc.containsKey("rollTrim")) {
    vs.rollTrim = jsonDoc["rollTrim"].as<int>();
  }
  if (jsonDoc.containsKey("trimMin")) {
    vs.trimMin = jsonDoc["trimMin"].as<int>();
  }
  if (jsonDoc.containsKey("trimMax")) {
    vs.trimMax = jsonDoc["trimMax"].as<int>();
  }

  // ***** Stratux Settings
  if (jsonDoc.containsKey("scPitchRoll")) {
    vs.scPitchRoll = jsonDoc["scPitchRoll"].as<bool>();
  }
  if (jsonDoc.containsKey("scHeading")) {
    vs.scHeading = jsonDoc["scHeading"].as<bool>();
  }
  if (jsonDoc.containsKey("scSlip")) {
    vs.scSlip = jsonDoc["scSlip"].as<bool>();
  }

  // ***** Debug Variables *****
  if (jsonDoc.containsKey("debugFreq")) {
    vs.debugFreq = jsonDoc["debugFreq"].as<int>();
  }

  Serial.println("Settings loaded from file.");
  return true;
}
