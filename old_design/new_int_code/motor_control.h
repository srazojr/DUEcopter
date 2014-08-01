

//motor_control.h
/*
void initializemotors();
      call this function to initialize 4 motors
      the motors should be on pins 6,7,8,9
      the motors are called 6,7,8,9
      this should only be called one time in void setup()
void write_motor(int pin, int speed);
      sets the speed of motor "pin" to "speed"
      acceptable values for speed are 0-1000
      if speed>1000, then speed =1000
      if speed<0 then speed=0
int current_speed_motor(int pin);
      returns the current speed of motor "pin"
*/






//declarations for motors
#include<Arduino.h>
void write_motor(int pin, int speed);//speed is from 0-255
void init_motor(int pin);//pins 6,7,8,9
int current_speed_motor(int pin);
void initializemotors();
static bool PWMEnabled = false;//start with everything disabled
current_motor_speed_array[4];
//end motor declarations






//motor functions================================================================================
void initializemotors(){
        init_motor(6);
        init_motor(7);
        init_motor(8);
        init_motor(9);
}
void init_motor(int pin) {
        if(!PWMEnabled) {
                pmc_enable_periph_clk(PWM_INTERFACE_ID);//turn on the clock
                PWMC_ConfigureClocks(1000000, 0, VARIANT_MCK);
                PWMEnabled = true;
        }
        const PinDescription *config = &g_APinDescription[pin];
        int channel = config->ulPWMChannel;
        if(channel == NOT_ON_PWM)
                return;

        PIO_Configure(
                config->pPort,
                config->ulPinType,
                config->ulPin,
                config->ulPinConfiguration);
        PWMC_ConfigureChannel(PWM_INTERFACE, channel, PWM_CMR_CPRE_CLKA, 0, 0);
        PWMC_SetPeriod(PWM_INTERFACE, channel, 10000);//set period
        write_motor(pin, 0);//initialize the motor at 0 speed(1000ms pulse)
        PWMC_EnableChannel(PWM_INTERFACE, channel);
}

void write_motor(int pin, int dutyCycle) {//duty cycle=0-1000
        int channel = g_APinDescription[pin].ulPWMChannel;
        if(channel == NOT_ON_PWM)
                return;
        //check range
        if(dutyCycle < 0)
                dutyCycle = 0;
        if(dutyCycle > 1000)
                dutyCycle = 1000;
        PWMC_SetDutyCycle(PWM_INTERFACE, channel, 1000+dutyCycle);//set speed
        current_motor_speed_array[pin-6]=dutyCycle;
}
int current_speed_motor(int pin){
  return current_motor_speed_array[pin-6];
}
//motor functions================================================================================
