// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//      2013-05-08 - added multiple output formats
//                 - added seamless Fastwire support
//      2011-10-07 - initial release

/* ============================================
  I2Cdev device library code is placed under the MIT license
  Copyright (c) 2011 Jeff Rowberg

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  ===============================================
*/

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
//#include "MPU9250.h"
//#include ""


// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 50;           // interval at which to blink (milliseconds)

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

//MPU9250 IMU(Wire, 0x68);
int status;

int16_t ax, ay, az;

int minVal = 265; int maxVal = 402;

bool XnegMD, XposMD, YnegMD, YposMD, ZnegMD, ZposMD;
bool zero_detect;


/* magnetometer data */
float h, hx, hy, hz;
/* magnetometer calibration data */
float hxb, hxs, hyb, hys, hzb, hzs;
/* euler angles */
float yaw_rad, heading_rad;
/* filtered heading */
float filtered_heading_rad;
float window_size = 20;
/* conversion radians to degrees */
const float R2D = 180.0f / PI;

double x, y, z;
int screenOff, prevScreen;


// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO


//#define INTERRUPT_PIN 15  // use pin 2 on Arduino Uno & most boards
//#define LED_PIN 2
bool blinkState = false;


void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(38400);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // use the code below to change accel/gyro offset values
}

void loop() {
  // read raw accel/gyro measurements from device
  //   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);



  // these methods (and a few others) are also available
  accelgyro.getAcceleration(&ax, &ay, &az);
  // accelgyro.getRotation(&gx, &gy, &gz);


#ifdef OUTPUT_READABLE_ACCELGYRO
  // display tab-separated accel/gyro x/y/z values

  int xAng = map(ax, minVal, maxVal, -90, 90);
  int yAng = map(ay, minVal, maxVal, -90, 90);
  int zAng = map(az, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);


  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    getScreenOff(x, y, z);
  }

  getControls(prevScreen, screenOff, x, y, z);

  prevScreen = screenOff;

#endif
}

void getScreenOff(int16_t x, int16_t y, int16_t z) {
  // Normaal
  if ((y >= 45 && y <= 135) && (x >= 90) && (z >= 315 || z <= 45)) {
    screenOff = 2;
  }

  // Kantel naar voren
  if ((x >= 135 && x <= 225) && (y >= 135 && y <= 225) ) {
    screenOff = 5;
  }

  // Onderste Boven
  if ((x >= 180 && x <= 270) && (y >= 225 && y <= 315) && (z >= 135 && z <= 225)) {
    screenOff = 4;
  }

  // Kanel naar voren
  if ((x >= 315 || x <= 45 ) && (y >= 315 || y <= 45) && (z >= 180 && z <= 270)) {
    screenOff = 3;
  }

  // Kantel naar links
  if ((x >= 225 && x <= 315) && (y >= 180 && y <= 270) && (z >= 225 && z <= 315)) {
    screenOff = 1;
  }

  // Kantel naar rechts
  if ((x >= 45 && x <= 135) && (y >= 180 && y <= 270) && (z <= 135 && z >= 45)) {
    screenOff = 6;
  }
      Serial.print(" ");
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
  
      Serial.print(" "); Serial.println(z);
  
      Serial.print("Screen Off= "); Serial.println(screenOff);
}

void getControls(int prevScreen, int screenOff, int16_t x, int16_t y, int16_t z) {

  // Screen 1
  if (prevScreen == 1) {
    if (screenOff == 3) {
      Serial.println("Move Forward");
    }
    if (screenOff == 5) {
      Serial.println("Move Backwards");
    }
    if (screenOff == 2) {
      Serial.println("Move Right");
    }
    if (screenOff == 4) {
      Serial.println("Move Left");
    }
  }

  // Screen 2
  if (prevScreen == 2) {
    if (screenOff == 3) {
      Serial.println("Move Forward");
    }
    if (screenOff == 5) {
      Serial.println("Move Backwards");
    }
    if (screenOff == 6) {
      Serial.println("Move Right");
    }
    if (screenOff == 1) {
      Serial.println("Move Left");
    }
  }

  // Screen 3
  if (prevScreen == 3) {
    if (screenOff == 4) {
      Serial.println("Move Forward");
    }
    if (screenOff == 2) {
      Serial.println("Move Backwards");
    }
    if (screenOff == 6) {
      Serial.println("Move Right");
    }
    if (screenOff == 1) {
      Serial.println("Move Left");
    }
  }

  // Screen 4
  if (prevScreen == 4) {
    if (screenOff == 5) {
      Serial.println("Move Forward");
    }
    if (screenOff == 3) {
      Serial.println("Move Backwards");
    }
    if (screenOff == 6) {
      Serial.println("Move Right");
    }
    if (screenOff == 1) {
      Serial.println("Move Left");
    }
  }

  // Screen 5
  if (prevScreen == 5) {
    if (screenOff == 2) {
      Serial.println("Move Forward");
    }
    if (screenOff == 4) {
      Serial.println("Move Backwards");
    }
    if (screenOff == 6) {
      Serial.println("Move Right");
    }
    if (screenOff == 1) {
      Serial.println("Move Left");
    }
  }

  // Screen 6
  if (prevScreen == 6) {
    if (screenOff == 3) {
      Serial.println("Move Forward");
    }
    if (screenOff == 5) {
      Serial.println("Move Backwards");
    }
    if (screenOff == 4) {
      Serial.println("Move Right");
    }
    if (screenOff == 2) {
      Serial.println("Move Left");
    }
  }

}
