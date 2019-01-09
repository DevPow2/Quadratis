#ifndef Display_H
#define Display_H

#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define AMOUNT_DISPLAYS 5
#define MOSI 23
#define SCK 18

#define MAX_SPI_FREQUENCY 80000000
#define AMOUNT_OF_SPI 5
#define SPI_FREQUENCY ((MAX_SPI_FREQUENCY / AMOUNT_OF_SPI) - 2000000)

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
