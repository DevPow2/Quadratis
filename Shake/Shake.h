#ifndef SHAKE_H
#define SHAKE_H

#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#define NOISE 1000
#define TRESHOLDVALUE 30000
#define DEPTH 10
#define AXES 3
#define X 0
#define Y 1
#define Z 2
#define INTERVAL 1

void setupShake();
boolean getShaking();
boolean handleShake(unsigned long dal[DEPTH][AXES], unsigned long top[DEPTH][AXES]);
unsigned long getDal(int16_t x);
unsigned long getTop(int16_t x);


#endif
