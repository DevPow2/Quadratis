#ifndef Snake_H
#define Snake_H

#include <Arduino.h>
#include "Game.h"

//https://github.com/mouboo/snake/blob/master/snake.ino
class Snake : Game
{
  struct food
  {
    int x;
    int y;
  };

  struct snake
  {
    int headX = 30;
    int headY = 30;
    int beenHeadX[470];
    int beenHeadY[470];
    int changeX = 0;
    int changeY = 0;
    const int width = 10;
    const int height = 10;
  };

public:
  int borderX = 10;
  int borderY = 30;
  const int stepSize = 10;
  int score = 1;
  int counter = 0;
  int clearPoint = 0;
  food food;
  snake snake;
  //int snake [];
  Snake(Display *displayTemp);
  ~Snake();
  void init();
  // void showStartScreen();
  // void showEndScreen();
  void clearObject(int x, int y);
  // void reset();
  bool eaten();
  void grow();
  void generateFood();
  void move();
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  void printScore();

private:
  Display *displays;
  Adafruit_ILI9341 *temp[1];
};

#endif
