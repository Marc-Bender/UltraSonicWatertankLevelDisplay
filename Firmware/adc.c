/*
 * adc.c
 *
 * Created: 19.05.2024 14:38:22
 *  Author: marc
 */ 

#include "adc.h"
#include <avr/io.h>

void ADC_init(void)
{
	ADMUX |= 1<<REFS0; //AVCC with external cap. --> mux bits are 0x00 ie. selected channel is ADC0 (vbatmeas)
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1); // internal rc is @ 8mhz and adc max clock is 200khz thus minimum division factor is 8*5 = 40 --> 64 
	DIDR0 |= (1<<ADC0D)|(1<<ADC1D)|(1<<ADC2D)|(1<<ADC3D)|(1<<ADC5D)|(1<<ADC7D); // 
	ADCSRA |= 1<<ADEN; // start ADC and prescaler
	ADCSRA |= 1<<ADSC; //start conversion for initialization of the adc. 
	while((ADCSRA & (1<<ADSC)) != 0); // wait for initialization conversion to complete
}

void ADC_startConversion(void)
{
	ADCSRA |= 1<<ADSC;
}

uint16_t ADC_getConversionResult(void)
{
	const volatile uint8_t dummy0 = ADCL; // because order of reading the result register halfs is important
	const volatile uint8_t dummy1 = ADCH;
	return (
				  ((uint16_t)dummy0 << 0)
				| ((uint16_t)dummy1 << 8)
		   );
}

void ADC_awaitConversionComplete(void)
{
	while((ADCSRA & (1<<ADSC)) != 0); 
}

void ADC_disable(void)
{
	ADCSRA &= ~(1<<ADEN);
}
