#ifdef MASTER //master
#include <Arduino.h>

#include "Communication.h"
#include "Snake.h"
#include "Display.h"

TaskHandle_t TaskA, TaskB;
void core0Loop(void *parameter);
void core1Loop(void *parameter);
Communication *comm;
void setup()
{
    Serial.begin(9600); //Debug serial
    comm = Communication::getInstance();

    xTaskCreatePinnedToCore(core0Loop, "Workload0", 50000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload1", 50000, NULL, 1, &TaskB, 1);
}

void loop() {} //Dont use this

void core0Loop(void *parameter)
{

    Snake *snake = new Snake(new Display()); //initializes the snake in the constructor

    snake->generateSnack();
   snake->move(10);
   snake->move(10);
   snake->move(10);

    while (true)
    {
        if (snake->collision() == true)
        {
            Serial.print("loser");
        }

        snake->move(10);

        //     comm->writeSerial("play song 1,");
        //    vTaskDelay(50);
        //    comm->writeSerial("play song 2,");
        vTaskDelay(100);
    }
}

void core1Loop(void *parameter)
{
    while (true)
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
