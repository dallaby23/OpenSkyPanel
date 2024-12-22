  Hey guys, check out my project. I hope you find this interesting and functional. If you use it please let me know. Obviously while this is a functional instrument it is ultimately for educational purposes and as backup to your main instruments. I have been using versions of the EIS portion of this for years in a few planes and have found the warning components very helpful and also cleanup of many gauges and wiring. 

  This is completely opensource and free to use. If you want to team up and develop it further please let me know. I do have several plans for its future. I will also be providing video of inflight in the very near future, so stay tuned!! 

EFIS Panel

![image](https://github.com/user-attachments/assets/29588057-1ae5-4e3e-bbde-44c65f2379d1)


OpenSource EFIS/EIS panel based on the esp32 with Web UI
EFIS Panel Functionality includes
1. Artificial Horizon - configured to optionally use internal IMU data or Stratux data if connected
2. Heading Indicator - adjustable headingBug for autopilot heading hold navigation
3. AoA Indicator - configurable stall value
4. Airspeed Indicator - configurable with max value, yellow alert min and max, red alert min and max and airspeedBug value for autopilot navigation limiting
5. Altitude Indicator - configurable with step count and altimeterBug for autopilot altitude hold option. also altimeter setting in inHg
6. VSI Indicator - configurable with step count and min max value
7. Slip Indicator
8. Tach - configurable with max rpm, yellow alert and red alert rpm
9. Settings Btn - Cage PFD - Use Stratux Data
10. Autopilot - options for engage, altitude hold (altimeterBug), wing level or heading hold (headingBug)
11. Trim - adjustment for pitch and roll trim
12. EFIS Btn - doubles as alert warning info for EIS data and click to open EIS Panel


EIS Panel

![image](https://github.com/user-attachments/assets/49c24916-a923-46a1-b287-f5374f1ae233)

EIS Panel Functionality includes
1. 8 Configurable sensors - (Oil Pressure, Oil Temp, Water Temp, CHT, Voltage, Current, Fuel level, Fuel Pressure, etc) - configurable with Min, Max, YellowMin, YellowMax, RedMin, and RedMax values
2. Alert Monitoring - When sensors violate configurable thresholds alert system is triggered. Red Flashing bar at bottom of screen and flashing red button on EFIS Panel
3. Hobbs - Engine runtime based on Oil Pressure


Advanced Settings

![image](https://github.com/user-attachments/assets/7a87254c-51dc-438e-9c88-614465ce62b6)

Advanced Settings Page
1. Provides realtime access to all adjustable variables in backend system.


