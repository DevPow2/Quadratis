#include "Communication.h"

Communication::Communication()
{
    Serial2.begin(115200, SERIAL_8N1, TX_COMMUNICATION, RX_COMMUNICATION); //Hardware serial
    Serial2.setTimeout(1);
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
        return data;
    }
    return "";
}


void Communication::writeSerial(String message)
{
    String temp = message;
    // char tempArray[temp.length() + 1];
    // temp.toCharArray(tempArray, temp.length());
    
    if (Serial2.available() > 0)
    {
        Serial2.println(temp);
    }
    
}

String Communication::split(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
