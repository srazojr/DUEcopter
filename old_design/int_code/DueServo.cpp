/**
 * Hardware Servo library. Available pins on the Arduino Due: 6, 7, 8, 9
 */
 
 
#include "DueServo.h"

#define PWM_CLOCK       1000000
#define PWM_PERIOD      10000

static bool PWMEnabled = false;

void initServo(int pin) {
        if(!PWMEnabled) {
                pmc_enable_periph_clk(PWM_INTERFACE_ID);
                PWMC_ConfigureClocks(PWM_CLOCK, 0, VARIANT_MCK);
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
        PWMC_SetPeriod(PWM_INTERFACE, channel, PWM_PERIOD);
        writeMicros(pin, 1000);
        PWMC_EnableChannel(PWM_INTERFACE, channel);
}

void writeMicros(int pin, uint16_t dutyCycle) {
        int channel = g_APinDescription[pin].ulPWMChannel;

        if(channel == NOT_ON_PWM)
                return;

        if(dutyCycle < PWM_DUTY_MIN)
                dutyCycle = PWM_DUTY_MIN;
        if(dutyCycle > PWM_DUTY_MAX)
                dutyCycle = PWM_DUTY_MAX;

        PWMC_SetDutyCycle(PWM_INTERFACE, channel, 1000+dutyCycle*1000/255);
        
        
}
