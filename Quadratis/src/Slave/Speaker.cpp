#include "Speaker.h"

Speaker::Speaker()
{
  Serial1.begin(9600, SERIAL_8N1, TX_MP3, RX_MP3);
  Serial.println(F("Initializing speaker ..."));

  if (!myDFPlayer->begin(Serial1, true, false))
  {
    Serial.println("The speaker is unable to begin. Recheck the connection and insert the SD card.");
    while (true)
    {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  delay(5000);
}

Speaker::~Speaker()
{
  myDFPlayer = NULL;
}

void Speaker::setVolume(int volume)
{
  myDFPlayer->volume(volume);
}

void Speaker::playSong(int fileNumber)
{
  Serial.print("playing number: ");
  Serial.println(fileNumber);
  switch (fileNumber)
  {
  case 1:
    myDFPlayer->play(1);
    break;

  case 2:
    myDFPlayer->play(2);
    break;

  default: //todo
    myDFPlayer->play(1);
    break;
  }
}