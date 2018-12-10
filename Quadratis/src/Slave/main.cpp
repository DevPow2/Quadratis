#ifdef SLAVE //slave
#include <Arduino.h>
#include "Communication.h"
#include "MPU6050.h"
#include "Speaker.h"

Communication *comm;
MPU6050 *mpu6050;
Speaker *speaker;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    comm = new Communication();
    mpu6050 = new MPU6050();
    speaker = new Speaker();
}

void loop()
{
    if (Serial.available() > 0) //read master
    {

        digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
        delay(1000);                     // wait for a second
        digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
        delay(1000);
    }

    // put your main code here, to run repeatedly:
    // comm.Encode();
    //mpu6050.getSensorData();
    // speaker->setMusic();
    delay(10000);
}
#endif
