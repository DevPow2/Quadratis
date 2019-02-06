#include "Speaker.h"

Speaker::Speaker()
{
  Serial1.begin(9600, SERIAL_8N1, TX_MP3, RX_MP3);
  Serial.println(F("Initializing speaker ..."));

  if (!myDFPlayer->begin(Serial1, true, false))
  {
    Serial.println("The speaker is unable to begin. Recheck the connection and insert the SD card.");
    //ESP.restart();
  }
  Serial.println(F("DFPlayer Mini online."));
  // delay(200);
  vTaskDelay(200);
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
    myDFPlayer->play(0);
    break;
  }
}