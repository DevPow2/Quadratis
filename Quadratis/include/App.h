#ifndef App_H
#define App_H

#include <Arduino.h>


struct Info
{
  String gameName;
  String fileNameLogo;
};

class App
{

public:
  virtual Info getInfo() = 0;
  virtual void run() = 0;
};

#endif