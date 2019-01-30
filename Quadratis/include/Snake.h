#ifndef Snake_H
#define Snake_H

#include <Arduino.h>
#include "Game.h"

//https://github.com/mouboo/snake/blob/master/snake.ino
class Snake : public Game
{
  struct food
  {
    int x;
    int y;
    int display;
  };

  struct snake
  {
    int headX = 100;
    int headY = 100;
    int beenHeadX[470];
    int beenHeadY[470];
    int beenHeadOnDisplay[470];
    int changeX = 0;
    int changeY = 10;
    const int width = 10;
    const int height = 10;
  };

public:
  Snake(Display *display);
  ~Snake();
  Info getInfo() override;
  void run() override;

private:
  Display *displays;
  int currentDisplay = 0;
  int borderX = 10;
  int borderY = 40;
  const int stepSize = 10;
  int score = 1;
  int counter = 0;
  int clearPoint = 0;
  food food;
  snake snake;
  Adafruit_ILI9341 *temp[1];

  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  void printScore();
  void init();
  void clearObject(int display, int x, int y);
  bool eaten();
  void grow();
  void generateFood();
};

#endif
