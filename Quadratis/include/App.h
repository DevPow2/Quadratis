#ifndef App_H
#define App_H

#include <Arduino.h>

// struct Image
// {
//   unsigned int width;
//   unsigned int height;
//   unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
//   unsigned char pixel_data[320 * 240 * 2 + 1];
// };

struct Info
{
  String gameName;
  // Image image;
};

class App
{

public:
  virtual Info getInfo() = 0;
  virtual void run() = 0;
};

#endif