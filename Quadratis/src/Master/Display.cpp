#include "Display.h"

Display::Display() // initialize all displays
{

    /*initialize displays */
    displaylocation.displayNumber = 0;
    displayArr[0] = new Adafruit_ILI9341(4, 5);
    displayArr[1] = new Adafruit_ILI9341(32, 5);
    displayArr[2] = new Adafruit_ILI9341(22, 5);
    displayArr[3] = new Adafruit_ILI9341(27, 5);
    displayArr[4] = new Adafruit_ILI9341(2, 5);
    displayArr[5] = new Adafruit_ILI9341(33, 5);

    for (int i = 0; i < AMOUNT_DISPLAYS; i++)
    {
        displayArr[i]->begin(15000000);
    }

    /*initialize touchscreens */
   // touchArr[0] = new XPT2046_Touchscreen(25);
    // pinMode(14, OUTPUT);
    touchArr[0] = new XPT2046_Touchscreen(35);
    for (int i = 0; i < AMOUNT_TOUCH; i++)
    {
        touchArr[i]->begin();
    }

    if (!SD.begin(14))
    {
        Serial.println("failed!");
    }
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

void Display::bmpDraw(int display, String filename, int x, int y)
{
    File bmpFile;
    int bmpWidth, bmpHeight;            // W+H in pixels
    uint8_t bmpDepth;                   // Bit depth (currently must be 24)
    uint32_t bmpImageoffset;            // Start of image data in file
    uint32_t rowSize;                   // Not always = bmpWidth; may have padding
    uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel buffer (R+G+B per pixel)
    uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
    boolean goodBmp = false;            // Set to true on valid header parse
    boolean flip = true;                // BMP is stored bottom-to-top
    int w, h, row, col;
    uint8_t r, g, b;
    uint32_t pos = 0, startTime = millis();

    if ((x >= displayArr[display]->width()) || (y >= displayArr[display]->height()))
        return;

    Serial.println();
    Serial.print(F("Loading image '"));
    Serial.print(filename);
    Serial.println('\'');

    // Open requested file on SD card
    if ((bmpFile = SD.open(filename)) == NULL)
    {
        Serial.print(F("File not found"));
        return;
    }

    // Parse BMP header
    if (read16(bmpFile) == 0x4D42)
    { // BMP signature
        Serial.print(F("File size: "));
        Serial.println(read32(bmpFile));
        (void)read32(bmpFile);            // Read & ignore creator bytes
        bmpImageoffset = read32(bmpFile); // Start of image data
        Serial.print(F("Image Offset: "));
        Serial.println(bmpImageoffset, DEC);
        // Read DIB header
        Serial.print(F("Header size: "));
        Serial.println(read32(bmpFile));
        bmpWidth = read32(bmpFile);
        bmpHeight = read32(bmpFile);
        if (read16(bmpFile) == 1)
        {                               // # planes -- must be '1'
            bmpDepth = read16(bmpFile); // bits per pixel
            Serial.print(F("Bit Depth: "));
            Serial.println(bmpDepth);
            if ((bmpDepth == 24) && (read32(bmpFile) == 0))
            { // 0 = uncompressed

                goodBmp = true; // Supported BMP format -- proceed!
                Serial.print(F("Image size: "));
                Serial.print(bmpWidth);
                Serial.print('x');
                Serial.println(bmpHeight);

                // BMP rows are padded (if needed) to 4-byte boundary
                rowSize = (bmpWidth * 3 + 3) & ~3;

                // If bmpHeight is negative, image is in top-down order.
                // This is not canon but has been observed in the wild.
                if (bmpHeight < 0)
                {
                    bmpHeight = -bmpHeight;
                    flip = false;
                }

                // Crop area to be loaded
                w = bmpWidth;
                h = bmpHeight;
                if ((x + w - 1) >= displayArr[display]->width())
                    w = displayArr[display]->width() - x;
                if ((y + h - 1) >= displayArr[display]->height())
                    h = displayArr[display]->height() - y;

                // Set TFT address window to clipped image bounds
                displayArr[display]->startWrite();
                displayArr[display]->setAddrWindow(x, y, w, h);

                for (row = 0; row < h; row++)
                { // For each scanline...

                    // Seek to start of scan line.  It might seem labor-
                    // intensive to be doing this on every line, but this
                    // method covers a lot of gritty details like cropping
                    // and scanline padding.  Also, the seek only takes
                    // place if the file position actually needs to change
                    // (avoids a lot of cluster math in SD library).
                    if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
                        pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
                    else // Bitmap is stored top-to-bottom
                        pos = bmpImageoffset + row * rowSize;
                    if (bmpFile.position() != pos)
                    { // Need seek?
                        displayArr[display]->endWrite();
                        bmpFile.seek(pos);
                        buffidx = sizeof(sdbuffer); // Force buffer reload
                    }

                    for (col = 0; col < w; col++)
                    { // For each pixel...
                        // Time to read more pixel data?
                        if (buffidx >= sizeof(sdbuffer))
                        { // Indeed
                            displayArr[display]->endWrite();
                            bmpFile.read(sdbuffer, sizeof(sdbuffer));
                            displayArr[display]->startWrite();
                            buffidx = 0; // Set index to beginning
                        }

                        // Convert pixel from BMP to TFT format, push to display
                        b = sdbuffer[buffidx++];
                        g = sdbuffer[buffidx++];
                        r = sdbuffer[buffidx++];
                        displayArr[display]->pushColor(displayArr[display]->color565(r, g, b));
                    } // end pixel
                    displayArr[display]->endWrite();
                } // end scanline
                Serial.print(F("Loaded in "));
                Serial.print(millis() - startTime);
                Serial.println(" ms");
            } // end goodBmp
        }
    }

    bmpFile.close();
    if (!goodBmp)
        Serial.println(F("BMP format not recognized."));
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
