/**
* @file ir.c
* @brief C file in order to use ADC, IR sensor
* @author Quan Wang, Shuangquan Li
* @date December 2/2018
*/

#include "ir.h"


void ADC0_init()
{
    //enable ADC 0 module on port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    //enable clock for ADC
    SYSCTL_RCGCADC_R |= 0x1;

    //enable port B pin 0 to work as alternate functions
    GPIO_PORTB_AFSEL_R |= 0x1;

    //set pin to input - 0
    GPIO_PORTB_DEN_R &= ~(0x1);

    //disable analog isolation for the pin
    GPIO_PORTB_AMSEL_R |= 0x04;

    //initialize the port trigger source as processor (default)
    GPIO_PORTB_ADCCTL_R = 0x00;

    //disable SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //initialize the ADC trigger source as processor (default)
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;

    //set 1st sample to use the AIN10 ADC pin
    ADC0_SSMUX0_R |= 0x000A;

    //enable raw interrupt
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);

    //enable oversampling to average
    ADC0_SAC_R |= ADC_SAC_AVG_64X;

    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
}

int ADC0_readData()
{

    ADC0_PSSI_R = ADC_PSSI_SS0; // initiates SS0 conversion

    while ((ADC0_RIS_R & ADC_RIS_INR0) == 0)    // wait for conversion
    {
    }
    int value = ADC0_SSFIFO0_R; // store result in value

    return value;
}

double ADC0_getDistance(int value)
{

    // values calculated from excel chart
//    int slope = 82259;
//    double exponent = -1.127;

    //value for Robot 9
    int slope = 499295;
    double exponent = -1.384;



    // returns distance
    return (slope * pow(value, exponent));
}
