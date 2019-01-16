#include "Snake.h"

Snake::Snake(Display *displayTemp) //constructor
{
    memset(snake.beenHeadX, 0, 470); //initiate beenHead with a bunch of zeros
    memset(snake.beenHeadY, 0, 470);
    memset(snake.beenHeadOnDisplay, 0, 470);
    displays = displayTemp;

    displays->drawRect(snake.beenHeadOnDisplay[counter], snake.headX, snake.headY, snake.width, snake.height, ILI9341_WHITE);
    displays->drawRectAllDisplays(0, 0, borderX, borderY, ILI9341_YELLOW);
    displays->drawRectAllDisplays(SCREEN_X_SIZE - borderY, 0, borderX, borderY, ILI9341_YELLOW);

    displays->drawRectAllDisplays(0, SCREEN_Y_SIZE - borderX, borderX, borderY, ILI9341_YELLOW);
    displays->drawRectAllDisplays(320 - borderY, 240 - borderX, borderX, borderY, ILI9341_YELLOW);

    
    // displays->drawRect(0, (240 - borderX), borderX, 320, ILI9341_YELLOW);

    generateFood();

    displays->setTextColor(ILI9341_WHITE); //Score keeper
    displays->setTextSize(2);
    displays->setCursor(45, 3);
    displays->print("Length: ");
    printScore();

    //temp[0] = displays->displayArr[0];
    //displayArr[0].fillRect(100, 100, 100, 20, ILI9341_BLACK);
}

void Snake::generateFood()
{
    // int bla = 240 / 30;
    // int bla2 = 320 / 30;
    food.x = 100;
    food.y = 200;
    food.display = displays->getCurrentDisplay();
    displays->drawRect(food.display, food.x, food.y, snake.width, snake.height, ILI9341_BLUE); //draws a blue rectangle
}

bool Snake::eaten()
{
    // Serial.println(snake.headX);
    // Serial.println("bla");
    // Serial.println(food.x);
    if (snake.headX == food.x && snake.headY == food.y) //change to range?
    {
        printScore();
        Serial.print("true");
        clearObject(food.display, food.x, food.y);
        score++;
        return true;
    }
    //Serial.print("false");

    return false;
}

void Snake::clearObject(int display, int x, int y)
{
    for (int i = y; i < y + snake.height; i++)
    {
        for (int j = x; j < x + snake.width; j++)
        {
            displays->clearPixel(display, j, i, ILI9341_BLACK);
        }
    }
}

void Snake::move()
{

    snake.beenHeadX[counter] = snake.headX; //adds current head coordinates to be
    snake.beenHeadY[counter] = snake.headY; //covered later

    snake.headX = snake.headX + snake.changeX; //head moved
    snake.headY = snake.headY + snake.changeY;

    if (displays->checkCollision(&snake.headX, &snake.headY, &snake.changeX, &snake.changeY))
    {
      currentDisplay = displays->getNextScreen();
    }
    snake.beenHeadOnDisplay[counter] = currentDisplay;
    // snake.beenHeadOnDisplay[counter] = displays->getCurrentDisplay();
    Serial.print("X : ");
    Serial.println(snake.headX);
    Serial.print("Y : ");
    Serial.println(snake.headY);
    Serial.print("Display : ");
    Serial.println(snake.beenHeadOnDisplay[counter]);
    Serial.println("-----------------------------------");

    if (eaten() == true)
    {
        Serial.print("You just ate a snack!");
        //play sound
        generateFood();
        grow();
    }

    displays->drawRect(snake.beenHeadOnDisplay[counter], snake.headX, snake.headY, snake.width, snake.height, ILI9341_WHITE);
    counter++;
    if (counter > 467)
    {
        clearPoint = counter - score;
        counter = 0;
    }
    if (counter - score >= 0)
    {
        clearObject(snake.beenHeadOnDisplay[counter - score], snake.beenHeadX[counter - score], snake.beenHeadY[counter - score]);
    }
    else
    {
        clearObject(snake.beenHeadOnDisplay[clearPoint], snake.beenHeadX[clearPoint], snake.beenHeadY[clearPoint]);
        clearPoint += 1;
    }
}

void Snake::grow()
{
    //snake.beenHeadX;
}

// void Snake::moveUp()
// {

//     snake.changeX = 0; //changes the direction of the snake
//     snake.changeY = 10;
//     //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
//     move();
// }

// void Snake::moveDown()
// {
//     snake.changeX = 0; //changes the direction of the snake
//     snake.changeY = -10;
//     //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
//     move();
// }

// void Snake::moveRight()
// {
//     snake.changeX = 10; //changes the direction of the snake
//     snake.changeY = 0;
//     move();
//     //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
// }

// void Snake::moveLeft()
// {
//     snake.changeX = -10; //changes the direction of the snake
//     snake.changeY = 0;
//     move();
//     //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
// }
void Snake::printScore()
{

    displays->fillRectAllDisplays(130, 3, 50, 16, ILI9341_BLACK); //clears old score
    displays->setCursor(130, 3);
    displays->print(score); //prints current score}
}

Snake::~Snake()
{
}