/*
have 4 global start and stop times and distances
initialize function
	start al proper inputs
	set in to low
	
update ping distances
this will attach 4 interrupts looking for high
update all distances to 0
send the high pulse and return

start pulse interrupts
start the time
attach low interupts

low interupts
stop time
dettach interupts
calculate distance

calculate distance
check overflow
set the distance
*/
#define PING_STAR_PIN 	46
#define PING_PORT_PIN 	48
#define PING_FRONT_PIN 	50
#define PING_BACK_PIN 	52
#define PING_TRIG_PIN 	35


unsigned long ping_star_start_time, ping_port_start_time, ping_back_start_time
				ping_front_start_time, 
			  ping_star_stop_time, ping_port_stop_time, ping_back_stop_time
				ping_front_stop_time;
float	      ping_star_distance, ping_port_distance, ping_back_distance,
			    ping_front_distance;
			  
void ping_initialize(){
pinMode(PING_TRIG_PIN, OUTPUT);
digitalWrite(PING_TRIG_PIN, LOW);

pinMode(PING_PORT_PIN, INPUT);
pinMode(PING_STAR_PIN, INPUT);
pinMode(PING_BACK_PIN, INPUT);
pinMode(PING_FRONT_PIN, INPUT);
return;
}

void ping_update_distances(){
attachInterupt(PING_FRONT_PIN, ping_front_rising, HIGH);
attachInterupt(PING_STAR_PIN, ping_star_rising, HIGH);
attachInterupt(PING_BACK_PIN, ping_back_rising, HIGH);
attachInterupt(PING_PORT_PIN, ping_port_rising, HIGH);

digitalWrite(PING_TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(PING_TRIG_PIN, LOW);
return;
}


void ping_front_rising(){
ping_front_start_time=micros();
attachInterrupt(PING_FRONT_PIN, ping_front_falling, LOW);
return;
}
void ping_front_falling(){
ping_front_stop_time=micros();
//check overflow
ping_front_stop_time-=ping_front_start_time-((ping_front_stop_time<ping_front_start_time)?0xFFFFFFFF, 0x00000000);
//convert  us to inches:
//(1 total time/ 2 distances)*340.19m/s*(1s/10^6us)*(100cm/1m)*(1 inch/2.54cm)=1/149.328
ping_front_distance=(float) ping_front_stop_time/149.328;

//set ping_front_distance
return;}


void ping_back_rising(){
ping_back_start_time=micros();
attachInterrupt(PING_BACK_PIN, ping_back_falling, LOW);
return;
}
void ping_back_falling(){
ping_back_stop_time=micros();
//check overflow
ping_back_stop_time-=ping_back_start_time-((ping_back_stop_time<ping_back_start_time)?0xFFFFFFFF, 0x00000000);
//convert  us to inches:
//(1 total time/ 2 distances)*340.19m/s*(1s/10^6us)*(100cm/1m)*(1 inch/2.54cm)=1/149.328
ping_back_distance=(float) ping_back_stop_time/149.328;

//set ping_front_distance
return;}

void ping_port_rising(){
ping_port_start_time=micros();
attachInterrupt(PING_PORT_PIN, ping_port_falling, LOW);
return;
}
void ping_front_falling(){

ping_port_stop_time=micros();
//check overflow
ping_port_stop_time-=ping_port_start_time-((ping_port_stop_time<ping_port_start_time)?0xFFFFFFFF, 0x00000000);
//convert  us to inches:
//(1 total time/ 2 distances)*340.19m/s*(1s/10^6us)*(100cm/1m)*(1 inch/2.54cm)=1/149.328
ping_port_distance=(float) ping_port_stop_time/149.328;

//set ping_front_distance
return;}

void ping_star_rising(){
ping_star_start_time=micros();
attachInterrupt(PING_STAR_PIN, ping_star_falling, LOW);
return;
}
void ping_star_falling(){
ping_star_stop_time=micros();
//check overflow
ping_star_stop_time-=ping_star_start_time-((ping_star_stop_time<ping_star_start_time)?0xFFFFFFFF, 0x00000000);
//convert  us to inches:
//(1 total time/ 2 distances)*340.19m/s*(1s/10^6us)*(100cm/1m)*(1 inch/2.54cm)=1/149.328
ping_star_distance=(float) ping_star_stop_time/149.328;

//set ping_front_distance
return;}


