/**
 * Hardware servo library. Available pins on the Arduino Due: 6, 7, 8, 9.
 */
#ifndef DUE_SERVO_H
#define DUE_SERVO_H

#include <Arduino.h>

#define PWM_DUTY_MIN    0
#define PWM_DUTY_MAX    255

void writeMicros(int pin, uint16_t speed);//speed is from 0-255
void initServo(int pin);
#endif
