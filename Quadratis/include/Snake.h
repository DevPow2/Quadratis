#ifndef Snake_H
#define Snake_H

#include <Arduino.h>
#include "Game.h"

//https://github.com/mouboo/snake/blob/master/snake.ino
class Snake : Game
{
  struct snack
  {
    int x;
    int y;
  };

  struct location
  {
    int x = 90;
    int y = 90;
  };

public:
  int width = 30;
  const int height = 30;

  snack snack;
  location location;
  Snake(Display *displayTemp);
  ~Snake();
  void init();
  // void showStartScreen();
  // void showEndScreen();
  void clearObject(int x, int y);
  void reset();
  bool collision();
  void grow();
  void generateSnack();
  void move(int stepSize);
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();

private:
  Display *displays;
  Adafruit_ILI9341 *temp[1];
};

#endif
