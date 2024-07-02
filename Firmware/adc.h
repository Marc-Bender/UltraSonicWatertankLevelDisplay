/*
 * adc.h
 *
 * Created: 19.05.2024 14:37:03
 *  Author: marc
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void ADC_init(void);
void ADC_disable(void);

void ADC_startConversion(void);
uint16_t ADC_getConversionResult(void);
void ADC_awaitConversionComplete(void);

#endif /* ADC_H_ */