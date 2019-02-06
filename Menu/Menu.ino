/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// For the ESP8266, these are the default.
#define TFT_DC 2
#define TFT_CS 15

bool updated = false;
uint16_t touchX, touchY;
int section;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046_Touchscreen touch(/*cs=*/ 4, /*irq=*/ 5);



void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!");

  tft.begin();
  touch.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);

  //  tft.setFont(&Org_01);
  updated = true;
  menu();

}


void loop(void) {
  getTouch();
}



void menu() {
  section = 0;
  tft.fillScreen(ILI9341_BLACK);
  setTextTFT(2, "Opties", 1);
  setTextTFT(2, "Media", 2);
  setTextTFT(2, "Games", 3);
  setTextTFT(2, "Developer", 4);
}

void costumize() {
  section = 2;
  tft.fillScreen(ILI9341_BLACK);
  setTitleTFT(2.5, "Customize", 1);
  setTextTFT(2.5, "Achtergrond", 2);
  setTextTFT(2.5, "Knoppen", 3);
  setTextTFT(2.5, "Font", 4);
}

void options() {
  section = 1;
  tft.fillScreen(ILI9341_BLACK);
  setTitleTFT(2, "Opties", 1);
  setTextTFT(2, "Netwerk", 2);
  setTextTFT(2, "Customize", 3);
  setTextTFT(2, "Geluid", 4);
}

void setTextTFT(int fontSize, String text, int yOffset) {
  int x, y, space,
      cx = tft.width()  / 2 - 1,
      cy = tft.height() / 2 - 1;

  space = 20;
  x = cx - ((fontSize * 6) * text.length() / 2);
  y = (fontSize * 8 + space) * yOffset + 22;

  setTitleTFT(fontSize, text, yOffset);
  tft.drawRoundRect(x - 10, y - 5, (6 * text.length() * fontSize) + 20, (8 * fontSize) + 9, 5, 0xFFFF  );

  //  Serial.println(textWidth("Opties"));
}

void setTitleTFT(int fontSize, String text, int yOffset) {

  int x, y, space, textW, textH,
      cx = tft.width()  / 2 - 1,
      cy = tft.height() / 2 - 1;

  space = 20;
  x = cx - ((fontSize * 6) * text.length() / 2);
  y = (fontSize * 8 + space) * yOffset + 22;

  tft.setCursor(x, y);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(fontSize);
  tft.println(text);


  //  Serial.println(textWidth("Opties"));

}

void getTouch() {
  if (touch.touched()) {

    // Retrieve a point
    TS_Point p = touch.getPoint();
    // Scale from ~0->4000 to tft.width using the calibration #'s
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    if (p.x >= 135 && p.x <= 221 && p.y >= 56 && p.y <= 70 && section == 0) {
      options();
    }

    if (p.x >= 116 && p.x <= 238 && p.y >= 128 && p.y <= 142 && section == 1) {
      costumize();
    }

    Serial.print("X: ");
    Serial.print(p.x);
    Serial.print(" ");
    Serial.print("Y: ");
    Serial.println(p.y);
  }

}
