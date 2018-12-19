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
    Speaker *speaker = new Speaker();
    
    LOOP
    {
        // TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
        // TIMERG0.wdt_feed=1;
        // TIMERG0.wdt_wprotect=0;

        String message = comm->readSerial();
        if(message != "")
        { 
            Serial.println(message);
            Serial.println("t");
        }
        if(strstr(message.c_str(), "play song 2"))
        {
            Serial.println("test");
            // int songNumber = comm->split(message, ',', 0).toInt(); //Gets the songnumber from the song command sent over the serial
            // speaker->playSong(songNumber);
        }
        vTaskDelay(10);
    }
}

void core1Loop(void *parameter) //Gyro loop
{
    Communication *comm = Communication::getInstance();
    GyroAcc *gyroAcc = new GyroAcc();
    
    LOOP
    {
        // TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
        // TIMERG0.wdt_feed=1;
        // TIMERG0.wdt_wprotect=0;

        if(gyroAcc->getShaking())
        {
            comm->writeSerial("er is geschudt");
        }
        vTaskDelay(10);
    }
}

#endif
