#ifndef Speaker_H
#define Speaker_H

#include <Arduino.h>
//#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

class Speaker
{ 
    // Access specifier 
    public: 

    // Data Members 
    // string geekname; 
  
    // Member Functions() 
    Speaker();
    ~Speaker();
    void setMusic();

  private:
   // SoftwareSerial* mySoftwareSerial = new SoftwareSerial(D3,D4); // RX, TX
    DFRobotDFPlayerMini* myDFPlayer = new DFRobotDFPlayerMini();

    void printDetail(uint8_t type, int value);
}; 

#endif
