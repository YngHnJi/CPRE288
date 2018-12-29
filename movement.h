/**
* @file movement.h
* @brief Header file for functions related with movement combining with Uart to send messages
* @author Younghoon Ji, Emily Kinne
* @date Nov 26, 2018
*/

#ifndef MOVEMENT_H_
#define MOVEMENT_H_


#include "open_interface.h"
#include <stdio.h>
#include "uart.h""

//Move forward including collision detection
void move_forward(oi_t *sensor_data, int dist);
//Move Backward
void move_backward(oi_t *sensor, int centermeter);
//Turn clockwise
void turn_clockwise(oi_t *sensor, int degrees);
//Turn counter Clock wise
void turn_counterclockwise(oi_t *sensor, int degrees);
//detect line and cliffs, which is used in move_forward function
int linedetector(oi_t *sensor);


#endif /* MOVEMENT_H_ */
