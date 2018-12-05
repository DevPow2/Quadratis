#include "Shake.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int16_t lastTop = 0;
int16_t lastDal = 0;
unsigned long dal[DEPTH][AXES] = {{0, 0}};
unsigned long top[DEPTH][AXES] = {{0, 0}};

int topCounter = 0;
int dalCounter = 0;

long previousMillis = 0;

boolean topMode = true;

void setupShake()
{
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
//  Serial.begin(38400);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  
}

boolean getShaking()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > INTERVAL) {
    previousMillis = currentMillis;
    if (!topMode)
    {
      unsigned long tempX = getDal(ax);
      if (tempX != 0)
      {
        dal[dalCounter][X] = tempX;
      }
      unsigned long tempY = getDal(ay);
      if (tempY != 0)
      {
        dal[dalCounter][Y] = tempY;

      }
      unsigned long tempZ = getDal(az);
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
      unsigned long tempX = getTop(ax);
      if (tempX != 0)
      {
        top[topCounter][X] = tempX;
      }
      unsigned long tempY = getTop(ay);
      if (tempY != 0)
      {
        top[topCounter][Y] = tempY;
      }
      unsigned long tempZ = getTop(az);
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

boolean handleShake(unsigned long dal[DEPTH][AXES], unsigned long top[DEPTH][AXES])
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

unsigned long getDal(int16_t x)
{
  if (abs(x) > TRESHOLDVALUE)
  {
    topMode = !topMode;
    return millis();
  }
  return 0;
}

unsigned long getTop(int16_t x)
{
  if (x > TRESHOLDVALUE)
  {
    topMode = !topMode;
    return millis();
  }
  return 0;
}
