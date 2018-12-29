/**
* @author Ziming Liu, Jiancheng Zhang
* @date 07/05/2018
*/

#include "ir.h"
#include <stdint.h>
#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include <timer.h>
#include <lcd.h>
#include <math.h>

void main()
{
    int IR_value =  ADC0_readData();
    int IR = ADC0_getDistance(IR_value);
    lcd_printf("value: %d Distance:%d",IR_value,IR);
}
