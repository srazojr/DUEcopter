#include <DueTimer.h>

//VEX_RX
#define VEX_RX_PIN 53

typedef enum {SYNC, CH1,CH2,CH3,CH4,CH5,CH6, INV} VEX_RX_STATE_t;
volatile VEX_RX_STATE_t vex_rx_state=INV;
volatile int vex_rx_ch_timings[]={0,0,0,0,0,0};
volatile int vex_rx_last_event=0;
volatile bool vex_rx_framing=false;
#define VEX_RX_MIN_SYNC_TIME 4000
////////////////////////////////////////


void vex_rx_time_isr(){
  if(micros()-vex_rx_last_event>20000){
    vex_rx_state=INV;
  }
}

void vex_rx_isr(){
  if (vex_rx_state==INV){
    
    //if we are invalid, wait for a falling edge to go to sync state, else stay in INV
    if(digitalRead(VEX_RX_PIN)==LOW){
      vex_rx_last_event=micros();
      vex_rx_state=SYNC;
    }
  }
  else if(vex_rx_state==SYNC){
    //if falling edge, stay in sync. 
    if(digitalRead(VEX_RX_PIN)==LOW){
      vex_rx_last_event=micros();
    }
    else{//if rising edge then check if it was a sync pulse
      int current_frame_time;
      current_frame_time=micros();
      current_frame_time-=vex_rx_last_event;
      
      if (current_frame_time>=VEX_RX_MIN_SYNC_TIME){//if it was a sync pulse then enter state CH1, else we stay in sync
        vex_rx_last_event=micros();
        vex_rx_state=CH1;
        vex_rx_framing=true;
      }
    } 
    
  }
  else if(vex_rx_state==CH1){
    if (vex_rx_framing==true){
     vex_rx_framing=false; 
    }
    else{
       int current_frame_time;
      current_frame_time=micros();
      current_frame_time-=vex_rx_last_event;
      vex_rx_ch_timings[0]=current_frame_time;
      
       vex_rx_last_event=micros();
        vex_rx_state=CH2;
        vex_rx_framing=true;
    }
    
  }
    else if(vex_rx_state==CH2){
    if (vex_rx_framing==true){
     vex_rx_framing=false; 
    }
    else{
       int current_frame_time;
      current_frame_time=micros();
      current_frame_time-=vex_rx_last_event;
      vex_rx_ch_timings[1]=current_frame_time;
      
       vex_rx_last_event=micros();
        vex_rx_state=CH3;
        vex_rx_framing=true;
    }
    
  }
  
    else if(vex_rx_state==CH3){
    if (vex_rx_framing==true){
     vex_rx_framing=false; 
    }
    else{
       int current_frame_time;
      current_frame_time=micros();
      current_frame_time-=vex_rx_last_event;
      vex_rx_ch_timings[2]=current_frame_time;
      
       vex_rx_last_event=micros();
        vex_rx_state=CH4;
        vex_rx_framing=true;
    }
    
  }
  
    else if(vex_rx_state==CH4){
    if (vex_rx_framing==true){
     vex_rx_framing=false; 
    }
    else{
       int current_frame_time;
      current_frame_time=micros();
      current_frame_time-=vex_rx_last_event;
      vex_rx_ch_timings[3]=current_frame_time;
      
       vex_rx_last_event=micros();
        vex_rx_state=CH5;
        vex_rx_framing=true;
    }
    
  }
  
    else if(vex_rx_state==CH5){
    if (vex_rx_framing==true){
     vex_rx_framing=false; 
    }
    else{
       int current_frame_time;
      current_frame_time=micros();
      current_frame_time-=vex_rx_last_event;
      vex_rx_ch_timings[4]=current_frame_time;
      
       vex_rx_last_event=micros();
        vex_rx_state=CH6;
        vex_rx_framing=true;
    }
    
  }
  
    else if(vex_rx_state==CH6){
    if (vex_rx_framing==true){
     vex_rx_framing=false; 
    }
    else{
       int current_frame_time;
      current_frame_time=micros();
      current_frame_time-=vex_rx_last_event;
      vex_rx_ch_timings[5]=current_frame_time;
      
       vex_rx_last_event=micros();
        vex_rx_state=SYNC;
        
    }
    
  }
  
}

void vex_rx_print(){
  
  if (vex_rx_state==INV){
      Serial1.println("INV");
      }
    else{
      for(int counter=0; counter<6; counter++){
        Serial1.print("CH");Serial1.print(counter+1);Serial1.print(": ");
        Serial1.print(vex_rx_ch_timings[counter]);Serial1.print("    ");   
      }
      Serial1.println(" ");
      }
      Serial1.flush();
      
}


///////////////////////////////////////////////
//END VEX_RX


void setup(){
        Serial1.begin(9600);
        
        //VEX RX
        attachInterrupt(53, vex_rx_isr, CHANGE);
	Timer.getAvailable().attachInterrupt(vex_rx_time_isr).start(20000);// Calls every 20ms
        //VEX RX
        
        
}

void loop(){
  //VEX RX vex_rx_ch_timings[0-5] and vex_rx_state void vex_rx_print()
    vex_rx_print();
  //END VEX RX
}
   
