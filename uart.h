/**
* @file uart.h
* @brief Header file related with UART, communicating between computer and robot
* @author Younghoon Ji, Emily Kinne
* @date Nov 27, 2018
*/


#ifndef UART_H_
#define UART_H_

#include "uart.h"

//UART initialize
void uart_init(void);

//Send Character from robot to Putty
void uart_sendChar(char data);

//receive Character from Putty to robot
char uart_receive(void);

//Send String from robot to Putty
void uart_sendStr(char *data);


#endif /* UART_H_ */
