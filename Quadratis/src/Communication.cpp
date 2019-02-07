#include "Communication.h"

Communication::Communication()
{
    Serial2.begin(9600, SERIAL_8N1, TX_COMMUNICATION, RX_COMMUNICATION); //Hardware serial
}

Communication::~Communication()
{
}

/* Null, because instance will be initialized on demand. */
Communication *Communication::instance = 0;

Communication *Communication::getInstance()
{
    if (instance == 0)
    {
        instance = new Communication();
    }

    return instance;
}

String Communication::readSerial()
{
    if (Serial2.available() > 0)
    {
        //char terminator = ',';
        String data = Serial2.readStringUntil((char)',');
        data.trim();
        Serial.print("Incoming data : ");
        Serial.println(data);
        return data;
    }
    return "";
}

void Communication::writeSerial(String message)
{
    // char tempArray[temp.length() + 1];
    // temp.toCharArray(tempArray, temp.length());

    if (Serial2.available() > 0)
    {
        Serial2.println(message);
    }
}
