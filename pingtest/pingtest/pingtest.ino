#include <DueTimer.h>
#define PING_TIMEOUT 60000
//every 60ms

class ping_sensor {
	int triggerPin, echoPin;//ints holding the pins these are
        bool active;//to deactivate a sensor
	long duration;//internal value to hold raw duration of sensor in usec
	int last_event;

        static ping_sensor* activeSensor;//the sensro the ISR will target
        static ping_sensor* tail;//the last sensor active
        static int sensors;
        static DueTimer * ping_timeout_timer;//timer that means a timeout happened
        ping_sensor* next;//next sensor in the list
        void trigger();//state
        void echo(void);//state
        void timeout(void);
     public:
        void begin(int,int);//adds the new sensor to the linked list, initialization
        long inches,cm;//public measurements
        void attach(){active=true;}
        void detach(){active=false;};
        static void ping_ISR(void){ activeSensor->echo();};
        static void ping_timeout(void){activeSensor->timeout();};
};

void ping_sensor::begin(int trigger, int echo){
  sensors++;
  triggerPin=trigger;echoPin=echo;
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(triggerPin, LOW);
    cm=0;
    inches=0;
    this->attach();
    
   if(sensors>1){
      this->next=tail->next;
      tail->next=this;
      tail=this;
    } else {
      
      tail=this;
      this->next=this;
      activeSensor = this;
      
      ping_timeout_timer=&Timer.getAvailable().attachInterrupt(ping_timeout).start(PING_TIMEOUT);
      this->trigger();
    }

  }
  
  
  
  
  
  
void ping_sensor::trigger(){
 
  if(this->active){

    digitalWrite(triggerPin,LOW);
    digitalWrite(triggerPin,HIGH); 

 
    last_event=micros();
    attachInterrupt(echoPin,ping_ISR,CHANGE);
       digitalWrite(triggerPin, LOW); 
  } else {
    
    
  }
  
}

void ping_sensor::echo(){
  
 if(digitalRead(echoPin)==HIGH){
   
   last_event=micros();   
 } 
 else 
 {

   int new_event;
   new_event=micros();
   //if (new_event>last_event){
   duration=new_event-last_event;
   //}
   //else handle overflow
   
   inches = duration / 74 / 2;
   cm = inches*2.54;
   //Serial1.println(inches);
   
  detachInterrupt(echoPin);
   //ping_timeout_timer->stop();
  
  last_event=micros();
 } 
}

void ping_sensor::timeout(){
  
  if ((micros()-last_event)>40000){
  inches=156;
  cm=400;
  } 
  //detachInterrupt(echoPin);
   //ping_timeout_timer->stop();
  activeSensor=this->next;
  activeSensor->trigger();

}




int ping_sensor::sensors=0;
ping_sensor* ping_sensor::activeSensor;
ping_sensor* ping_sensor::tail;//the last sensor active
DueTimer * ping_sensor::ping_timeout_timer;//timer that means a timeout happened




 ping_sensor  ping,ping1,ping2,ping3;
void setup() {
  
  // put your setup code here, to run once:
  
  Serial1.begin(9600);
   ping.begin(25,23);
   ping1.begin(29,27);
   ping2.begin(33,31);
   ping3.begin(37,35);
}

void loop() {
  ping.detach();
  ping1.detach();
  ping2.detach();
  ping3.detach();
  Serial1.println(" ");
 Serial1.print("inches:  ");
 Serial1.print(ping.inches);Serial1.print("   ");
 Serial1.print(ping1.inches);Serial1.print("   ");
 Serial1.print(ping2.inches);Serial1.print("   ");
 Serial1.println(ping3.inches);
 
 Serial1.print("cm    :  ");
 Serial1.print(ping.cm);Serial1.print("   ");
 Serial1.print(ping1.cm);Serial1.print("   ");
 Serial1.print(ping2.cm);Serial1.print("   ");
 Serial1.println(ping3.cm);
 Serial1.flush();
   ping.attach();
  ping1.attach();
  ping2.attach();
  ping3.attach();
 delay(100);
 
  // put your main code here, to run repeatedly:

}
