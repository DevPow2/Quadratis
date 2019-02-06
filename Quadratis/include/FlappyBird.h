#ifndef FlappyBird_H
#define FlappyBird_H

#include <Arduino.h>
#include "Game.h"
// #include "Image_flappyBird.h"

class FlappyBird : public Game
{
  public:
    FlappyBird(Display_Master *display);
    ~FlappyBird();
    Info getInfo() override;
    void run() override;

};

#endif
