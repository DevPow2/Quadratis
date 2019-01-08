#ifdef MASTER //master
#include <Arduino.h>

#include "Communication.h"
#include "Snake.h"
#include "Display.h"

#define LOOP while(true)

TaskHandle_t TaskA, TaskB;
void core0Loop(void *parameter);
void core1Loop(void *parameter);
Communication *comm;
Display* display;

void setup()
{
    Serial.begin(9600); //Debug serial
    comm = Communication::getInstance();
    display = new Display();
    xTaskCreatePinnedToCore(core0Loop, "Workload0", 50000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload1", 10000, NULL, 1, &TaskB, 1);
    
}

void loop() {} //Dont use this

void core0Loop(void *parameter) 
{
    //Snake *snake = new Snake();
    //snake->moveUp();
    //snake->moveDown();
    
    
    LOOP
    {
        display->update();
    //     comm->writeSerial("play song 1,");
    //    vTaskDelay(50);
    //    comm->writeSerial("play song 2,");
        vTaskDelay(50);
    }
}

void core1Loop(void *parameter) 
{
    
    LOOP
    {
        String message = comm->readSerial(); 
       // Serial.print(".");
        /*if(message != "")
        { 
            Serial.println("message received:");
            comm->writeSerial(",");
            Serial.println(message);
            Serial.println("master");
        }*/
        vTaskDelay(50);
    }
}

#endif
