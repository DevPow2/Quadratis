#ifndef Game_H
#define Game_H

#include <App.h>
#include "Display_Master.h"
#include "Communication.h"
// #include "Snake.h"
// #include "FlappyBird.h"
#include <Arduino.h>
// #include "Adafruit_GFX.h"
// #include "Adafruit_ILI9341.h"

#define AMOUNT_GAMES 1



class Game
{

public:
  Game();
  virtual ~Game() = 0;
  virtual Info getInfo() = 0;
  virtual void run() = 0;
  void addGame(int x, Game *game);
  Game *getCurrentGame();
  void setCurrentGame(int game);

private:
  Game *currentGame = NULL;
  Game *listOfGames[AMOUNT_GAMES] = {0};
};

#endif
