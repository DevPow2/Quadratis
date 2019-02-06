#ifndef Display_Master_H
#define Display_Master_H

#include <Arduino.h>
#include "App.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include <SD.h>

#define AMOUNT_DISPLAYS 5
#define SCREEN_X_SIZE 320
#define SCREEN_Y_SIZE 240

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define BUFFPIXEL 20

#define MAX_SPI_FREQUENCY 80000000
#define AMOUNT_OF_SPI 5 //remove when everything is done
#define SPI_FREQUENCY ((MAX_SPI_FREQUENCY / AMOUNT_OF_SPI) - 2000000)

struct Coordinates
{
  int x;
  int y;
};

class Display_Master
{
  enum Direction{
    A,
    B,
    C,
    D
  };

  struct displayLocation
  {
    int displayNumber;
    Direction direction;
  };

public:
  Display_Master();
  ~Display_Master();  
  void drawPixel(int x, int y, int color);
  int getCurrentDisplay();
  void update();
  void clearPixel(int display, int x, int y, int color);
  void drawRect(int display, int x, int y, int w, int h, int color);
  void drawRectAllDisplays(int x, int y, int w, int h, int color);
  void fillRect(int display, int x, int y, int w, int h, int color);
  void fillRectAllDisplays(int x, int y, int w, int h, int color);
  void setCursor(int x, int y);
  void print(const char* x);
  void print(int x);
  void setTextColor(int color);
  void setTextSize(int size);
  int checkCollision(int* x, int* y, int *changeX, int *changeY);
  int getNextScreen();
  // void bmpDraw(int display, Image image, int x, int y);

private:
  displayLocation displaylocation;
  displayLocation screenIndex[12][2] = { {{0,A},{3,A}}, {{0,B},{2,A}}, {{0,C},{1,A}}, {{0,D},{4,A}}, {{1,B},{2,D}}, {{1,C},{5,A}}, {{1,D},{4,B}}, {{2,B},{3,D}}, {{2,C},{5,B}}, {{3,B},{4,D}}, {{3,C},{5,C}}, {{4,C},{5,D}} };
  Adafruit_ILI9341 *displayArr[AMOUNT_DISPLAYS] = {0}; //240 x 320

};

#endif
