#ifndef GyroAcc_H
#define GyroAcc_H

#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#define NOISE 1000
#define TRESHOLDVALUE 25000
#define DEPTH 10
#define AXES 3
#define X 0
#define Y 1
#define Z 2
#define INTERVAL 1

class GyroAcc
{
  // Access specifier
public:
  // Data Members
  // string geekname;

  // Member Functions()
  GyroAcc();
  ~GyroAcc();
  void getSensorData();
  boolean getShaking();

private:
  MPU6050 accelgyro;

  int screenOff = 0;
  int16_t lastTop = 0;
  int16_t lastDal = 0;
  unsigned long dal[DEPTH][AXES] = {{0, 0}};
  unsigned long top[DEPTH][AXES] = {{0, 0}};

  int topCounter = 0;
  int dalCounter = 0;

  long previousMillis = 0;

  boolean topMode = true;

  void getAcceleration(int16_t accData[3]);
  void getGyro(int16_t gyroData[3]);
  boolean handleShake(unsigned long dal[DEPTH][AXES], unsigned long top[DEPTH][AXES]);
  unsigned long getDal(int16_t x);
  unsigned long getTop(int16_t x);
};

#endif
