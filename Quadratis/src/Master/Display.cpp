#include "Display.h"

Display::Display()
{
    displays[0] = new Adafruit_ILI9341(4, 5);
    displays[1] = new Adafruit_ILI9341(32, 5);
    displays[2] = new Adafruit_ILI9341(22, 5);
    displays[3] = new Adafruit_ILI9341(27, 5);
    displays[4] = new Adafruit_ILI9341(2, 5);

    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
    {
        displays[i]->begin(15000000);
        if(i < 3)  displays[i]->setRotation(3);
        else displays[i]->setRotation(1);
    }
}

Display::~Display()
{
}

void Display::update()
{
    if (i > 240)
    {
        
        displays[3]->fillScreen(ILI9341_BLACK);
        i = 0;
    }
    i+= 10;
    displays[3]->fillTriangle(0,0,i,i,i,0, ILI9341_BLUE);
    displays[4]->drawFastVLine(10,10,100, ILI9341_BLUE);
    displays[2]->fillTriangle(0,0,40,40,80,0, ILI9341_BLUE);
    displays[1]->drawFastVLine(10,10,100, ILI9341_BLUE);
    displays[0]->fillTriangle(0,0,40,40,80,0, ILI9341_BLUE);
    displays[3]->drawFastVLine(10,10,100, ILI9341_BLUE);
    
//   for (int i = 0; i < AMOUNT_DISPLAYS; i++)
//   {
//       displays[i]->fillScreen(ILI9341_GREEN);
//   }
//   for (int i = 0; i < AMOUNT_DISPLAYS; i++)
//   {
//       displays[i]->fillScreen(ILI9341_BLUE);
//   }
//   for (int i = 0; i < AMOUNT_DISPLAYS; i++)
//   {
//       displays[i]->fillScreen(ILI9341_RED);
//   }
//   for (int i = 0; i < AMOUNT_DISPLAYS; i++)
//   {
//       displays[i]->fillScreen(ILI9341_YELLOW);
//   }
//   for (int i = 0; i < AMOUNT_DISPLAYS; i++)
//   {
//       displays[i]->fillScreen(ILI9341_GREENYELLOW);
//   }
}