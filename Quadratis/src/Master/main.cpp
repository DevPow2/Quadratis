#ifdef MASTER
#include <Arduino.h>

#include "Display_Master.h"
#include "Snake.h"
#include "FlappyBird.h"
#include "Game.h"
#include "Communication.h"

#include <Wifi.h>
#include <WiFiMulti.h>
#include "Ota.h"

WiFiMulti wifiMulti;

TaskHandle_t TaskA, TaskB;
void core0Loop(void *parameter);
void core1Loop(void *parameter);
Communication *comm;
Display_Master *display;
Game *game;
boolean playingGame = false;

void setup()
{
    Serial.begin(9600); //Debug serial
    Serial.println("----------------------------------------------");

    setupWifi();

    comm = Communication::getInstance();
    comm->writeSerial(",");

    display = new Display_Master();

    // for (int i = 0; i < 30; i++)
    // {
    //     Adafruit_ILI9341 disp5 = Adafruit_ILI9341(i, 5); //werkt
    //     disp5.begin();
    //     delay(5000);
    //     disp5.fillScreen(ILI9341_OLIVE);
    //     Serial.println()
    // // }

    // game->addGame(0,  new Snake(comm, display));
    // game->addGame(1,  new FlappyBird(display));
    xTaskCreatePinnedToCore(core0Loop, "Workload0", 10000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    xTaskCreatePinnedToCore(core1Loop, "Workload1", 10000, NULL, 1, &TaskB, 1);
}

void loop() {} //Dont use this

void core0Loop(void *parameter)
{

    //   Adafruit_ILI9341 disp3 = Adafruit_ILI9341(25, 5); //checked
    //   disp3.begin();
    //   disp3.fillScreen(ILI9341_PURPLE);

    // Ota ota;
    while (true)
    {

        //     comm->writeSerial(",");
        //     String message = comm->readSerial();
        //     if (strstr(message.c_str(), "Schudden"))
        //     {
        //         playingGame = false;
        //         game = NULL;
        //     }

        //     if (strstr(message.c_str(), "Play"))
        //     {
        //         game->setCurrentGame(0);
        //         playingGame = true;
        //     }
        //     if (playingGame)
        //     {
        //         game->getCurrentGame()->run();
        //     }
        //     ota.handleOTA();
            vTaskDelay(500);
    }
}

void core1Loop(void *parameter)
{
    while (true)
    {
        //         String message = comm->readSerial();
        //         // Serial.print(".");
        //         /*if(message != "")

        //         {
        //             Serial.println("message received:");
        //             comm->writeSerial(",");
        //             Serial.println(message);
        //             Serial.println("master");
        //         }*/
        vTaskDelay(50);
    }
}

void setupWifi()
{
    wifiMulti.addAP("KoensHotspot", "koen2008");
    if (wifiMulti.run() == WL_CONNECTED)
    {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

#endif
