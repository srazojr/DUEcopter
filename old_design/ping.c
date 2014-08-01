//ping sensor things
#define FRONT_PING   46
#define BACK_PING    48  
#define STAR_PING    50
#define PORT_PING    52
#define TRIG_PING    35
unsigned long  trigger_start_time;
unsigned long front_ping_distance, back_ping_distance, star_ping_distance, port_ping_distance;

void setup(){
  init_ping();
  
  Serial.begin(9600);
 
}


 unsigned long delays;

void loop(){
  commence_pinging_trigger();
  //code
  Serial.print(front_ping_distance);
   Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n");
   /*
   Serial.print("FRONT: ");
   Serial.print(front_ping_distance);
   Serial.print("\nPORT: ");
   Serial.print(port_ping_distance);
   Serial.print("\nSTARBOARD: ");
   Serial.print(star_ping_distance);
   Serial.print("\nBACK: ");
   Serial.print(back_ping_distance);
   
 */
 
 
 for (delays=0;delays<4000000;delays++){}
 
}




void init_ping(){
  pinMode(FRONT_PING, INPUT);
  pinMode(BACK_PING, INPUT);
  pinMode(STAR_PING, INPUT);
  pinMode(PORT_PING, INPUT);
  
  pinMode(TRIG_PING, OUTPUT);
  
  digitalWrite(TRIG_PING, LOW);
  front_ping_distance=0;
  star_ping_distance=0;
  back_ping_distance=0;
  port_ping_distance=0;
  return;
}




void commence_pinging_trigger(){

  //initialize the timer and the interupts
  
  //attachInterrupt(BACK_PING,  back_ping_interrupt,  FALLING);
  //attachInterrupt(STAR_PING,  star_ping_interrupt,  FALLING);
 // attachInterrupt(PORT_PING,  port_ping_interrupt,  FALLING);
   digitalWrite(TRIG_PING, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PING, LOW);
  attachInterrupt(FRONT_PING, front_ping_interrupt, FALLING);
  trigger_start_time=micros();
  
  return ;
}


void front_ping_interrupt(){
unsigned long current_time;

  current_time=micros();
  front_ping_distance=ping_distance_calculation(current_time);
  detachInterrupt(FRONT_PING);
  
 return; 
}




unsigned long ping_distance_calculation(unsigned long current_time){
unsigned long  delta_time,overflow_check=0;
  float inches;
  
  if (current_time<=trigger_start_time)// no overflow
  {
    overflow_check=0xFFFFFFFF;
  }
  delta_time=overflow_check+trigger_start_time-current_time;
  //73.746 us/inch so (delta_time us/pulse)*(1 inch/73.746us)* (1 pulse/2 trip)=inches/trip
  //inches=(float) delta_time/(147.492);
  return delta_time;  
}