#include <Arduino.h>
#include "DueServo.h"




void setup() {
  Serial.begin(9600);
        initServo(6);
         initServo(7);
          initServo(8);
           initServo(9);
}
int value=0;
void loop() {

  if (Serial.available()){
 int number=Serial.read();
  switch (number){
   case ';':
     value=100;
     Serial.println(value);
     break;
   case '.':
     value=0;
     Serial.println(value);
     break;
   case 'l':
     value++;
     Serial.println(value);
     break;
   case ',':
     value--;
     Serial.println(value);
     break;
   } 
   if (value>255)
   value=255;
   if (value<0)
   value=0;
   writeMicros(6, value);
   writeMicros(7, value);
   writeMicros(8, value);
   writeMicros(9, value);
}
  
}
