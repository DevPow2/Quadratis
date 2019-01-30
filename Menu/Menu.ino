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

//Font
#include <Fonts/Org_01.h>

// For the ESP8266, these are the default.
#define TFT_DC 2
#define TFT_CS 15

bool updated = false;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!");

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  //  tft.setFont(&Org_01);
  updated = true;

}


void loop(void) {
  if (updated) {
    updated = false;
    costumize();
  }
  for (uint8_t rotation = 0; rotation < 4; rotation++) {
    //    tft.setRotation(rotation);
    //    testText();

    delay(1000);
  }
}



void menu() {
  setTextTFT(3, "Opties", 1);
  setTextTFT(3, "Media", 2);
  setTextTFT(3, "Games", 3);
  setTextTFT(3, "Developer", 4);
}

void costumize() {
  setTitleTFT(2.5, "Customize", 1);
  setTextTFT(2.5, "Achtergrond", 2);
  setTextTFT(2.5, "Knoppen", 3);
  setTextTFT(2.5, "Font", 4);
}

void options() {
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

//int16_t textWidth(const String& string) {
//  int16_t len = string.length() + 2;
//  char buffer[len];
//  string.toCharArray(buffer, len);
//  return textWidth(buffer);
//}
