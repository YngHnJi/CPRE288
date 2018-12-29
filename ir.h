/**
* @file ir.h
* @brief Header file in order to use ADC, IR sensor
* @author
* @date
*/

#ifndef IR_H_
#define IR_H_

#include <stdio.h>
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <timer.h>
#include <lcd.h>
#include <math.h>

//ADC initialize
void ADC0_init();
//get the digital value from IR sensor
int ADC0_readData();
//calculate the distance from the value gotten by ADC0_readData
double ADC0_getDistance(int value);

#endif /* IR_H_ */
