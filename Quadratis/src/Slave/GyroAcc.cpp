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
    
    if(accelgyro.testConnection())
    {
        Serial.println("MPU6050 connection successful");
    }
    else
    {
        Serial.println("MPU6050 connection failed, restarting.....");
        ESP.restart();
        delay(1000);
    }
}

GyroAcc::~GyroAcc()
{
}

void GyroAcc::getSensorData()
{
    
}

boolean GyroAcc::getShaking()
{
  int16_t accArray[3];
  getAcceleration(accArray);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > INTERVAL) {
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
    //accData[0] = 5;
}

void GyroAcc::getGyro(int16_t gyroData[3])
{
    
    accelgyro.getAcceleration(&gyroData[0], &gyroData[1], &gyroData[2]);
}