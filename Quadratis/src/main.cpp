#include <Arduino.h>
#include "Communication.h"
#include "MPU6050.h"
#include "Speaker.h"

#if MASTER == 1
Communication* comm;
MPU6050* mpu6050;
Speaker* speaker;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9800);
  comm = new Communication();
  mpu6050 = new MPU6050();
  speaker = new Speaker();
}

void loop() {
  // put your main code here, to run repeatedly:
 // comm.Encode();
  //mpu6050.getSensorData();
  speaker->setMusic();
  delay(10000);
}
#endif

#if MASTER==0
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("adf");
  int test = 0;
  test = 0;
  
}
#endif

