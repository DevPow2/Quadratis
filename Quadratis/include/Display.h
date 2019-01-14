#ifndef Display_H
#define Display_H

#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define AMOUNT_DISPLAYS 1
#define MOSI 23
#define SCK 18

#define MAX_SPI_FREQUENCY 80000000
#define AMOUNT_OF_SPI 5 //remove when everything is done
#define SPI_FREQUENCY ((MAX_SPI_FREQUENCY / AMOUNT_OF_SPI) - 2000000)

class Display
{
public:
  Display();
  void update();
  int i = 0;
  ~Display();
  void clearPixel(int x, int y, int color);
  //int startPos = 100;
  void drawRect(int x, int y, int w, int h, int color);
  Adafruit_ILI9341 *displayArr[AMOUNT_DISPLAYS] = {0};
  //240 x 320
};

#endif
