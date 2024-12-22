//*****************************************************************
//*************************Read Flight Sensors*********************
//*****************************************************************
void read_IMU() {
  //Read IMU Data
  if (millis() - efis.imuTimer >= efis.imuFreq) {
    sensors_event_t accel, gyro, mag;
    accelerometer->getEvent(&accel);
    gyroscope->getEvent(&gyro);
    magnetometer->getEvent(&mag);

    cal.calibrate(mag);

    efis.slip = accel.acceleration.y;
    efis.gx = gyro.gyro.x * SENSORS_RADS_TO_DPS;
    efis.gy = gyro.gyro.y * SENSORS_RADS_TO_DPS;
    efis.gz = gyro.gyro.z * SENSORS_RADS_TO_DPS;

    filter.update(efis.gx, efis.gy, efis.gz,
                  accel.acceleration.x, accel.acceleration.y, accel.acceleration.z,
                  mag.magnetic.x, mag.magnetic.y, mag.magnetic.z);

    efis.roll = filter.getRoll() - vs.rollCageOffset;
    efis.pitch = filter.getPitch() - vs.pitchCageOffset;
    efis.heading = filter.getYaw();

    efis.imuTimer = millis();
  }
}


void read_flight(){

  if (millis() - efis.sensorTimer >= efis.efisFreq) {
    //Get Airspeed
    efis.airspeedRaw = readChannel2(ADS1115_COMP_1_GND);
    efis.airspeedSmooth = efis.airspeedSmooth * 0.9 + efis.airspeedRaw * 0.1;
    efis.airspeed = mapfloat(efis.airspeedSmooth, 2.4000, 1.5000, 0.0000, 100.0000);
    if (efis.airspeed < 0) {
      efis.airspeed = 0;
    }

    //Get AoA
    efis.aoaRaw = readChannel2(ADS1115_COMP_2_GND);
    efis.aoaSmooth = efis.aoaSmooth * 0.9 + efis.aoaRaw * 0.1;
    efis.aoa = mapfloat(efis.aoaSmooth, 2.5000, 1.5000, 0.000, 12.000);
    if (efis.aoa < 0) {
      efis.aoa = 0;
    }

    //Get Altitude
    if (!bmp.performReading()) {
      Serial.println("Failed to read Pressure");
    }

    efis.altitude = (int(bmp.readAltitude(vs.altimeterSetting * 33.863886)) * 3.281);

    efis.verticalSpeed = (efis.altitude - vs.previousAltitude) / 0.1;

    vs.previousAltitude = efis.altitude;

    //Update Webpage
    sendEFISData();

    efis.sensorTimer = millis();
  }
}


void sendEFISData() {

    if (stratuxData.sEnabled){
      if (vs.scPitchRoll){
        efis.pitch = stratuxData.sPitch;
        efis.roll = stratuxData.sRoll;
      }
      if (vs.scHeading){
        efis.heading = stratuxData.sHeading;
      }
      if (vs.scSlip){
        efis.slip = stratuxData.sSlip;
      }
      efis.groundSpeed = stratuxData.sGroundspeed;
      efis.gForce = stratuxData.sGForce;
    }

    StaticJsonDocument<512> doc;

    // Populate the JSON document with EIS variables
    doc["pitch"] = int(efis.pitch);
    doc["roll"] = int(efis.roll);
    doc["slip"] = int(efis.slip);
    doc["heading"] = int(efis.heading);
    doc["aoa"] = int(efis.aoa);
    doc["airspeed"] = int(efis.airspeed);
    doc["groundSpeed"] = int(efis.groundSpeed);
    doc["altitude"] = int(efis.altitude);
    doc["verticalSpeed"] = int(efis.verticalSpeed);
    // Add more variables as needed

    // Serialize JSON to a string
    String jsonString;
    serializeJson(doc, jsonString);

    // Broadcast the JSON string to all connected clients
    ws.textAll(jsonString);
}


// Define your cagePFD function
void cagePFD() {
    Serial.println("Caging PFD...");
    vs.pitchCageOffset = filter.getPitch();
    vs.rollCageOffset = filter.getRoll();
}