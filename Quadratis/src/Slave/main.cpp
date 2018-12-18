#ifdef SLAVE
#include <Arduino.h>

#include "Communication.h"
#include "GyroAcc.h"
#include "Speaker.h"

TaskHandle_t TaskA, TaskB;
void core0Loop(void *parameter);
void core1Loop(void *parameter);

void setup()
{
    Serial.begin(9600); //Debug serial

    xTaskCreatePinnedToCore(core0Loop, "Workload1", 1000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload2", 1000, NULL, 1, &TaskB, 1);
}

void loop() {} //Dont use this

void core0Loop(void *parameter) //Speaker loop
{
    Speaker *speaker = new Speaker();
    while (true)
    {
        Communication *comm = Communication::getInstance();
        String message = comm->readSerial();
        int songNumber = comm->split(message, ',', 0).toInt(); //Gets the songnumber from the song command sent over the serial
        speaker->playSong(songNumber);
        delay(1);
    }
}

void core1Loop(void *parameter) //Gyro loop
{
    GyroAcc *gyroAcc = new GyroAcc();
    while (true)
    {
        gyroAcc->getShaking();
        delay(1);
    }
}

#endif
