#include "Display.h"

Display::Display()
{
    //pinMode(4, OUTPUT);
   // pinMode(2, OUTPUT);
   
    displays[0] = new Adafruit_ILI9341(4, 5);
    displays[1] = new Adafruit_ILI9341(32, 5);
    displays[2] = new Adafruit_ILI9341(22, 5);
    displays[3] = new Adafruit_ILI9341(27, 5);
    displays[4] = new Adafruit_ILI9341(2, 5);

    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
    {
        displays[i]->begin(12000000);
        if(i < 3)  displays[i]->setRotation(3);
        else displays[i]->setRotation(1);
    }
    //displays[1]->begin();
    // displays[1]->begin();
     //displays[0]->begin();
     
// displays[1]->begin();
    // for(int i = 0; i < AMOUNT_DISPLAYS; i++) 
    // {
    //     uint8_t x = displays[i]->readcommand8(ILI9341_RDMODE);
    //     Serial.print("Display Power Mode: 0x");
    //     Serial.println(x, HEX);
    //     x = displays[i]->readcommand8(ILI9341_RDMADCTL);
    //     Serial.print("MADCTL Mode: 0x");
    //     Serial.println(x, HEX);
    //     x = displays[i]->readcommand8(ILI9341_RDPIXFMT);
    //     Serial.print("Pixel Format: 0x");
    //     Serial.println(x, HEX);
    //     x = displays[i]->readcommand8(ILI9341_RDIMGFMT);
    //     Serial.print("Image Format: 0x");
    //     Serial.println(x, HEX);
    //     x = displays[i]->readcommand8(ILI9341_RDSELFDIAG);
    //     Serial.print("Self Diagnostic: 0x");
    //     Serial.println(x, HEX);
    // }
}

Display::~Display()
{
}

void Display::update()
{
  //  for(int i = 0; i < AMOUNT_DISPLAYS; i++) { displays[i]->fillScreen(ILI9341_BLACK); }
  for (int i = 0; i < AMOUNT_DISPLAYS; i++)
  {
      displays[i]->fillScreen(ILI9341_GREEN);
  }
  for (int i = 0; i < AMOUNT_DISPLAYS; i++)
  {
      displays[i]->fillScreen(ILI9341_BLUE);
  }
  for (int i = 0; i < AMOUNT_DISPLAYS; i++)
  {
      displays[i]->fillScreen(ILI9341_RED);
  }
  for (int i = 0; i < AMOUNT_DISPLAYS; i++)
  {
      displays[i]->fillScreen(ILI9341_YELLOW);
  }
  for (int i = 0; i < AMOUNT_DISPLAYS; i++)
  {
      displays[i]->fillScreen(ILI9341_GREENYELLOW);
  }
//    displays[3]->fillScreen(ILI9341_CYAN);
//    displays[2]->fillScreen(ILI9341_BLUE);
//    displays[1]->fillScreen(ILI9341_GREEN);
//    displays[0]->fillScreen(ILI9341_RED);
  //  displays[1]->fillScreen(ILI9341_BLUE);
  //  displays[2]->fillScreen(ILI9341_BLUE);
  //  displays[0]->fillScreen(ILI9341_RED);
  //  displays[1]->fillScreen(ILI9341_RED);
  //  displays[2]->fillScreen(ILI9341_RED);
}