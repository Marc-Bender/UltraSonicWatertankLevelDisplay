/*
 * powerMgr.c
 *
 * Created: 19.05.2024 17:41:22
 *  Author: marc
 */ 

#include "powerMgr.h"
#include <avr/io.h>
#include <util/atomic.h>

void PWR_disableAllPeripherals(void)
{
	PRR2 |= 0x0f;
	PRR1 |= 0x03;
	PRR0 |= 0xFF;
}

void PWR_disableUsedPeripherals(void)
{
	PRR0 |= (1<<PRADC) | (1<<PRTIM2) | (1<<PRUSART0) ;
}

void PWR_enableUsedPeripherals(void)
{
	PRR0 &= ~((1<<PRADC) | (1<<PRTIM2) | (1<<PRUSART0));
}

void PWR_setSlowestClockSpeed(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		CLKPR = 1<<CLKPCE; // must be written to 1 while all other bits are written to zero
		CLKPR = 1<<CLKPS3; // prescaler to 256 aka maximum possible prescaler... results in 8mhz / 256 --> 31.2 khz
	}
}
void PWR_setNormalClockSpeed(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		CLKPR = 1<<CLKPCE; // must be written to 1 while all other bits are written to zero
		CLKPR = 0; // prescaler to 1 ie. the prescaling is inactive --> mcu runs at full 8mhz
	}
}

