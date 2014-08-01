#include otor_control.h

void setup() {
  Serial.begin(9600);
  //initialize each motor
  initializemotors();
  //end motor initialization
}

int value=0;
void loop() {

  
  //only run if serial available
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
   write_motor(6, value);
   write_motor(7, value);
   write_motor(8, value);
   write_motor(9, value);
}
  
}





