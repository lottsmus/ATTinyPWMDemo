/*
 * IncFile1.h
 *
 * Created: 11/29/2015 7:41:56 PM
 *  Author: Synth
 */ 


#ifndef TINYADC_H
#define TINYADC_H

#ifndef F_CPU								//check if F_CPU has already been defined
#define F_CPU 1000000						//define CPU frequency in Hz, 1000000 is Atmel AVR default frequency
#endif										//end F_CPU selection

#if (F_CPU > 12800000 && F_CPU <= 25600000)
#define PSC_ADC 0x7							//if F_CPU falls in previous range define ADC prescaler for F_CPU/128
#elif (F_CPU > 6400000 && F_CPU <= 12800000)
#define PSC_ADC 0x6							//if F_CPU falls in previous range, define ADC prescaler for F_CPU/64
#elif (F_CPU > 3200000 && F_CPU <= 6400000)
#define PSC_ADC 0x5							//if F_CPU falls in previous range, define ADC prescaler for F_CPU/32
#elif (F_CPU > 1600000 && F_CPU <= 3200000)
#define PSC_ADC 0x4							//if F_CPU falls in previous range, define ADC prescaler for F_CPU/16
#elif (F_CPU > 800000 && F_CPU <= 1600000)
#define PSC_ADC 0x3							//if F_CPU falls in previous range, define ADC prescaler for F_CPU/8
#elif (F_CPU > 400000 && F_CPU <= 800000)
#define PSC_ADC 0x2							//if F_CPU falls in previous range, define ADC prescaler for F_CPU/4
#elif (F_CPU >= 100000 && F_CPU <= 400000)
#define PSC_ADC 0x1							//if F_CPU falls in previous range, define ADC prescaler for F_CPU/2
#elif (F_CPU < 100000 || F_CPU > 25600000)
#error F_CPU set out of range				//return preprocessor error if CPU frequency not in valid range for proper ADC operation
#endif										//end PSC_ADC selection

#define AREF_VCC			0x0					//VCC used as Voltage Reference, disconnected from PB0 (AREF)
#define AREF_EXT			0x4					//External Voltage Reference at PB0 (AREF) pin, Internal Voltage Reference turned off
#define AREF_IN_11			0xC					//Internal 1.1V Voltage Reference
#define AREF_IN_256			0x9					//Internal 2.56V Voltage Reference without external bypass capacitor, disconnected from PB0 (AREF)
#define AREF_EX_256			0xD					//Internal 2.56V Voltage Reference with external bypass capacitor at PB0 (AREF) pin

#ifndef A_REF									//check if A_REF has already been defined
#define A_REF AREF_VCC							//define A_REF to use VCC as analog reference
#endif											//end A_REF selection

#ifndef ADJ_LEFT								//check if ADJ_LEFT has already been defined
#define ADJ_LEFT 0								//ADC result left adjusted if set to 1, else ADC result is right adjusted if set to 0
#endif											//end ADJ_LEF configuration

extern void initADC(void);
extern uint16_t readADC(uint8_t channelADC);

#endif //end of TINYADC_H