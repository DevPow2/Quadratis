#ifdef SLAVE
#include <Arduino.h>
// #include "soc/timer_group_struct.h"
// #include "soc/timer_group_reg.h"

#include "Communication.h"
#include "GyroAcc.h"
#include "Speaker.h"
#include "Display_Slave.h"

#include <Wifi.h>
#include <WiFiMulti.h>
#include "Wifi_Credentials.h"
#include "Ota.h"

#define LOOP while (true)

WiFiMulti wifiMulti;

TaskHandle_t TaskA, TaskB;
void core0Loop(void *parameter);
void core1Loop(void *parameter);
Communication *comm;
Display_Slave *display_Slave;
GyroAcc *gyroAcc;
Speaker *speaker;

int direction = 5;

void setup()
{
    Serial.begin(9600); //Debug serial
    wifiMulti.addAP(SSID1, PASS1);

    if (wifiMulti.run() == WL_CONNECTED)
    {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }

    comm = Communication::getInstance();
    // display_Slave = new Display_Slave();
    gyroAcc = new GyroAcc();
    speaker = new Speaker();
    speaker->setVolume(30);
    xTaskCreatePinnedToCore(core0Loop, "Workload1", 5000, NULL, 1, &TaskA, 0); //TaskCode, pcName, usStackDepth, uxPriority, pxCreatedTask, xCoreID
    // xTaskCreatePinnedToCore(core1Loop, "Workload2", 5000, NULL, 1, &TaskB, 1);
}

void loop()
{
}

void core0Loop(void *parameter)
{
    Ota ota;
    while (true)
    {
        comm->writeSerial(",");
        String message = comm->readSerial();
        if (message != "")
        {
            Serial.println(message);
        }
        if (strstr(message.c_str(), "Play song"))
        {
            speaker->playSong(1);
            // comm->writeSerial("Command recieved,");
        }
        if (gyroAcc->getShaking())
        {
            Serial.println("er zou nu een bericht worden gestuurd");
            comm->writeSerial("Schudden,");
        }

        int currentDirection = gyroAcc->getDirection();

        if (currentDirection != direction)
        {
            comm->writeSerial("testets,");
            Serial.print("current direction : ");
            Serial.println(currentDirection);
            direction = currentDirection;
        }
        // }
        // Coordinates coords = display_Slave->getTouch(0);
        // if(coords.x > 0 && coords.y > 0)
        // {
        //     comm->writeSerial("Play,");
        // }

        ota.handleOTA();
        vTaskDelay(50);
    }
} //Dont use this

// void core0Loop(void *parameter) //Speaker loop
// {

// }

// void core1Loop(void *parameter) //Gyro loop
// {
//     // GyroAcc *gyroAcc = new GyroAcc();
//     // LOOP
//     // {
//     //     if(gyroAcc->getShaking())
//     //     {
//     //         comm->writeSerial("KABOEM KAPOT,");
//     //     }
//     //    // comm->writeSerial("KABOEM KAPOT,");
//         vTaskDelay(10);
//     // }
// }

#endif
