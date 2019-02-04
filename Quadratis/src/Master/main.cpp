#ifdef MASTER //master
#include <Arduino.h>

#include "Display.h"
#include "Snake.h"
#include "FlappyBird.h"
#include "Game.h"
#include "Communication.h"
// #include "Image_logo.h"



TaskHandle_t TaskA, TaskB;
void core0Loop(void *parameter);
void core1Loop(void *parameter);
Communication *comm;
Display *display;
Game *game;
boolean playingGame = false;

void setup()
{
    Serial.begin(9600); //Debug serial
    Serial.println("----------------------------------------------");
    comm = Communication::getInstance();
    
    display = new Display();
    
    // Image image = logoImage;
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
    {
        // display->bmpDraw(5, image, 0, 0);
        Serial.println(i);
    }
    // delay(10000);
    // game->addGame(0,  new Snake(display));
   // game->addGame(1,  new FlappyBird(display));
    xTaskCreatePinnedToCore(core0Loop, "Workload0", 20000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload1", 10000, NULL, 1, &TaskB, 1);
}

void loop() {} //Dont use this

void core0Loop(void *parameter)
{
    
    int menuCounter = 0;;
    while (true)
    {
        // Serial.println("1");
        String message = comm->readSerial();
        if (message == "KABOEM KAPOT")
        {
            playingGame = false;
            game = NULL;
        }

        if (!playingGame)
        {
            // display->drawRect(5, 0,0,120,240,ILI9341_BLUE);
            // display->drawRect(5,180,0,180,240,ILI9341_BLUE);
            // display->bmpDraw(5, game->getCurrentGame()->getInfo().image, 0, 0);
            Coordinates coords = display->getTouch(0);
            Serial.print("x : ");
            Serial.print(coords.x);
            Serial.print("     y :");
            Serial.println(coords.y);
            // if (coords.x > 0 && coords.y > 0)
            // {
            //     if(coords.x > 120 && coords.x < 180) 
            //     {
            //         game->setCurrentGame(menuCounter);
            //         playingGame = true;
            //     }
            //     else 
            //     {
            //         menuCounter++;
            //         if (menuCounter > AMOUNT_GAMES) menuCounter = 0;
            //         game->setCurrentGame(menuCounter);
            //     }
            // }
        }
        if (playingGame)
        {
            game->getCurrentGame()->run();
        }
        vTaskDelay(10);
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
