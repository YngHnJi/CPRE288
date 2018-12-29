/**
* @file servo.c
* @brief C file related with control servo
* @author Quan Wang, Shuangquan Li
* @date December 2/2018
*/

#include "servo.h"


int pulse_period  = 320000;
int mid_width = 22000;

void servo_init(void)
{


     SYSCTL_RCGCTIMER_R |= BIT1; // ENABLE THE SYSTEM CLOCK OF TIMER1
     SYSCTL_RCGCGPIO_R |=BIT1; // ENABLE THE PORTB GPIO
     TIMER1_CTL_R &= ~TIMER_CTL_TBEN;//DISABLE THE TIMER TO CONFIG
     GPIO_PORTB_AFSEL_R |=0b100000;   // GPIO CONFIGIRACTION,PORT B PIN5,PB5(pg.1351)
     GPIO_PORTB_PCTL_R |= 0x00700000;
     GPIO_PORTB_DIR_R |= 0b00100000;
     GPIO_PORTB_DEN_R |= 0b100000;

     TIMER1_TBMR_R &= ~TIMER_TBMR_TBCMR;  //CLEAR THE TBCMR
     TIMER1_CFG_R |= 0x4; //set to 16-bit default timers
     TIMER1_TBMR_R |= 0x2; //TAMR 0x2:PERIODIC TIMER MODE
     TIMER1_TBMR_R |= TIMER_TBMR_TBAMS; // ENABLE THE PWM MODE
     TIMER1_TBILR_R = pulse_period & 0xFFFF; //lower 16 bits of the interval
     TIMER1_TBPR_R = pulse_period >> 16 ;//set the upper 8 bits of the interval

     TIMER1_TBMATCHR_R = (pulse_period - mid_width ) & 0xFFFF;
     TIMER1_TBPMR_R = (pulse_period - mid_width) >> 16;
     TIMER1_CTL_R |= TIMER_CTL_TBEN; //REENABLE THE TIMER
}

void servo_move(int degrees)
{
     unsigned pulse_width;
     pulse_width = (36000 -7500)*degrees /180.0 + 7500;    // 7500->0 degree    36000->180 degree
     pulse_width =
     TIMER1_TBMATCHR_R = (pulse_period - pulse_width ) & 0xFFFF;
     TIMER1_TBPMR_R = (pulse_period - pulse_width) >> 16;
     timer_waitMillis(10);
}
