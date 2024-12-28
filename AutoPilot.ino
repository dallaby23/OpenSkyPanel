//****************************************************************************
//******************Autopilot functions***************************************
//****************************************************************************

void updateAutopilot(float currentPitch, float currentRoll) {

  if (millis() - ap.apTimer >= ap.apFreq) {

    unsigned long now = millis();
    ap.apDeltaTime = (now - ap.apLastUpdate) / 1000.0;
    if (ap.apDeltaTime <= 0.0) ap.apDeltaTime = 0.1;
    ap.apLastUpdate = now;

    float headingCommand = 0.0;
    float altitudeCommand = 0.0;

    // HEADING HOLD / WING LEVELER
    if (!vs.apWingLeveler) {

      float currentHeading = efis.heading;
      float headingError = vs.headingBug - currentHeading;
      if (headingError > 180) headingError -= 360;
      if (headingError < -180) headingError += 360;

      float headingDTerm = (headingError - ap.apHeadingPrevError) / ap.apDeltaTime;
      headingCommand = vs.apHeadingKp * headingError + vs.apHeadingKd * headingDTerm;
      ap.apHeadingPrevError = headingError;

      float rollError = -currentRoll;
      float rollDTerm = (rollError - ap.apHeadingPrevError) / ap.apDeltaTime;
      headingCommand = vs.apHeadingKp * rollError + vs.apHeadingKd * rollDTerm;
      ap.apHeadingPrevError = rollError;

    } else {
      float rollError = -currentRoll;
      float rollDTerm = (rollError - ap.apHeadingPrevError) / ap.apDeltaTime;
      headingCommand = vs.apHeadingKp * rollError + vs.apHeadingKd * rollDTerm;
      ap.apHeadingPrevError = rollError;
    }

    // ALTITUDE HOLD
    if (vs.apAltitudeHold) {
      float currentAltitude = efis.altitude;
      float altitudeError = vs.altitudeBug - currentAltitude;

      float altitudeDTerm = (altitudeError - ap.apAltitudePrevError) / ap.apDeltaTime;
      altitudeCommand = vs.apAltitudeKp * altitudeError + vs.apAltitudeKd * altitudeDTerm;
      ap.apAltitudePrevError = altitudeError;

      // Adjust altitude command based on vertical speed limits
      if (efis.verticalSpeed > vs.maxVertical && altitudeCommand > 0) {
        altitudeCommand *= (vs.maxVertical / efis.verticalSpeed);  // Scale down to limit climb rate
      }
      if (efis.verticalSpeed < -vs.maxVertical && altitudeCommand < 0) {
        altitudeCommand *= (vs.maxVertical / -efis.verticalSpeed);  // Scale up to limit descent rate
      }

      // Adjust altitude command based on airspeed limits
      if (efis.airspeed < vs.airspeedBug) {
        float airspeedFactor = efis.airspeed / vs.airspeedBug;
        altitudeCommand *= airspeedFactor;  // Scale down as airspeed approaches the bug value
      }
    } else {
      altitudeCommand = 0.0;
    }


    headingCommand = constrain(headingCommand, -vs.maxRoll, vs.maxRoll);
    altitudeCommand = constrain(altitudeCommand, -vs.maxPitch, vs.maxPitch);

    ap.apRollCommand = headingCommand;
    ap.apPitchCommand = altitudeCommand;

    //float desiredAileronTrimAngle = apRollCommand * 9.0;
    ap.trimTabAileronAngle = ap.apRollCommand * 9.0;
    float desiredElevatorTrimAngle = ap.apPitchCommand * 9.0;

    ap.trimTabElevatorAngle = smoothServoMovement(ap.trimTabElevatorAngle, desiredElevatorTrimAngle, vs.apServoAdjustmentRate, ap.apDeltaTime);

    ap.trimTabAileronAngle = constrain(ap.trimTabAileronAngle, -90.0, 90.0);
    ap.trimTabElevatorAngle = constrain(ap.trimTabElevatorAngle, -90.0, 90.0);

    float servoAileronOutputDeg;
    float servoElevatorOutputDeg;
    uint16_t pulseLen;
    // Use config.apEngage etc.
    if (!vs.apEngage) {
      servoAileronOutputDeg = 90.0 + vs.rollTrim;
      servoElevatorOutputDeg = 90.0 + vs.pitchTrim;
    } else {
      servoAileronOutputDeg = ((ap.trimTabAileronAngle + 90.0) + vs.rollTrim);
      servoElevatorOutputDeg = ((ap.trimTabElevatorAngle + 90.0) + vs.pitchTrim);
    }

    pulseLen = map((uint16_t)servoAileronOutputDeg, 0, 180, vs.servoMin, vs.servoMax);
    servo.setPWM(8, 0, pulseLen);

    pulseLen = map((uint16_t)servoElevatorOutputDeg, 0, 180, vs.servoMin, vs.servoMax);
    servo.setPWM(7, 0, pulseLen);

    //Update timer
    ap.apTimer = millis();
  }
}