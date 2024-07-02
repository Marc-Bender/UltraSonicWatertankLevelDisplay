/*
 * exti.c
 *
 * Created: 13.06.2024 20:07:50
 *  Author: marc
 */ 

#include "exti.h"
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	cli();  // ensure the wakeup only triggers once to prevent the interrupt catching the program flow off guard
}

void Exti_init(void)
{
	//EICRA |= 2<<ISC00; // falling edge on int0 aka wakeup pin for generating a wakeup for triggering a new measurement
	EICRA = 0;
	EIMSK |= 1<<INT0; // enable the interrupt attached to the wakeup pin1
}

void Exti_deinit(void)
{
	EICRA = 0;
	EIMSK = 0;
}
