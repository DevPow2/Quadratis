#include "Shake.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  setupShake();
  
}

void loop() {
  // put your main code here, to run repeatedly:

    boolean result = getShaking();
    
    if(result) Serial.println(result);
}
