#ifdef MASTER //master
#include <Arduino.h>
#include "Communication.h"

void setup()
{
    Serial.begin(9600); //debug serial
    Serial2.begin(9600, SERIAL_8N1, 16, 17); //communications serial
}

void loop()
{

    Serial2.write("Play song 1"); //tell the slave to play song 1
    delay(1000);
    // String received = "";
    // while (Serial2.available())
    // {
    //     received = Serial2.read();
    //     Serial.println(received);
    // }
}
#endif
