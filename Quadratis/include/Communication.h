#ifndef Communication_H
#define Communication_H

#include <Arduino.h>

class Communication
{

private:
  static Communication *instance;

  Communication(); //Constructor

public:
  ~Communication(); //deconstructor

  static Communication *getInstance();

  static String split(String data, char separator, int index);
  String readSerial();
  void writeSerial(String message);
};

#endif
