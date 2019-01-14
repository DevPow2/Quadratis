#include "Snake.h"

Snake::Snake(Display *displayTemp) //constructor
{
    displays = displayTemp;
    init();
    //temp[0] = displays->displayArr[0];

    //displayArr[0].fillRect(100, 100, 100, 20, ILI9341_BLACK);
}
void Snake::init()
{
    // displays->drawRect(100, 100, width, height);
}

void Snake::generateSnack()
{

int bla = 240/30;
int bla2 = 320/30;
    snack.x = random(0, bla) * 30;
    snack.y = random(0, bla2) * 30;

    // snack.x = 200;
    // snack.y = 100;
    displays->drawRect(snack.x, snack.y, width, height, ILI9341_BLUE);
}

bool Snake::collision()
{
    if (location.x == snack.x && location.y == snack.y)
    {
        clearObject(snack.x, snack.y);
        generateSnack();
        return true;
    }

    return false;
}

void Snake::clearObject(int x, int y)
{
    for (int j = y; j < y + height; j++)
    {

        for (int i = x; i < x + width; i++)
        {
            displays->clearPixel(i, j, ILI9341_WHITE);
        }
    }
}

void Snake::move(int stepSize)
{
    for (int j = location.y; j < location.y + height; j++)
    {

        for (int i = location.x; i < location.x + width; i++)
        {
            displays->clearPixel(i, j, ILI9341_WHITE);
        }
    }
    if (location.x > 235)
    {
        location.x = 0;
    }

    location.x = location.x + stepSize;
    displays->drawRect(location.x, location.y, width, height, ILI9341_BLACK);
}
// void Snake::Update()
// {

//     y = y + 5;
//     //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
// }

// void Snake::move(int stepSize)
// {
//     displays->drawRect();
// }

// void Snake::moveUp()
// {

//     y = y + 5;
//     //displays[0]->fillRect(100, 100, 100, 20, ILI9341_BLACK);
// }
// void Snake::moveDown()
// {
//     y = y - 5;
// }
// void Snake::moveLeft()
// {
//     x = x - 5;
// }
// void Snake::moveRight()
// {
//     x = x + 5;
// }
Snake::~Snake() {}