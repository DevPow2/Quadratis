#ifdef SLAVE
#include <Arduino.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#include "Communication.h"
#include "GyroAcc.h"
#include "Speaker.h"

#define LOOP while(true)

TaskHandle_t TaskA, TaskB;
void core0Loop(void *parameter);
void core1Loop(void *parameter);
Communication *comm;
void setup()
{
    Serial.begin(9600); //Debug serial
    comm = Communication::getInstance();
    xTaskCreatePinnedToCore(core0Loop, "Workload1", 5000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload2", 5000, NULL, 1, &TaskB, 1);
}

void loop() {} //Dont use this

void core0Loop(void *parameter) //Speaker loop
{
    
    Speaker *speaker = new Speaker();
    // speaker->setVolume(30);
    // speaker->playSong(1);
    LOOP
    {
        String message = comm->readSerial();
        if(message != "")
        { 
            Serial.println(message);
            Serial.println("slave");
            comm->writeSerial(",");
        }
        if(strstr(message.c_str(), "play song 2"))
        {
            Serial.println("test");
            
            // int songNumber = comm->split(message, ',', 0).toInt(); //Gets the songnumber from the song command sent over the serial
            // speaker->playSong(songNumber);
        }
        
        vTaskDelay(1000);
    }
}

void core1Loop(void *parameter) //Gyro loop
{
    GyroAcc *gyroAcc = new GyroAcc();
    LOOP
    {
        if(gyroAcc->getShaking())
        {
            comm->writeSerial("KABOEM KAPOT,");
        }
       // comm->writeSerial("KABOEM KAPOT,");
        vTaskDelay(10);
    }
}

#endif
