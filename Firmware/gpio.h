/*
 * gpio.h
 *
 * Created: 19.05.2024 15:45:58
 *  Author: marc
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

void GPIO_init(void);
void GPIO_setVBatMeasEn_to(const bool enable);
void GPIO_setRW_to(const bool enable);
void GPIO_setE_to(const bool enable);
void GPIO_setDispEn_to(const bool enable);
void GPIO_setRS_to(const bool enable);
void GPIO_setSensSupP_to(const bool enable);
void GPIO_setSensSupM_to(const bool enable);
void GPIO_setSensTrig_to(const bool enable);
void GPIO_setSensSig_to(const bool enable);

void GPIO_setDPins_to(const uint8_t value);
void GPIO_DPinReinit(void);
void GPIO_SensSigPinReinit(void);

typedef struct  
{
	volatile uint8_t * port;
	volatile uint8_t * ddr;
	volatile uint8_t * pin;
	volatile uint8_t pinnumber;
	bool isOutput;
}GPIO_t;

typedef enum
{
	VBatMeas,
	RS,
	SupP,
	SupM,
	SensSig,
	SensTrig,
	SensEcho,
	D7,
	D6,
	D5,
	D4,
	D3,
	D2,
	D1,
	D0,
	RX,
	TX,
	Wakeup,
	VBatMeasEn,
	RW,
	EN,
	DispEn,
	PINS_COUNT
}   pins_e;

extern GPIO_t pins[PINS_COUNT];

uint8_t GPIO_getPin(const pins_e whichPin); //< 1 = high 0=low

#endif /* GPIO_H_ */