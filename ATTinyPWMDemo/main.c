//Project Name: DEMO_PWM
//Original Author: Matthew Lotts
//Date of Creation: 2015-11-29 (YYYY-MM-DD)
//Revision: 0001
//Revision Author: Matthew Lotts
//Date of Revision: 2015-11-29 (YYYY-MM-DD)
//Development Environment: Atmel Studio 7.0.594, under Window 7 Professional SP1 64-bit
//Dependencies:
//	- tinyADC_REV_0001
//		- tinyADC.h
//		- tinyADC.c

#define F_CPU 1000000			//define the CPU operating frequency in Hz

#include <avr/io.h>				//include io.h
#include "tinyADC.h"			//include tinyADC header file

void initPWM(void);

int main(void)
{
	uint16_t rawADC;
	DDRB = 
		(0 << DDB5) +			//configure PB5 for input
		(0 << DDB4) +			//configure PB4 (ADC2) for input
		(0 << DDB3) +			//configure PB3 (PCINT3) for input
		(0 << DDB2) +			//configure PB2 (SCL) for input
		(1 << DDB1) +			//configure PB1 (OC1A) for output
		(0 << DDB0);			//configure PB0 (SDA) for input
	
	initPWM();					//invoke PWM initialization
    initADC();					//invoke ADC initialization
	
    while (1) 
    {
		rawADC = readADC(2);			//perform one-shot ADC conversion and store value
		OCR1A = (uint8_t)(rawADC/26);	//convert rawADC value into value proportional to TOP value of TC1
    }
}

void initPWM(void)
{
	DDRB |= (1 << DDB1);		//configure PB1 (OC1A) for output
	OCR1A = 39;					//load initial toggle value into OCR1A
	OCR1C = 39;					//load TOP value into OCR1C
	TCCR1 =
		(0 << CTC1) +			//TC1 is reset to $00 in the CPU clock cycle after a compare
		(1 << PWM1A) +			//enable PWM mode base on OCR1A and resets after match with OCR1C
		(1 << COM1A1) +	
		(0 << COM1A0) +			//Clear the OC1A output line
		(0 << CS13) +
		(0 << CS12) +
		(0 << CS11) +
		(1 << CS10);			//Set prescaler division factor to /1
}