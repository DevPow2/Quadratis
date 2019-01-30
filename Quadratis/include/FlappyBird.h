#ifndef FlappyBird_H
#define FlappyBird_H

#include <Arduino.h>
#include "Game.h"

class FlappyBird : public Game
{
  public:
    FlappyBird(Display *display);
    ~FlappyBird();
    Info getInfo() override;
    void run() override;

};

#endif
