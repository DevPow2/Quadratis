#ifndef Snake_H
#define Snake_H

#include <Arduino.h>
#include "Game.h"

struct {
  int x;
  int y;
} snake;

//https://github.com/mouboo/snake/blob/master/snake.ino
class Snake : Game
{
    // Access specifier
  public:
    // Data Members
    // string geekname;
    
    // Member Functions()
    Snake();
    ~Snake();
    void showStartScreen();
    void showEndScreen();
    void reset();
    int  collision();
    void grow();
    void generateSnack();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
};

#endif
