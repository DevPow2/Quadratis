#ifndef Display_H
#define Display_H

#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define AMOUNT_DISPLAYS 4
#define MOSI 23
#define SCK 18

class Display
{
    // Access specifier
  public:
    // Data Members
    // string geekname;
    // Member Functions()
    Display();
    ~Display();
    void update();
  private:
    Adafruit_ILI9341* displays[AMOUNT_DISPLAYS] = {0};

};

#endif
