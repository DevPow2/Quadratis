#ifndef Game_H
#define Game_H

#include <Arduino.h>
#include <App.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Display.h"

class Game : App
{
public:
  Game();
  ~Game();
  void getApp();
};

#endif
