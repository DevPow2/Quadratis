#include "Speaker.h"

Speaker::Speaker()
{
  Serial.println("TESTTT");
  Serial1.begin(9600, SERIAL_8N1, TX_MP3, RX_MP3);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  
  if (!myDFPlayer->begin(Serial1, true, false))
  { //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
    {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  delay(5000);
}

Speaker::~Speaker() //deconstructor
{
  // mySoftwareSerial = NULL;
  myDFPlayer = NULL;
}

void Speaker::setMusic()
{
  Serial.println("sound");
  myDFPlayer->volume(30); //Set volume value. From 0 to 30
  myDFPlayer->next();     //Play the first mp3
}

void Speaker::playSong(int fileNumber)
{
  Serial.print("playing number :: ");
  Serial.println(fileNumber);
  switch (fileNumber)
  {
  case 1:
    myDFPlayer->play(1);
    break;

  case 2:
    myDFPlayer->play(1);
    break;

  default: //todo
    myDFPlayer->play(1);
    break;
  }
}