#include<Wire.h>

const int MPU_addr=0x68; int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265; int maxVal=402;

double x; double y; double z;
int screenOff;

void setup(){
  Wire.begin(21 , 22, 400000);
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true); 
  Serial.begin(9600); 
  } 
  
  void loop(){ 
    Wire.beginTransmission(MPU_addr); 
    Wire.write(0x3B); 
    Wire.endTransmission(false); 
    Wire.requestFrom(MPU_addr,14,true); 
//    screenOff = 0;
    AcX=Wire.read()<<8|Wire.read(); 
    AcY=Wire.read()<<8|Wire.read(); 
    AcZ=Wire.read()<<8|Wire.read(); 
    int xAng = map(AcX,minVal,maxVal,-90,90); 
    int yAng = map(AcY,minVal,maxVal,-90,90); 
    int zAng = map(AcZ,minVal,maxVal,-90,90);
    
    x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
    y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
    z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

    // Kantel naar achter
    if(y >= 40 && y <= 140){
      screenOff = 1;
    }

    // Onderste Boven
    if(x >= 150 && x <= 210 && y >= 150 && y <= 210){
      screenOff = 2;
    }

    // Kantel naar voren 
    if(y >= 240){
      screenOff = 3;
    }

    // Normaal 
    if(x >= 337 || x <= 22 && y >= 337 || y <= 22){
      screenOff = 4;
    }

    // Kantel naar links
    if(x >= 240 && x <= 300 && y >= 180){
      screenOff = 5;
    }

    // Kantel naar rechts
    if(x >= 60 && x <= 150 && y <= 180){
      screenOff = 6;
    }

    

Serial.print("AngleX= "); Serial.println(x);

Serial.print("AngleY= "); Serial.println(y);

Serial.print("AngleZ= "); Serial.println(z);

 Serial.print("Screen Off= "); Serial.println(screenOff);
Serial.println("-----------------------------------------"); 
delay(400); 
}
