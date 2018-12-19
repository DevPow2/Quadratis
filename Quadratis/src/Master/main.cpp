#ifdef MASTER //master
#include <Arduino.h>

#include "Communication.h"

#define LOOP while(true)

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
    int i  = 0;
    Communication *comm = Communication::getInstance();
    LOOP
    {
        //Serial.print(".");
        comm->writeSerial("play song 1,");
        i++;
        vTaskDelay(10);
        comm->writeSerial("play song 2,");
        vTaskDelay(10);
    }
}

void core1Loop(void *parameter) //Gyro loop
{
    LOOP
    {
        delay(1);
    }
}

#endif
