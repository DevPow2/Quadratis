#include "GyroAcc.h"

GyroAcc::GyroAcc()
{
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  

  if (accelgyro.testConnection())
  {
    Serial.println("MPU6050 connection successful");
  }
  else
  {
    Serial.println("MPU6050 connection failed, restarting.....");
    vTaskDelay(1000);
    ESP.restart();
  }
}

GyroAcc::~GyroAcc()
{
}

int GyroAcc::getDirection()
{
   int16_t accArray[3];
  getAcceleration(accArray);

  unsigned long currentMillis = millis();

  int xAng = map(accArray[0], minVal, maxVal, -90, 90);
  int yAng = map(accArray[1], minVal, maxVal, -90, 90);
  int zAng = map(accArray[2], minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + 3.14159265358979323846);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + 3.14159265358979323846);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + 3.14159265358979323846);

  int screenOff = getScreenOff(x,y,z);
  int direction = getControls(prevScreen, screenOff);
  prevScreen = screenOff;
  return direction;

}
int GyroAcc::getControls(int prevScreen, int screenOff) {

  // Screen 1
  if (prevScreen == 1) {
    if (screenOff == 3) {
      Serial.println("Move Forward");
      return 1;
    }
    if (screenOff == 5) {
      Serial.println("Move Backwards");
      return 2;
    }
    if (screenOff == 2) {
      Serial.println("Move Right");
      return 3;
    }
    if (screenOff == 4) {
      Serial.println("Move Left");
      return 4;
    }
  }

  // Screen 2
  if (prevScreen == 2) {
    if (screenOff == 3) {
      Serial.println("Move Forward");
      return 1;
    }
    if (screenOff == 5) {
      Serial.println("Move Backwards");
      return 2;
    }
    if (screenOff == 6) {
      Serial.println("Move Right");
      return 3;
    }
    if (screenOff == 1) {
      Serial.println("Move Left");
      return 4;
    }
  }

  // Screen 3
  if (prevScreen == 3) {
    if (screenOff == 4) {
      Serial.println("Move Forward");
      return 1;
    }
    if (screenOff == 2) {
      Serial.println("Move Backwards");
      return 2;
    }
    if (screenOff == 6) {
      Serial.println("Move Right");
      return 3;
    }
    if (screenOff == 1) {
      Serial.println("Move Left");
      return 4;
    }
  }

  // Screen 4
  if (prevScreen == 4) {
    if (screenOff == 5) {
      Serial.println("Move Forward");
      return 1;
    }
    if (screenOff == 3) {
      Serial.println("Move Backwards");
      return 2;
    }
    if (screenOff == 6) {
      Serial.println("Move Right");
      return 3;
    }
    if (screenOff == 1) {
      Serial.println("Move Left");
      return 4;
    }
  }

  // Screen 5
  if (prevScreen == 5) {
    if (screenOff == 2) {
      Serial.println("Move Forward");
      return 1;
    }
    if (screenOff == 4) {
      Serial.println("Move Backwards");
      return 2;
    }
    if (screenOff == 6) {
      Serial.println("Move Right");
      return 3;
    }
    if (screenOff == 1) {
      Serial.println("Move Left");
      return 4;
    }
  }

  // Screen 6
  if (prevScreen == 6) {
    if (screenOff == 3) {
      Serial.println("Move Forward");
      return 1;
    }
    if (screenOff == 5) {
      Serial.println("Move Backwards");
      return 2;
    }
    if (screenOff == 4) {
      Serial.println("Move Right");
      return 3;
    }
    if (screenOff == 2) {
      Serial.println("Move Left");
      return 4;
    }
  }
  return -1;
}
int GyroAcc::getScreenOff(int16_t x, int16_t y, int16_t z)
{
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
}

boolean GyroAcc::getShaking()
{
  int16_t accArray[3];
  getAcceleration(accArray);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > INTERVAL)
  {
    previousMillis = currentMillis;
    if (!topMode)
    {
      unsigned long tempX = getDal(accArray[0]);
      if (tempX != 0)
      {
        dal[dalCounter][X] = tempX;
      }
      unsigned long tempY = getDal(accArray[1]);
      if (tempY != 0)
      {
        dal[dalCounter][Y] = tempY;
      }
      unsigned long tempZ = getDal(accArray[2]);
      if (tempZ != 0)
      {
        dal[dalCounter][Y] = tempZ;
      }
      if (tempX != 0 || tempY != 0 || tempZ != 0)
      {
        dalCounter++;
      }
    }
    else
    {
      unsigned long tempX = getTop(accArray[0]);
      if (tempX != 0)
      {
        top[topCounter][X] = tempX;
      }
      unsigned long tempY = getTop(accArray[1]);
      if (tempY != 0)
      {
        top[topCounter][Y] = tempY;
      }
      unsigned long tempZ = getTop(accArray[2]);
      if (tempZ != 0)
      {
        top[topCounter][Z] = tempZ;
      }
      if (tempX != 0 || tempY != 0 || tempZ != 0)
      {
        topCounter++;
      }
    }
  }
  if (dalCounter > DEPTH - 1 || topCounter > DEPTH - 1)
  {
    dalCounter = 0;
    topCounter = 0;
    boolean result = handleShake(dal, top);
    unsigned long temp[DEPTH][AXES] = {0, 0};
    memcpy(dal, temp, sizeof(dal));
    memcpy(top, temp, sizeof(top));
    return result;
  }
  return false;
}

boolean GyroAcc::handleShake(unsigned long dal[DEPTH][AXES], unsigned long top[DEPTH][AXES])
{
  int i;
  int j;
  int total = 0;
  int start = 0;
  for (i = 0; i < AXES; i++)
  {
    for (j = 0; j < DEPTH; j++)
    {
      if (j == 0)
      {
        start = top[j][i];
      }
      total += dal[j][i] - top[j][i];
    }

    if ((total / DEPTH) <= INTERVAL + 1 && start != 0)
    {
      Serial.println("SCHUDDEENNNN");
      return true;
    }
  }
  return false;
}

unsigned long GyroAcc::getDal(int16_t x)
{
  if (abs(x) > TRESHOLDVALUE)
  {
    topMode = !topMode;
    return millis();
  }
  return 0;
}

unsigned long GyroAcc::getTop(int16_t x)
{
  if (x > TRESHOLDVALUE)
  {
    topMode = !topMode;
    return millis();
  }
  return 0;
}

void GyroAcc::getAcceleration(int16_t accData[3])
{
  accelgyro.getAcceleration(&accData[0], &accData[1], &accData[2]);
}

void GyroAcc::getGyro(int16_t gyroData[3])
{

  accelgyro.getAcceleration(&gyroData[0], &gyroData[1], &gyroData[2]);
}