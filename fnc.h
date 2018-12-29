/**
* @file fnc.c
* @brief C file in order to operate cyBot.
* @author Younghoon Ji, Emily Kinne
* @date Nov 30, 2018
*/


#ifndef FNC_H_
#define FNC_H_

#include <movement.h>
#include <stdio.h>
#include <uart.h>
#include "lcd.h"
#include "open_interface.h"
#include "timer.h"
#include "ping.h"
#include "ir.h"
#include "servo.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void scan();
void flash();
void music();
void LED ();



#endif /* FNC_H_ */
