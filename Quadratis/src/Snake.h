#ifndef Snake_H
#define Snake_H

#include <Arduino.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Game.h"

class Snake : Game
{
    // Access specifier
  public:
    // Data Members
    // string geekname;

    // Member Functions()
    Snake();
    ~Snake();

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
};

#endif
