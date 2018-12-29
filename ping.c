/**
 * @file ping.c
 * @brief C file for functions related with ping sensor
* @author Quan Wang, Shuangquan Li
* @date December 2/2018
 *
 */


#include "ping.h"

volatile int clock_edge;
volatile int read_clock_edge;
volatile int rising_time;
volatile int falling_time;

void ping_init()
{
    // clock edge set to 1 for TIMER3B_Handler to read rising_time
    clock_edge = 1;

    // read_clock_edge set to 0 before pulse is sent
    read_clock_edge = 0;

    // enable module 1 timer
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;

    // clear timer enable bit
    TIMER3_CTL_R &= ~(TIMER_CTL_TBEN);

    // set 16-bit timer
    TIMER3_CFG_R |= 0x04;

    // enable direction, count up, capture
    TIMER3_TBMR_R |= 0x10 | 0x04 | 0x03;

    // set to max so prescalar will concatenate the
    // timer value regsiter to make 24-bit register
    TIMER3_TBILR_R = 0xFFFF;

    // enable interrupt
    TIMER3_ICR_R |= TIMER_IMR_CBEIM;

    TIMER3_IMR_R |= TIMER_IMR_CBEIM;

    // enable timer B event mode: both
    TIMER3_CTL_R |= TIMER_CTL_TBEVENT_BOTH;

    TIMER3_CTL_R |= TIMER_CTL_TBEN;

    // enale ping module on port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    // set pin 3 alternate function for peripherals
    GPIO_PORTB_AFSEL_R |= 0x08;

    // set pin 3 to input
    GPIO_PORTB_DIR_R &= 0xF7;

    // enable pin 3
    GPIO_PORTB_DEN_R |= 0x08;

    // interrupt 36 in register 5 is TIMER3B
    NVIC_EN1_R |= 0x10;
    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntMasterEnable();
}

int send_pulse()
{
    // initialize variable to hold pulse width
    int pulse_width = 0;

    // set to 1 after pulse is set
    read_clock_edge = 1;

    // disable T3CCP1 as alternate function
    GPIO_PORTB_PCTL_R &= ~(GPIO_PCTL_PB3_T3CCP1);

    // disable pin 3 alternate function
    GPIO_PORTB_AFSEL_R &= 0xF7;

    // set pin 3 to output
    GPIO_PORTB_DIR_R |= 0x08;

    // pin 3 set to 1
    GPIO_PORTB_DATA_R |= 0x08;

    // wait 5 microseconds
    timer_waitMicros(5);

    // pin 3 set to 0
    GPIO_PORTB_DATA_R &= 0xF7;

    // set pin 3 to input
    GPIO_PORTB_DIR_R &= 0xF7;

    // enable port B pin 3 alternate function
    GPIO_PORTB_AFSEL_R |= 0x08;

    // enable T3CCP1 as alternate function to capture compare from pin 1
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB3_T3CCP1;

    // waits until pulse is received
    while (read_clock_edge);

    // checks overflow
    int overflow = check_overflow(falling_time, rising_time);

    // shifting bits in clock_overflow by 24 to fit into register
    // pulse_width accounts for distance between falling and rising time
    pulse_width = ((unsigned) overflow << 24) + falling_time - rising_time;

    // returns distance of pulse
    return pulse_width;
}

// checking for overflow if new value from TIMER3_TBR_R is less than last value
int check_overflow( falling_time, rising_time)
{

    if (falling_time < rising_time)
    {
        return 1;       // count up for every overflow
    }
    else
    {               // returns 0 otherwise
        return 0;
    }
}

void TIMER3B_Handler(void)
{
    // clear interrupt
    TIMER3_ICR_R |= TIMER_IMR_CBEIM;

    if (clock_edge)
    {                       // if clock edge is 1
        rising_time = TIMER3_TBV_R;     // read time
        clock_edge = 0;                 // set clock edge back to 0
    }

    else
    {                               // if clock edge is 0
        falling_time = TIMER3_TBV_R;    // read time
        read_clock_edge = 0;            // set read back to 0
        clock_edge = 1;                 // set clock edge to 1
    }
}
float ping_getDistance(void)
{
    //return ((send_pulse()/16000000)*17000) ;
    return ((send_pulse() * 0.0010852) - 0.07114);
}
