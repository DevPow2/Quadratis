#include "Communication.h"

Communication::Communication() //constructor
{
}

Communication::~Communication() //deconstructor
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
        return Serial2.readString();
    }
    return "";
}

void Communication::writeSerial(String message)
{
    String temp = message;
    char tempArray[temp.length()];
    temp.toCharArray(tempArray, temp.length());

    if (Serial2.availableForWrite() > 0)
    {

        Serial2.write(tempArray);
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
