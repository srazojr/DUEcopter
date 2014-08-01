#include <Wire.h>

#include "IMU.h"

void setup(){
  Serial.begin(9600);
  initialize_12c();
}

void loop(){
  
  int  dataAccel[3];
  int dataGyro[3];
  //int *temperature;
  //updateTemp(temperature);
  updateAccel(dataAccel);
  updateGyro(dataGyro);

  Serial.print("x: ");
  Serial.println(dataAccel[0]);
  Serial.print("y: ");
  Serial.println(dataAccel[1]);
  Serial.print("z: ");
  Serial.println(dataAccel[2]);
  
  Serial.print("theta: ");
  Serial.println(dataGyro[0]);
  Serial.print("omega: ");
  Serial.println(dataGyro[1]);
  Serial.print("omicron: ");
  Serial.println(dataGyro[2]);
  
  //Serial.print("temp:  ");
  //Serial.println((int) &temperature);


  Serial.print("degrees ");
  Serial.println(DegreesYaw());
  delay(500);
  
  
 
  
  
}
  

