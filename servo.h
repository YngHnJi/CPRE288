/**
* @file servo.h
* @brief Header file related with control servo
* @author
* @date
*/


#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include <timer.h>
#include <lcd.h>
#include <math.h>
#include <stdbool.h>

//servo initialize
void servo_init(void);
//make servo moved
void servo_move(int degrees);

#endif /* SERVO_H_ */
