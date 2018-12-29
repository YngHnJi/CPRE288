/*
 * line_dect_cali.c
 *
 *  Created on: Dec 4, 2018
 *      Author: yhji325
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



int main(){


    lcd_init();

    oi_t *sensor = oi_alloc();
    oi_init(sensor);

    while(1){
        oi_update(sensor);
        uint16_t FL_data = sensor->cliffFrontLeftSignal;
        uint16_t FR_data = sensor->cliffFrontRightSignal;
        uint16_t L_data = sensor->cliffLeftSignal;
        uint16_t R_data = sensor->cliffRightSignal;

        timer_waitMillis(15);
        lcd_printf("FL data: %d, FR_data: %d\nL data: %d, R_data: %d\n", FL_data, FR_data, L_data, R_data);
        check_dest(sensor);
    }
}
