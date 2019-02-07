#include "Display_Slave.h"
int section;

Display_Slave::Display_Slave()
{
    Serial.println("Setting up display");

    display = new Adafruit_ILI9341(25, 5);
    display->begin();
    delay(10);
    display->setRotation(1);
    drawLogo();

    touchscreen = new XPT2046_Touchscreen(26); //todo
    touchscreen->begin();

    Serial.println("OK!");
}

void Display_Slave::drawLogo()
{
    display->fillScreen(ILI9341_BLACK);
    display->setCursor(20, 100);

    display->setTextSize(5);
    display->println("Quadratis");
}


void Display_Slave::menu()
{
    section = 0;
    //   tft.fillScreen(ILI9341_BLACK);
    setTextTFT(2, "Opties", 1);
    setTextTFT(2, "Media", 2);
    setTextTFT(2, "Games", 3);
    setTextTFT(2, "Developer", 4);
}

void Display_Slave::setTextTFT(int fontSize, String text, int yOffset)
{

    int x, y, space,
        cx = SCREEN_X_SIZE / 2 - 1,
        cy = SCREEN_Y_SIZE / 2 - 1;

    space = 20;
    x = cx - ((fontSize * 6) * text.length() / 2);
    y = (fontSize * 8 + space) * yOffset + 22;

    setTitleTFT(fontSize, text, yOffset);
    display->drawRoundRect(x - 10, y - 5, (6 * text.length() * fontSize) + 20, (8 * fontSize) + 9, 5, 0xFFFF);

    //  Serial.println(textWidth("Opties"));
}

void Display_Slave::setTitleTFT(int fontSize, String text, int yOffset)
{

    int x, y, space, textW, textH,
        cx = display->width() / 2 - 1,
        cy = display->height() / 2 - 1;

    space = 20;
    x = cx - ((fontSize * 6) * text.length() / 2);
    y = (fontSize * 8 + space) * yOffset + 22;

    display->setCursor(x, y);
    display->setTextColor(ILI9341_WHITE);
    display->setTextSize(fontSize);
    display->println(text);

    //  Serial.println(textWidth("Opties"));
}

void Display_Slave::getTouch()
{
    if (touchscreen->touched())
    {

        // Retrieve a point
        TS_Point p = touchscreen->getPoint();
       
        // Scale from ~0->4000 to tft.width using the calibration #'s
        p.x = map(p.x, TS_MINX, TS_MAXX, 0, SCREEN_X_SIZE);
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, SCREEN_Y_SIZE);

        if (p.x >= 135 && p.x <= 221 && p.y >= 56 && p.y <= 70 && section == 0)
        {
            options();
        }

        if (p.x >= 116 && p.x <= 238 && p.y >= 128 && p.y <= 142 && section == 1)
        {
            customize();
        }

        if (p.x >= 0 && p.x <= 50 && p.y >= 0 && p.y <= 50 && (section == 1 || section == 2))
        {
            menu();
        }

        Serial.print("X: ");
        Serial.print(p.x);
        Serial.print(" ");
        Serial.print("Y: ");
        Serial.println(p.y);
    }
}

void Display_Slave::customize()
{
    section = 2;
    display->fillScreen(ILI9341_BLACK);
    display->setCursor(10, 10);
    display->setTextColor(ILI9341_WHITE);
    display->setTextSize(1);
    display->println("Back");
    setTitleTFT(2.5, "Customize", 1);
    setTextTFT(2.5, "Achtergrond", 2);
    setTextTFT(2.5, "Knoppen", 3);
    setTextTFT(2.5, "Font", 4);
}
void Display_Slave::options()
{
    section = 1;
    display->fillScreen(ILI9341_BLACK);
    display->setCursor(10, 10);
    display->setTextColor(ILI9341_WHITE);
    display->setTextSize(1);
    display->println("Back");
    setTitleTFT(2, "Opties", 1);
    setTextTFT(2, "Netwerk", 2);
    setTextTFT(2, "Customize", 3);
    setTextTFT(2, "Geluid", 4);
}
Display_Slave::~Display_Slave() {}