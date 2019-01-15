#include "Snake.h"

Snake::Snake(Display *displayTemp) //constructor
{
    displays = displayTemp;

    displays->drawRect(snake.headX, snake.headY, snake.width, snake.height, ILI9341_WHITE);
    displays->drawRect(0, 0, borderX, 320, ILI9341_YELLOW);
    displays->drawRect(0, (240 - borderX), borderX, 320, ILI9341_YELLOW);
    generateFood();

    //temp[0] = displays->displayArr[0];
    //displayArr[0].fillRect(100, 100, 100, 20, ILI9341_BLACK);
}

void Snake::generateFood()
{
    // int bla = 240 / 30;
    // int bla2 = 320 / 30;
    food.x = 0;
    food.y = 30;
    displays->drawRect(food.x, food.y, snake.width, snake.height, ILI9341_BLUE); //draws a blue rectangle
}

bool Snake::eaten()
{
    Serial.println(snake.headX);
    Serial.println("bla");
    Serial.println(food.x);
    if (snake.headX == food.x && snake.headY == food.y) //change to range?
    {

        Serial.print("true");
        clearObject(food.x, food.y);
        score++;
        return true;
    }
    //Serial.print("false");

    return false;
}

void Snake::clearObject(int x, int y)
{
    for (int i = y; i < y + snake.height; i++)
    {
        for (int j = x; j < x + snake.width; j++)
        {
            displays->clearPixel(j, i, ILI9341_BLACK);
        }
    }
}

void Snake::move()
{

    snake.beenHeadX[counter] = snake.headX; //adds current head coordinates to be
    snake.beenHeadY[counter] = snake.headY; //covered later

    snake.headX = snake.headX + snake.changeX; //head moved
    snake.headY = snake.headY + snake.changeY;

    if (eaten() == true)
    {
        Serial.print("You just ate a snack!");
        //play sound
        generateFood();
        grow();
    }

    counter++;
    if (counter > 467)
    {
        clearPoint = counter - score;
        counter = 0;
    }
    displays->drawRect(snake.headX, snake.headY, snake.width, snake.height, ILI9341_WHITE);

  
    if (counter - score >= 0)
    {
        clearObject(snake.beenHeadX[counter - score], snake.beenHeadY[counter - score]);
    }
    else
    {
        clearObject(snake.beenHeadX[clearPoint], snake.beenHeadY[clearPoint]);
        clearPoint += 1;
    }
}

void Snake::grow()
{
    //snake.beenHeadX;
}

void Snake::moveUp()
{

    snake.changeX = 0; //changes the direction of the snake
    snake.changeY = 10;
    //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
    move();
}

void Snake::moveDown()
{
    snake.changeX = 0; //changes the direction of the snake
    snake.changeY = -10;
    //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
    move();
}

void Snake::moveRight()
{
    snake.changeX = 10; //changes the direction of the snake
    snake.changeY = 0;
    move();
    //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
}

void Snake::moveLeft()
{
    snake.changeX = -10; //changes the direction of the snake
    snake.changeY = 0;
    move();
    //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
}
Snake::~Snake()
{
}