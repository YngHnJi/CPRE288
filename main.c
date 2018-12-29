/**
* @file main.c
* @brief main C file to operate the robot
* @author Younghoon Ji, Emily Kinne
* @date Nov 30, 2018
*/
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
#include "fnc.h"


//compatiable code for cyBot 9, cyBot 12

void main()
{
    //initial all functions and sensors at once



    lcd_init();
    ADC0_init();
    ping_init();
    servo_init();
    uart_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);


    /*
     * This code is operated by Putty over Wifi
     * It can be controlled by 'w', 's', 'a', 'd', 'r', 'q'
     *
     */



    while (1)
    {
        oi_update(sensor_data);

        //putty
        char receive = uart_receive();

        if (receive == 'w') //move forward
        {
            char message_moveforward[] = "Moving Forward\r\n";
            uart_sendStr(message_moveforward);
            move_forward(sensor_data, 50);

        }

        else if (receive == 's') //move backward
        {
            char message_movebackward[] = "Moving Backward\r\n";
            uart_sendStr(message_movebackward);
            move_backward(sensor_data, 50);
        }

        else if (receive == 'a') //turn left
        {
            char message_Turningleft[] = "Turning Left\r\n";
            uart_sendStr(message_Turningleft);
            turn_counterclockwise(sensor_data, 15);

        }

        else if (receive == 'd') //turn right
        {
            char message_TurningRight[] = "Turning Right\r\n";
            uart_sendStr(message_TurningRight);
            turn_clockwise(sensor_data, 15);

        }

        else if (receive == 'e') //scan around this robot from 0 degree to 180 degrees
        {
            scan();
            uart_sendStr("\nScan done. Proceed with movement \n\n\r");
        }

        else if (receive == 'q') //play music
        {
            music();
            flash();
        }
        else if (receive == 'p')
        {
            LED();
        }

    }
}

