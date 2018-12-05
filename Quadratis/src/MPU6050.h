#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <Input.h>

class MPU6050 : public Input
{
    // Access specifier
  public:
    // Data Members
    // string geekname;

    // Member Functions()
    MPU6050();
    ~MPU6050();
    void getSensorData();
};

#endif
