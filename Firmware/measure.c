/*
 * measure.c
 *
 * Created: 04.06.2024 22:23:55
 *  Author: marc
 */ 

#include "measure.h"
#include "adc.h"

uint16_t Meas_BatVoltage(void)
{
	ADC_startConversion();
	ADC_awaitConversionComplete();
	const uint16_t voltageRaw = ADC_getConversionResult();
	return (uint16_t)(((uint32_t)voltageRaw * (uint32_t)3uLL * (uint32_t)5000uLL) / 1024uLL); // 5k / (10k+5k) --> 1/3
}

