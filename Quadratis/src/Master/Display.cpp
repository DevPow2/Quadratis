#include "Display.h"

Display::Display() // initialize all displays
{

    /*initialize displays */
    displaylocation.displayNumber = 0;
    displayArr[0] = new Adafruit_ILI9341(25, 5);
    // displayArr[1] = new Adafruit_ILI9341(32, 5);
    // displayArr[2] = new Adafruit_ILI9341(22, 5);
    // displayArr[3] = new Adafruit_ILI9341(27, 5);
    // displayArr[4] = new Adafruit_ILI9341(4, 5);
    // displayArr[5] = new Adafruit_ILI9341(2, 5);

    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
    {
        displayArr[i]->begin(12000000);
    }

    displayArr[0]->fillScreen(ILI9341_GREEN);

    // displayArr[1]->fillScreen(ILI9341_BLUE);

    // displayArr[2]->fillScreen(ILI9341_GREEN);

    // displayArr[3]->fillScreen(ILI9341_YELLOW);

    // displayArr[4]->fillScreen(ILI9341_RED);

    // displayArr[5]->fillScreen(ILI9341_BLUE);

    /*initialize touchscreens */
    touchArr[0] = new XPT2046_Touchscreen(26);
    for (int i = 0; i < AMOUNT_TOUCH; i++)
    {
        touchArr[i]->begin();
    }

    // if (!SD.begin(14))
    // {
    //     Serial.println("failed!");
    // }
    Serial.println("OK!");
}

int Display::touched()
{
    for (int i = 0; i < AMOUNT_TOUCH; i++)
    {
        if (!touchArr[i]->bufferEmpty())
        {
            return i;
        }
    }
    return -1; //nothing is touched
}

Coordinates Display::getTouch(int display)
{
    Coordinates coordinates;
    if (touchArr[display]->touched())
    {
        TS_Point p = touchArr[display]->getPoint();
        coordinates.x = map(p.x, TS_MINX, TS_MAXX, 0, displayArr[display]->width());
        coordinates.y = map(p.y, TS_MINY, TS_MAXY, 0, displayArr[display]->height());
        return coordinates;
    }
    coordinates.x = -1;
    coordinates.y = -1;
    return coordinates;
}

void Display::clearPixel(int display, int x, int y, int color)
{
    displayArr[display]->drawPixel(x, y, color);
}

void Display::drawRect(int display, int x, int y, int w, int h, int color)
{
    for (int i = y; i < y + h; i++)
    {
        for (int j = x; j < x + w; j++)
        {
            displayArr[display]->drawPixel(j, i, color);
        }
    }
}
void Display::drawRectAllDisplays(int x, int y, int w, int h, int color)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->fillRect(x, y, h, w, color);
}

void Display::fillRect(int display, int x, int y, int w, int h, int color)
{
    for (int i = y; i < y + h; i++)
    {
        for (int j = x; j < x + w; j++)
        {
            displayArr[display]->drawPixel(j, i, color);
        }
    }
}

void Display::fillRectAllDisplays(int x, int y, int w, int h, int color)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->fillRect(x, y, w, h, color);
}

void Display::setCursor(int x, int y)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->setCursor(x, y);
}
void Display::print(const char *x)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->print(x);
}
void Display::print(int x)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->print(x);
}
void Display::setTextColor(int color)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->setTextColor(color);
}
void Display::setTextSize(int size)
{
    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
        displayArr[i]->setTextSize(size);
}

Display::~Display() {}

int Display::getCurrentDisplay()
{
    return displaylocation.displayNumber;
}

int Display::checkCollision(int *x, int *y, int *changeX, int *changeY)
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

int Display::getNextScreen()
{
    for (int i = 0; i < 12; i++)
    { // rows
        for (int j = 0; j < 2; j++)
        { // columns
            if (screenIndex[i][j].direction == displaylocation.direction && screenIndex[i][j].displayNumber == displaylocation.displayNumber)
            {
                Serial.println();
                Serial.println(screenIndex[i][j].displayNumber);
                Serial.println(screenIndex[i][j].direction);
                Serial.println(displaylocation.displayNumber);
                Serial.println(displaylocation.direction);
                Serial.println(screenIndex[i][abs(j - 1)].displayNumber);
                Serial.println("-----------------------------------");
                return screenIndex[i][abs(j - 1)].displayNumber; // will return an 1 when 0 or 0 when 1
            }
        }
    }
    return -1;
}

void Display::bmpDraw(int display, Image image, int x, int y)
{
    displayArr[0]->drawRGBBitmap(0, 0, (uint16_t *)image.pixel_data, image.width, image.height);
}

uint16_t Display::read16(File &f)
{
    uint16_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
}

uint32_t Display::read32(File &f)
{
    uint32_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
}
