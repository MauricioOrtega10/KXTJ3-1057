#include <Arduino.h>
#include "kxtj3-1057.h"

void setup()
{
  Serial.begin(115200);
  delay(1000); // wait until serial is open...

  if (IMU.begin() == IMU_SUCCESS) 
  {
    Serial.println("IMU initialized.");
  } 
  else 
  {
    Serial.println("Failed to initialize IMU.");
    while(true); // stop running sketch if failed
  }

  uint8_t readData = 0;

  // Get the ID:
  if (IMU.readRegister(&readData, KXTJ3_WHO_AM_I) ==
  IMU_SUCCESS) {
  Serial.print("Who am I? 0x");
  Serial.println(readData, HEX);
  } else {
    Serial.println("Communication error, stopping.");
	while(true); // stop running sketch if failed
  }
}

void loop()
{
  // Take IMU out of standby
  IMU.standby(false);

  uint8_t dataLowRes = 0;

  if (IMU.readRegister(&dataLowRes, KXTJ3_XOUT_H) ==
  IMU_SUCCESS) {
    Serial.print(" Acceleration X RAW = ");
    Serial.println((int8_t)dataLowRes);

    // Read accelerometer data in mg as Float
    Serial.print(" Acceleration X float = ");
    Serial.println(IMU.axisAccel(X), 4);
  }

  if (IMU.readRegister(&dataLowRes, KXTJ3_YOUT_H) ==
  IMU_SUCCESS) {
    Serial.print(" Acceleration Y RAW = ");
    Serial.println((int8_t)dataLowRes);

    // Read accelerometer data in mg as Float
    Serial.print(" Acceleration Y float = ");
    Serial.println(IMU.axisAccel(Y), 4);
  }

  if (IMU.readRegister(&dataLowRes, KXTJ3_ZOUT_H) ==
  IMU_SUCCESS) {
    Serial.print(" Acceleration Z RAW = ");
    Serial.println((int8_t)dataLowRes);

    // Read accelerometer data in mg as Float
    Serial.print(" Acceleration Z float = ");
    Serial.println(IMU.axisAccel(Z), 4);
  }

  // Put IMU back into standby
  IMU.standby(true);

  // Delay so serial data is human readable
  delay(1000);
}