#include "Speaker.h"

Speaker::Speaker()
{
  Serial.println("TESTTT");
  // mySoftwareSerial->begin(9800);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  //!myDFPlayer->begin(*mySoftwareSerial, true, false)
  if (true)
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

Speaker::~Speaker()
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