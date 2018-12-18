#ifdef MASTER //master
#include <Arduino.h>

#include "Communication.h"

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
    
    Communication *comm = Communication::getInstance();
    while (true)
    {
        
        comm->writeSerial("play song 1");
        delay(1);
    }
}

void core1Loop(void *parameter) //Gyro loop
{
    
    while (true)
    {
       
        delay(1);
    }
}

#endif
