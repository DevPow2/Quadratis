#ifdef SLAVE
#include <Arduino.h>

#include "Communication.h"
#include "MPU6050.h"
#include "Speaker.h"

TaskHandle_t TaskA, TaskB;
void core0Loop(void *parameter);
void core1Loop(void *parameter);

void setup()
{
    Serial.begin(9600);                      //Debug serial
    Serial2.begin(9600, SERIAL_8N1, 16, 17); //Hardware serial

    //todo
    xTaskCreatePinnedToCore(core0Loop, "Workload1", 1000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload2", 1000, NULL, 1, &TaskB, 1);
}

void loop() {}

void core0Loop(void *parameter)
{
    Speaker *speaker = new Speaker();
    while (true)
    {
        Communication *comm = Communication::getInstance();
        String message = comm->readSerial();
        int songNumber = comm->split(message, ',', 0).toInt();
        speaker->playSong(songNumber);
    }
}

void core1Loop(void *parameter)
{
    //MPU6050 *mpu6050 = new MPU6050();

    while (true)
    {
        //workLoad();
        delay(10);
    }
}

#endif
