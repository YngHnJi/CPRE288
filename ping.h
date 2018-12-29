/**
 * @file ping.h
 * @brief Header file for functions related with ping sensor
 * @author
 * @date
 *
 */

#ifndef PING_H_
#define PING_H_




#include "lcd.h"
# include "math.h"
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
#include "timer.h"
#include "driverlib/interrupt.h"

//ping initialize
void ping_init();
//send command to send pulse
int send_pulse();
//check the overflow happenend when it get digital values
int check_overflow(falling_time, rising_time);
//Timer Handler
void TIMER3B_Handler();
//Calculate the distance
float ping_getDistance();

#endif /* PING_H_ */
