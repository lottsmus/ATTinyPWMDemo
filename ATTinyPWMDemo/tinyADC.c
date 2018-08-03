/*
 * HelloADC_REV_0001.c
 *
 * Created: 11/29/2015 5:22:26 PM
 * Author : Synth
 */ 

#include <avr/io.h>								//ensure io.h is included
#include "tinyADC.h"							//include header file for tinyADC

void initADC(void)
{
	ADMUX |= 
		(A_REF << REFS1) +						//configure ADC for selected analog voltage reference source
		(ADJ_LEFT << ADLAR);					//configure ADC result for left or right adjust

	ADCSRA |= 
		(PSC_ADC << ADPS0) +					//set prescaler value for ADC
		(1 << ADEN);							//enable ADC
}

uint16_t readADC(uint8_t channelADC)
{
	ADMUX = (ADMUX & 0xF0) | (channelADC & 0x0F);	//select ADC channel with a safety mask if channelADC is too large
	ADCSRA |= (1 << ADSC);							//begin one-shot ADC conversion
	while(ADCSRA & (1<<ADSC));						//wait for ADC conversion to complete
	return ADC;
}