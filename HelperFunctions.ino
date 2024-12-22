//*****************************************************************
//*************************Helper Functions************************
//*****************************************************************
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void listLittleFSFiles() {
  Serial.println("Listing files in LittleFS:");
  File root = LittleFS.open("/");
  if (!root || !root.isDirectory()) {
    Serial.println("Failed to open directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    Serial.print("File: ");
    Serial.print(file.name());
    Serial.print(", Size: ");
    Serial.println(file.size());
    file = root.openNextFile();
  }
}

float readChannel1(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc1.setCompareChannels(channel);
  voltage = adc1.getResult_V();
  return voltage;
}

float readChannel2(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc2.setCompareChannels(channel);
  voltage = adc2.getResult_V();
  return voltage;
}

float calculateTemperature(float vOut) {
  const float Vcc = 4.54;
  const float R1 = 21300.0;
  float R2 = (vOut * R1) / (Vcc - vOut);

  const float A = 0.001291;
  const float B = 1.378e-4;
  const float C = 4.747e-7;

  float lnR = log(R2);
  float tempK = 1.0 / (A + B * lnR + C * pow(lnR, 3));

  float tempF = tempK * 9.0 / 5.0 - 459.67;
  int tempF_int = (int)(tempF + 0.5);

  return tempF_int;
}

float readPressure(float voltage) {
  return 25.0 * voltage - 12.5;
}

float smoothServoMovement(float currentAngle, float targetAngle, float rate, float deltaTime) {
  float angleDifference = targetAngle - currentAngle;
  return currentAngle + angleDifference * (rate * deltaTime);
}


void copySensorLabel(char* destination, size_t destSize, const char* source) {
  if (source) {
    strncpy(destination, source, destSize - 1);
    destination[destSize - 1] = '\0'; // Ensure null-termination
  } else {
    // If source is null, set to a default value or clear the string
    strncpy(destination, "default", destSize - 1);
    destination[destSize - 1] = '\0';
  }
}
