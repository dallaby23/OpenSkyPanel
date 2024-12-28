//*****************************************************************
//*************************Debug Values****************************
//*****************************************************************
void debug() {
  if (millis() - vs.debugTimer >= vs.debugFreq) {
    /*
    Serial.print("pitch: ");
    Serial.print(efis.pitch, 0);
    Serial.print(" , roll: ");
    Serial.print(efis.roll, 0);
    Serial.print(" , heading: ");
    Serial.print(efis.heading, 0);
    Serial.print(" , altitude: ");
    Serial.print(efis.altitude, 0);
    Serial.print(" , altimeterSet: ");
    Serial.print(vs.altimeterSetting);
    Serial.print(" , Voltage: ");
    Serial.print(eis.vVolt);
    Serial.print(" , Current: ");
    Serial.print(eis.vCurrent, 3);
    */
    Serial.print(" , WTemp: ");
    Serial.print(eis.vWTemp);
    Serial.print(" , OPressure: ");
    Serial.print(eis.vOPressure, 2);
    /*
    Serial.print(" , Airspeed: ");
    Serial.print(efis.airspeed, 4);
    Serial.print(" , AoA: ");
    Serial.print(efis.aoa, 4);
    Serial.print(" , Hobbs: ");
    Serial.print(eis.hours);
    Serial.print(":");
    if (eis.minutes < 10) {
      Serial.print("0");
    }
    Serial.print(eis.minutes);
    /*
    Serial.print(" , apEngage: ");
    Serial.print(vs.apEngage);
    Serial.print(" , apWingLeveler: ");
    Serial.print(vs.apWingLeveler);
    Serial.print(" , apRollCommand: ");
    Serial.print(ap.apRollCommand);
    Serial.print(" , aileronAngle: ");
    Serial.print(ap.trimTabAileronAngle);
    */

    
    Serial.print(", aoaRaw: ");
    Serial.print(efis.aoaRaw);
    Serial.print(", airspeedRaw: ");
    Serial.print(efis.airspeedRaw);
    

    Serial.println("");
    vs.debugTimer = millis();
  }
}