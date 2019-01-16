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

    xTaskCreatePinnedToCore(core0Loop, "Workload0", 2000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload1", 10000, NULL, 1, &TaskB, 1);
}

void loop() {} //Dont use this

void core0Loop(void *parameter)
{

    Snake *snake = new Snake(new Display()); //initializes the snake in the constructor
    while (true)
    {
        // snake->moveUp();
        // vTaskDelay(200);
        // snake->moveRight();
        // vTaskDelay(200);
        // snake->moveDown();
        // vTaskDelay(200);
        snake->moveRight();
        // snake->moveDown();
        // snake->moveLeft();

        

        // snake->moveUp();
        // snake->moveLeft();
        //     comm->writeSerial("play song 1,");
        //    vTaskDelay(50);
        //    comm->writeSerial("play song 2,");
      //  vTaskDelay(200);
       // snake->moveUp();
        // vTaskDelay(50);
        // snake->moveUp();
        // vTaskDelay(50);
        // snake->moveUp();
        // vTaskDelay(50);
        // snake->moveUp();
        // vTaskDelay(50);
        // snake->moveDown();
        // vTaskDelay(50);
        // snake->moveDown();
        // vTaskDelay(50);
        // snake->moveDown();
        // vTaskDelay(50);
        // snake->moveDown();
        // vTaskDelay(50);
        // snake->moveLeft();
        vTaskDelay(50);
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
