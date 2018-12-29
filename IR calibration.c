#include "lcd.h"
#include "Timer.h"
# include "math.h"
void initADC(void){
    //enable ADC 0 module on port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    //enable clock for ADC
    SYSCTL_RCGCADC_R |= 0x1;
    //enable port B pin 4 to work as alternate functions
    GPIO_PORTB_AFSEL_R |= 0b10000;
	//set PB4 to input
	//GPIO_PORTB_DIR_R &= 0b011101111;
    //disable PB4 digital function
    GPIO_PORTB_DEN_R &= 0b011101111;
    //disable analog isolation for the pin
    GPIO_PORTB_AMSEL_R |= 0b00001000;
    //initialize the port trigger source as processor (default)
    GPIO_PORTB_ADCCTL_R = 0x00;

    //disable SS0 sample sequencer to configure it， ACT active sample sequencer
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
    //initialize the ADC trigger source as processor (default)
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;
    //set (1st sample) to use the (AIN10) ADC pin 
    ADC0_SSMUX0_R |= 0x000A;//AIN10 adc uses Port B (PB4)
    //enable raw interrupt status
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);
    //enable oversampling to average
    ADC0_SAC_R |= ADC_SAC_AVG_64X;
    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
//
//    //initiate SS1 conversion
//    ADC0_PSSI_R=ADC_PSSI_SS1;
//    //wait for ADC conversion to be complete
//    while((ADC0_RIS_R & ADC_RIS_INR1) == 0){
//    //wait
//    }
//    //grab result
//    int value = ADC0_SSFIFO1_R;
//    //clear interrupt flags
//    ADC0_ISC_R |= ADC_ISC_IN0;
//    //enable ADC0SS0 interrupt
//    ADC0_IM_R |= ADC_IM_MASK0;
//    //enable interrupt for IRQ 14 set bit 14
//    NVIC_EN0_R |= 0x00004000;
//    //tell cpu to use ISR handler for ADC0SS0
//    IntRegister(INT_ADC0SS0, ADC0SS0_Handler);
//    //enable global interrupts
//    IntMasterEnable();
//


}

unsigned ADC_read(char channel){
    //initiate SS0 conversion(ADC processor sample sequence initiate)
    ADC0_PSSI_R=ADC_PSSI_SS0;//begin sampling on sample sequencer 0
    //wait for ADC conversion to be complete
    while((ADC0_RIS_R & ADC_RIS_INR0) == 0){
    //wait
    }
    //clear interrupt
    ADC0_ISC_R=ADC_ISC_IN0;
    //disable ADC0SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
    //set 1st sample to use the channel ADC pin
    ADC0_SSMUX0_R |= channel;
    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
    //initiate SS0 conversion
    ADC0_PSSI_R=ADC_PSSI_SS0;
    //wait for ADC conversion to be complete
    while((ADC0_RIS_R & ADC_RIS_INR0) == 0){}
    //clear interrupt
    ADC0_ISC_R=ADC_ISC_IN0;
    return ADC0_SSFIFO0_R;
}

int main(){

    initADC();
    double distance = 0;
    int dist = 0;
    lcd_init();
    int read = 0;
    int i = 0;
    int value = 0;
    int swag = 0;

    while (1)
    {


        value = ADC_read('10');
        distance = 499295 * pow(value, -1.384);
        lcd_printf("%d , %lf cm", value, distance);
        timer_waitMillis(100);
    }
    return 0;
}
