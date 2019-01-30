#include "Game.h"

Game::Game()
{
    // Snake snake(display);
    // FlappyBird flappyBird(display);
    // listOfGames[0] = (Game *) &snake;
    // listOfGames[1] = (Game *) &flappyBird;
}

Game::~Game()
{
    currentGame = NULL;
    for(int i = 0; i < AMOUNT_GAMES; i++) listOfGames[i] = NULL;
}

void Game::addGame(int x, Game* game)
{
    listOfGames[x] = game;
}

Game* Game::getCurrentGame()
{
    return currentGame;
}

void Game::setCurrentGame(int game)
{
    currentGame = listOfGames[game];
}

