#include "Snake.h"

Snake::Snake() //constructor
{
}

Snake::~Snake()
{
    snake.x = 500;
    snake.y = 500;
}

void Snake::moveUp()
{
    snake.y = snake.y + 5;
}

void Snake::moveDown()
{
    snake.y = snake.y - 5;
}
void Snake::moveLeft()
{
    snake.x = snake.x - 5;
}
void Snake::moveRight()
{
    snake.x = snake.x + 5;
}