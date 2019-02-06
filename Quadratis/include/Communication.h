#ifndef Communication_H
#define Communication_H

#include <Arduino.h>

#define TX_COMMUNICATION 16
#define RX_COMMUNICATION 17

class Communication
{

private:
  static Communication *instance;

  Communication(); //Constructor

public:
  ~Communication(); //deconstructor

  static Communication *getInstance();

  String readSerial();
  void writeSerial(String message);
};

#endif
