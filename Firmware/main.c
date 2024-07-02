/*
 * Fuellstandsmessung.c
 *
 * Created: 19.05.2024 14:26:16
 * Author : marc
 */ 

#include <avr/io.h>
#include "systemStates.h"
#include "gpio.h"
#include "uart.h"


int main(void)
{
    /* Replace with your application code */
	volatile const uint8_t mcusrold = MCUSR; // store the reset cause for the case that it needs to be evaluated (eg. during debugging)
	MCUSR = 0; // reset the reset cause flags as soon as possible to prevent getting stuck in a mode that can only be left by POR
    while (1) 
    {
		Appl_systemStateMachine_execute();
    }
}

