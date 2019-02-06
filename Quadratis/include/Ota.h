#ifndef OTA_H
#define OTA_H

#include <ArduinoOTA.h>
#include <WiFiUdp.h>

class Ota
{

public:
    Ota();
    void handleOTA();
};

#endif