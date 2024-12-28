//*****Includes*****
#include <Wire.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <ADS1115_WE.h>
#include <INA226.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <Adafruit_AHRS.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_LSM6DSL.h>
#include <ArduinoJson.h>
#include <Adafruit_PWMServoDriver.h>
#include <string.h>
#include "Adafruit_Sensor_Calibration.h"
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <tinyCore.hpp>

//*****Setup Multithreading
static tinyCore tc;
uint32_t delayMsec = 10;

//*****Setup IMU
Adafruit_Sensor *accelerometer, *gyroscope, *magnetometer;
Adafruit_NXPSensorFusion filter;
//Adafruit_Madgwick filter;
Adafruit_LIS3MDL lis3mdl;
Adafruit_LSM6DSL lsm6ds;

#ifdef ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM
Adafruit_Sensor_Calibration_EEPROM cal;
#else
Adafruit_Sensor_Calibration_SDFat cal;
#endif

//*****Setup I2C connections*****
ADS1115_WE adc1 = ADS1115_WE(0x48);
ADS1115_WE adc2 = ADS1115_WE(0x4A);
INA226 ina(0x40);
Adafruit_BMP3XX bmp;
Adafruit_PWMServoDriver servo = Adafruit_PWMServoDriver(0x41);

//*****Setup Webserver*****
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

//*****Setup WiFi*****
struct Wifi {
  String SSID = "smile";
  String Password = "sm1le8a8y";
  String StaticIP = "";
  String Gateway = "";
  String Subnet = "";
};
Wifi wifi;

IPAddress staticIP(192, 168, 10, 5);
IPAddress gateway(192, 168, 10, 1);
IPAddress subnet(255, 255, 255, 0);

//******Setup RPM
volatile unsigned long last_pulse_time = 0;

//*****Realtime Variables EFIS*****
struct Efis {
  float pitch = 0;
  float roll = 0;
  float heading = 0;
  float airspeed = 0;
  float airspeedRaw = 0;
  float airspeedSmooth = 0;
  float groundSpeed = 0;
  float altitude = 0;
  float verticalSpeed = 0;
  float slip = 0;
  float rpm = 0;
  float aoa = 0;
  float aoaRaw = 0;
  float aoaSmooth = 0;
  float gForce = 0.0;
  float gx, gy, gz;
  int efisFreq = 80;
  int imuFreq = 40;
  unsigned long imuTimer;
  unsigned long sensorTimer;
};
Efis efis;


//*****Realtime Variables EIS*****
struct Eis {
  float vOPressureRaw;
  float vOPressure = 0.0;
  float vFPressureRaw;
  float vFPressure = 0.0;
  float vOTempRaw;
  float vOTemp = 0.0;
  float vWTempRaw;
  float vWTemp = 0.0;
  float vCTempRaw;
  float vCTemp = 0.0;
  float vVoltRaw;
  float vVolt = 0.0;
  float vCurrentRaw;
  float vCurrent = 0.0;
  float vFuelLevelRaw;
  float vFuelLevel = 0.0;
  int hours = 0;
  int minutes = 0;
  unsigned long timer;
  long engineTime = 0;
  int eisFreq = 400;
};
Eis eis;


//*****Web Configuration Variables*****
struct Vs {

  //Cage
  float pitchCageOffset = 0;
  float rollCageOffset = 0;

  //Heading
  int headingBug = 0;

  //AoA
  int aoaStallVal = 4;

  //Airspeed
  int airspeedBug = 80;
  int airspeedMax = 150;
  int airspeedYellowMin = 50;
  int airspeedYellowMax = 100;
  int airspeedRedMin = 40;
  int airspeedRedMax = 120;

  //VSI
  int vsiScaleVal = 2000;
  int vsiSegments = 4;

  //Altimeter
  int altitudeStep = 100;
  int altitudeBug = 2000;
  float altimeterSetting = 29.92;  //1013.21;
  int previousAltitude = 0;

  //RPM
  int rpmMax = 6300;
  int rpmYellow = 5600;
  int rpmRed = 5800;

  // Autopilot related variables
  bool apEngage = false;
  bool apAltitudeHold = false;
  bool apWingLeveler = false;
  float maxVertical = 200.0;
  float maxPitch = 10.0;
  float maxRoll = 10.0;

  // PID Gains
  float apHeadingKp = 0.2;
  float apHeadingKd = 0.00;
  float apAltitudeKp = 0.5;
  float apAltitudeKd = 0.05;

  //Servo
  int servoMin = 150;
  int servoMax = 500;
  int servoFreq = 50;
  float apServoAdjustmentRate = 0.9;
  int pitchTrim = 0;
  int rollTrim = 0;
  int trimMin = -30;
  int trimMax = 30;

  //EIS
  char sensor1Label[20] = "default";
  int sensor1Min = 0;
  int sensor1Max = 100;
  int sensor1YellowMin = 10;
  int sensor1YellowMax = 80;
  int sensor1RedMin = 5;
  int sensor1RedMax = 95;
  bool sensor1Visible = true;

  char sensor2Label[20] = "default";
  int sensor2Min = 0;
  int sensor2Max = 100;
  int sensor2YellowMin = 10;
  int sensor2YellowMax = 80;
  int sensor2RedMin = 5;
  int sensor2RedMax = 95;
  bool sensor2Visible = true;

  char sensor3Label[20] = "default";
  int sensor3Min = 0;
  int sensor3Max = 100;
  int sensor3YellowMin = 10;
  int sensor3YellowMax = 80;
  int sensor3RedMin = 5;
  int sensor3RedMax = 95;
  bool sensor3Visible = true;

  char sensor4Label[20] = "default";
  int sensor4Min = 0;
  int sensor4Max = 100;
  int sensor4YellowMin = 10;
  int sensor4YellowMax = 80;
  int sensor4RedMin = 5;
  int sensor4RedMax = 95;
  bool sensor4Visible = true;

  char sensor5Label[20] = "default";
  int sensor5Min = 0;
  int sensor5Max = 100;
  int sensor5YellowMin = 10;
  int sensor5YellowMax = 80;
  int sensor5RedMin = 5;
  int sensor5RedMax = 95;
  bool sensor5Visible = true;

  char sensor6Label[20] = "default";
  int sensor6Min = 0;
  int sensor6Max = 100;
  int sensor6YellowMin = 10;
  int sensor6YellowMax = 80;
  int sensor6RedMin = 5;
  int sensor6RedMax = 95;
  bool sensor6Visible = true;

  char sensor7Label[20] = "default";
  int sensor7Min = 0;
  int sensor7Max = 100;
  int sensor7YellowMin = 10;
  int sensor7YellowMax = 80;
  int sensor7RedMin = 5;
  int sensor7RedMax = 95;
  bool sensor7Visible = true;

  char sensor8Label[20] = "default";
  int sensor8Min = 0;
  int sensor8Max = 100;
  int sensor8YellowMin = 10;
  int sensor8YellowMax = 80;
  int sensor8RedMin = 5;
  int sensor8RedMax = 95;
  bool sensor8Visible = true;

  //Hobbs
  float hobbs;

  //*****Debug*****
  int debugFreq = 100;
  unsigned long debugTimer;

  //*****Stratux Settings
  bool scPitchRoll = false;
  bool scHeading = false;
  bool scSlip = false;
};
Vs vs;


// ***** Autopilot Variables *****
struct Ap {

  float apHeadingPrevError = 0.0;
  float apAltitudePrevError = 0.0;
  float apRollCommand = 0.0;
  float apPitchCommand = 0.0;
  float trimTabAileronAngle = 0.0;
  float trimTabElevatorAngle = 0.0;
  unsigned long apLastUpdate = 0;
  float apDeltaTime = 0.0;
  unsigned long apTimer;
  int apFreq = 50;
};
Ap ap;

//Stratux Variables
struct StratuxData {
  bool sEnabled = false;
  float sPitch = 0.0;
  float sRoll = 0.0;
  float sHeading = 0.0;
  float sGroundspeed = 0.0;
  float sSlip = 0.0;
  float sGForce = 0.0;
};
StratuxData stratuxData;


//**********************Interrupts
void IRAM_ATTR calcRPM() {
  unsigned long current_time = micros();  // Current time in microseconds
  unsigned long pulse_interval = current_time - last_pulse_time;

  if (pulse_interval > 0) {                        // Avoid division by zero
    efis.rpm = 60.0 * 1000000.0 / pulse_interval;  // Calculate RPM
  }

  last_pulse_time = current_time;  // Update for the next pulse
}


//*****************************************************************
//*************************Setup Routine***************************
//*****************************************************************
void setup(void) {

  //Setup Wire Library
  Wire.begin();

  //Setup Serial
  Serial.begin(115200);
  delay(4000);

  //Initialize LittleFS
  if (!LittleFS.begin(true)) {
    Serial.println("Failed to initialize LittleFS");
    return;
  }
  Serial.println("LittleFS initialized successfully");
  listLittleFSFiles();

  //Load settings from /settings.json
  loadSettings();

  //Setup BMP pressure I2C Sensor
  if (!bmp.begin_I2C()) {
    Serial.println("Pressure sensor failed to initialize");
    delay(2000);
  }
  bmp.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_DISABLE);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  //Load Calibration
  if (!cal.begin()) {
    Serial.println("Failed to initialize calibration helper");
  } else if (!cal.loadCalibration()) {
    Serial.println("No calibration loaded/found");
  }

  //Setup IMU Sensors
  if (!lsm6ds.begin_I2C()) {
    Serial.println("Accel/Gyro sensor failed to initialize");
    delay(2000);
  }
  if (!lis3mdl.begin_I2C()) {
    Serial.println("Magnetometer sensor failed to initialize");
    delay(2000);
  }
  accelerometer = lsm6ds.getAccelerometerSensor();
  gyroscope = lsm6ds.getGyroSensor();
  magnetometer = &lis3mdl;
  lsm6ds.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  lsm6ds.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
  lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
  lsm6ds.setAccelDataRate(LSM6DS_RATE_104_HZ);
  lsm6ds.setGyroDataRate(LSM6DS_RATE_104_HZ);
  lis3mdl.setDataRate(LIS3MDL_DATARATE_1000_HZ);
  lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
  filter.begin(efis.imuFreq);

  //Setup Voltage/Current Sensor
  if (!ina.begin()) {
    Serial.println("Voltage/Current sensor failed to initialize");
    delay(2000);
  }
  ina.setMaxCurrentShunt(1, 0.010);

  //Setup ADC
  if (!adc1.init()) {
    Serial.println("ADC1 sensor failed to initialize");
    delay(2000);
  }
  if (!adc2.init()) {
    Serial.println("ADC2 sensor failed to initialize");
    delay(2000);
  }
  adc1.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc1.setMeasureMode(ADS1115_CONTINUOUS);
  adc1.setCompareChannels(ADS1115_COMP_0_GND);
  adc2.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc2.setMeasureMode(ADS1115_CONTINUOUS);
  adc2.setCompareChannels(ADS1115_COMP_0_GND);


  //Setup Servos
  servo.begin();
  servo.setOscillatorFrequency(27000000);
  servo.setPWMFreq(vs.servoFreq);

  //Setup WiFi
  const unsigned long wifiTimeout = 5000;
  unsigned long wifiStartTime = millis();
  WiFi.begin(wifi.SSID, wifi.Password);
  Serial.println("Attempting to connect to WiFi...");


  while (WiFi.status() != WL_CONNECTED && millis() - wifiStartTime < wifiTimeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nCould not connect to WiFi. Setting up Access Point...");
    WiFi.mode(WIFI_AP);
    WiFi.useStaticBuffers(true);
    WiFi.softAPConfig(staticIP, gateway, subnet);
    WiFi.softAP("Rebel_AP", "rebel", 6, false, 1);
    WiFi.setSleep(false);
    Serial.print("Access Point IP address: ");
    Serial.println(WiFi.softAPIP());
  }

  if (!MDNS.begin("efis")) {
    Serial.println("Error starting mDNS");
    return;
  }
  Serial.println("mDNS started. You can now reach the device at http://efis.local/");
  MDNS.addService("http", "tcp", 80);


  //Setup WebSocket
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);

  // Serve the index.html file from LittleFS
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/index.html", "text/html");
  });
  // Serve the config.html file from LittleFS
  server.on("/config", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/config.html", "text/html");
  });

  server.begin();

  //Setup Timers
  vs.debugTimer = millis();
  eis.engineTime = millis();
  eis.timer = millis();
  efis.sensorTimer = millis();
  efis.imuTimer = millis();
  ap.apTimer = millis();

  //Setup Multithread
  tc.begin((uint32_t)delayMsec);
}

//*****************************************************************
//*************************Main Loop*******************************
//*****************************************************************
void loop(void) {

  //Check Engine Sensors
  read_eis();

  //Check Flight Instrument Sensors
  read_flight();

  //Update autopilot using config variables
  updateAutopilot(efis.pitch, efis.roll);

  //Debug
  //debug();
}

//*****************************************************************
//*********************2nd Thread**********************************
//*****************************************************************
void setupN(void) {
  pinMode(18, INPUT_PULLUP);                                     // Set GPIO as input with pull-up
  attachInterrupt(digitalPinToInterrupt(18), calcRPM, FALLING);  // Trigger on falling edge
}

void loopN(void) {

  //Check and update Stratux Data
  if (stratuxData.sEnabled) {
    fetchStratuxData();
    if (!vs.scPitchRoll || !vs.scHeading || !vs.scSlip) {
      read_IMU();
    }
  } else {
    read_IMU();
  }
}
