#ifndef Input_H
#define Input_H

#include <Arduino.h>

class Input 
{ 
    // Access specifier 
    public: 

    // Data Members 
    // string geekname;

      // Member Functions()
      virtual void getSensorData() = 0;
}; 

#endif
