/*
 * timer.c
 *
 * Created: 13.06.2024 19:57:36
 *  Author: marc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

bool wakeupByTimer = false;

void Timer_init(void)
{
	TIMSK2 |= 1<<TOIE2; // enable overflow interrupt. 
	TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20); // prescaler = 1024 --> approx. 32hz input clock to the timer.
	// 32 clocks per second --> ie 8s max time before overflow
}

void Timer_deinit(void)
{
	TCCR2B = 0; // timer off
	TCNT2 = 0; // timer reset
	TIMSK2 = 0; // timer interrupt disable 
}

ISR(TIMER2_OVF_vect)
{
	// nothing to do here; just a wakeup because the display on time (w/ mcu sleeping) has elapsed
	// set the wakeupByTimer flag to ensure the apllication can distinguish the timer wakeup from the uart wakeup and thus transition in the correct next state
	wakeupByTimer = true;
}
