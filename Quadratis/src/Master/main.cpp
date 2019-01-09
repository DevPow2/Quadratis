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
    
    
    xTaskCreatePinnedToCore(core0Loop, "Workload0", 50000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload1", 50000, NULL, 1, &TaskB, 1);
    
}

void loop() {} //Dont use this

void core0Loop(void *parameter) 
{
    //Snake *snake = new Snake();
    //snake->moveUp();
    //snake->moveDown();
    //display = new Display();
    pinMode(4, OUTPUT);
    Adafruit_ILI9341 display = Adafruit_ILI9341(4,5);
    //  vTaskDelay(50);
    Adafruit_ILI9341 display1 = Adafruit_ILI9341(32,5);
    //  vTaskDelay(50);
    Adafruit_ILI9341 display2 = Adafruit_ILI9341(22,5);
    //  vTaskDelay(50);
    Adafruit_ILI9341 display3 = Adafruit_ILI9341(27,5);
    //  vTaskDelay(50);
    display.begin(2000000);
    //  vTaskDelay(50);
    display1.begin(2000000);
    //  vTaskDelay(50);
    display2.begin(2000000);
    //  vTaskDelay(50);
    display3.begin(2000000);
    //  vTaskDelay(50);
    
    LOOP
    { vTaskDelay(50);
        display.fillScreen(ILI9341_BLUE);
      vTaskDelay(50);
    display1.fillScreen(ILI9341_GREEN);
      vTaskDelay(50);
    display2.fillScreen(ILI9341_RED);
     vTaskDelay(50);
    display3.fillScreen(ILI9341_YELLOW);
        //display->update();
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
