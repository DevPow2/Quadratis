#include "Display_Master.h"
// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000
Display_Master::Display_Master() // initialize all displays
{

    /*initialize displays */
    displaylocation.displayNumber = 0;
    Serial.println("Setting up displays");

    displayArr[0] = new Adafruit_ILI9341(27, 5);
    displayArr[1] = new Adafruit_ILI9341(22, 5);
    displayArr[2] = new Adafruit_ILI9341(2, 5);
    displayArr[3] = new Adafruit_ILI9341(32, 5);
    displayArr[4] = new Adafruit_ILI9341(4, 5);
    int j = 0;
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
    {
        displayArr[i]->begin(10000000);
        displayArr[i]->setRotation(i);
        delay(10);
    }

    displayArr[0]->fillScreen(ILI9341_CYAN);
    delay(200);
    displayArr[1]->fillScreen(ILI9341_CYAN);
    delay(200);
    displayArr[2]->fillScreen(ILI9341_CYAN);
    delay(200);
    displayArr[3]->fillScreen(ILI9341_CYAN);
    delay(200);
    displayArr[4]->fillScreen(ILI9341_CYAN);
    delay(200);

    Serial.println("OK!");
}

void Display_Master::clearPixel(int display, int x, int y, int color)
{
    displayArr[display]->drawPixel(x, y, color);
}

void Display_Master::drawRect(int display, int x, int y, int w, int h, int color)
{
    for (int i = y; i < y + h; i++)
    {
        for (int j = x; j < x + w; j++)
        {
            displayArr[display]->drawPixel(j, i, color);
        }
    }
}
void Display_Master::drawRectAllDisplays(int x, int y, int w, int h, int color)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->fillRect(x, y, h, w, color);
}

void Display_Master::fillRect(int display, int x, int y, int w, int h, int color)
{
    for (int i = y; i < y + h; i++)
    {
        for (int j = x; j < x + w; j++)
        {
            displayArr[display]->drawPixel(j, i, color);
        }
    }
}

void Display_Master::fillRectAllDisplays(int x, int y, int w, int h, int color)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->fillRect(x, y, w, h, color);
}

void Display_Master::setCursor(int x, int y)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->setCursor(x, y);
}
void Display_Master::print(const char *x)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->print(x);
}
void Display_Master::print(int x)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->print(x);
}
void Display_Master::setTextColor(int color)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->setTextColor(color);
}
void Display_Master::setTextSize(int size)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->setTextSize(size);
}

Display_Master::~Display_Master() {}

int Display_Master::getCurrentDisplay()
{
    return displaylocation.displayNumber;
}

int Display_Master::checkCollision(int *x, int *y, int *changeX, int *changeY)
{
    if (*x < 0)
    {
        if ((*y / 2) > (SCREEN_Y_SIZE / 2))
        {
            *x = *y + ((SCREEN_X_SIZE - SCREEN_Y_SIZE) / 2);
        }
        else if ((*y / 2) < (SCREEN_Y_SIZE / 2))
        {
            *x = *y - ((SCREEN_X_SIZE - SCREEN_Y_SIZE) / 2);
        }
        *y = 220;
        *changeY = -10;
        *changeX = 0;
        displaylocation.direction = B;
        return true;
    }
    else if (*x > 320)
    {
        if ((*y / 2) > (SCREEN_Y_SIZE / 2))
        {
            *x = *y + ((SCREEN_X_SIZE - SCREEN_Y_SIZE) / 2);
        }
        else if ((*y / 2) < (SCREEN_Y_SIZE / 2))
        {
            *x = *y - ((SCREEN_X_SIZE - SCREEN_Y_SIZE) / 2);
        }
        *y = 0;
        *changeY = 10;
        *changeX = 0;
        displaylocation.direction = D;
        return true;
    }
    else if (*y < 0)
    {
        if ((*x / 2) > (SCREEN_X_SIZE / 2))
        {
            *y = *x - ((SCREEN_X_SIZE - SCREEN_Y_SIZE) / 2);
        }
        else if ((*x / 2) < (SCREEN_X_SIZE / 2))
        {
            *y = *x + ((SCREEN_X_SIZE - SCREEN_Y_SIZE) / 2);
        }
        *x = 340;
        *changeX = -10;
        *changeY = 0;
        displaylocation.direction = A;
        return true;
    }
    else if (*y > 240)
    {
        if ((*x / 2) > (SCREEN_X_SIZE / 2))
        {
            *y = *x - ((SCREEN_X_SIZE - SCREEN_Y_SIZE) / 2) - 20;
        }
        else if ((*x / 2) < (SCREEN_X_SIZE / 2))
        {
            *y = *x + ((SCREEN_X_SIZE - SCREEN_Y_SIZE) / 2) + 20;
        }
        *x = 0;
        *changeX = 10;
        *changeY = 0;
        displaylocation.direction = C;
        return true;
    }
    return false;
}

// int Display_Master::getNextScreen()
// {
//     for (int i = 0; i < 12; i++)
//     { // rows
//         for (int j = 0; j < 2; j++)
//         { // columns
//             if (screenIndex[i][j].direction == displaylocation.direction && screenIndex[i][j].displayNumber == displaylocation.displayNumber)
//             {
//                 Serial.println();
//                 Serial.println(screenIndex[i][j].displayNumber);
//                 Serial.println(screenIndex[i][j].direction);
//                 Serial.println(displaylocation.displayNumber);
//                 Serial.println(displaylocation.direction);
//                 Serial.println(screenIndex[i][abs(j - 1)].displayNumber);
//                 Serial.println("-----------------------------------");
//                 return screenIndex[i][abs(j - 1)].displayNumber; // will return an 1 when 0 or 0 when 1
//             }
//         }
//     }
//     return -1;
// }

int Display_Master::getNextScreen()
{
    displaylocation.displayNumber += 1;
    if(displaylocation.displayNumber > 4) displaylocation.displayNumber = 0;
    return displaylocation.displayNumber;
}

