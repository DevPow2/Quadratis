#ifndef Display_Slave_H
#define Display_Slave_H

#include <Arduino.h>
#include "App.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Communication.h"
#include <SD.h>

#define SCREEN_X_SIZE 320
#define SCREEN_Y_SIZE 240

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define BUFFPIXEL 20

struct Coordinates
{
  int x;
  int y;
};

class Display_Slave
{

public:
  Display_Slave();

  ~Display_Slave();
  void drawLogo();
  void menu();
  void setTextTFT(int fontSize, String text, int yOffset);
  void setTitleTFT(int fontSize, String text, int yOffset);
  void getTouch();
  void options();
  void customize();

private:
  Adafruit_ILI9341 *display;
  XPT2046_Touchscreen *touchscreen;
  boolean logo = true;
  Communication* comm;
};

#endif
