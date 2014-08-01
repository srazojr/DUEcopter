// program to test overflow of micros();
unsigned long new_time, old_time;
void setup(){
Serial.begin(9600);
}
void loop(){
  Serial.print("old time:  ");
  Serial.println((old_time=micros()) );
  delay(100);
  if(old_time>(new_time=micros())){
    Serial.print("there has been carry over");
    Serial.print("old time: ");
    
    Serial.println(old_time);
    
    Serial.print("new time:  ");
    Serial.println(new_time);
    while(true){}
  }
    Serial.print("new time:  ");
    Serial.println(new_time);
    Serial.println();

}
  
  
