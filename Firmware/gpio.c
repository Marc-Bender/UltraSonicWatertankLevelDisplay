/*
 * gpio.c
 *
 * Created: 19.05.2024 15:46:27
 *  Author: marc
 */ 

#include "gpio.h"
#include <avr/io.h>
#include <stdbool.h>

#define ARDUINO (0)

GPIO_t pins[] = 
{
#if ARDUINO == 0
	{&PORTA,&DDRA,&PINA,0, false}, // vbat meas
	{&PORTA,&DDRA,&PINA,1, true}, // rs
	{&PORTA,&DDRA,&PINA,2, true}, // sup+
	{&PORTA,&DDRA,&PINA,3, true}, // sup-
	{&PORTA,&DDRA,&PINA,4, false}, // senssig
	{&PORTA,&DDRA,&PINA,5, true}, // senstrig
	{&PORTA,&DDRA,&PINA,6, false}, // sensecho
              
	{&PORTB,&DDRB,&PINB,0, true}, // d7
	{&PORTB,&DDRB,&PINB,1, true}, // d6
	{&PORTB,&DDRB,&PINB,2, true}, // d5
	{&PORTB,&DDRB,&PINB,3, true}, // d4
	{&PORTB,&DDRB,&PINB,4, true}, // d3
	{&PORTB,&DDRB,&PINB,5, true}, // d2
	{&PORTB,&DDRB,&PINB,6, true}, // d1
	{&PORTB,&DDRB,&PINB,7, true}, // d0
              
	{&PORTD,&DDRD,&PIND,0, false}, // rx
	{&PORTD,&DDRD,&PIND,1, true}, // tx
	{&PORTD,&DDRD,&PIND,2, false}, // wakeup
	{&PORTD,&DDRD,&PIND,3, true}, // vbatmeasen
	{&PORTD,&DDRD,&PIND,4, true}, // rw
	{&PORTD,&DDRD,&PIND,5, true}, // en
	{&PORTD,&DDRD,&PIND,6, true}, // dispen
#else // ARDUINO == 1
	{&PORTF,&DDRF,&PINF,0, false}, // vbat meas
	{&PORTL,&DDRL,&PINL,3, true}, // rs
	{&PORTF,&DDRF,&PINF,1, true}, // sup+
	{&PORTF,&DDRF,&PINF,2, true}, // sup-
	{&PORTF,&DDRF,&PINF,3, false}, // senssig
	{&PORTF,&DDRF,&PINF,4, true}, // senstrig
	{&PORTF,&DDRF,&PINF,5, false}, // sensecho
              
	{&PORTA,&DDRA,&PINA,4, true}, // d7
	{&PORTA,&DDRA,&PINA,6, true}, // d6
	{&PORTC,&DDRC,&PINC,7, true}, // d5
	{&PORTC,&DDRC,&PINC,5, true}, // d4
	{&PORTC,&DDRC,&PINC,3, true}, // d3
	{&PORTC,&DDRC,&PINC,1, true}, // d2
	{&PORTD,&DDRD,&PIND,7, true}, // d1
	{&PORTG,&DDRG,&PING,1, true}, // d0
              
	{&PORTE,&DDRE,&PINE,0, false}, // rx
	{&PORTE,&DDRE,&PINE,1, true}, // tx
	{&PORTD,&DDRD,&PIND,0, false}, // wakeup
	{&PORTK,&DDRK,&PINK,0, true}, // vbatmeasen
	{&PORTL,&DDRL,&PINL,5, true}, // rw
	{&PORTL,&DDRL,&PINL,7, true}, // en
	{&PORTF,&DDRF,&PINF,6, true}, // dispen
#endif
};

void GPIO_SensSigPinReinit(void)
{
	*(pins[SensSig].ddr) &= ~(1<<(pins[SensSig].pinnumber)); // make input before possibly changing to output

	if(pins[SensSig].isOutput == true)
	{
		*(pins[SensSig].ddr) |= 1<<(pins[SensSig].pinnumber);
	}
	else
	{
		// input already set by preclear
	}
}

void GPIO_DPinReinit(void)
{
	for(uint8_t i=D7;i<=D0;i++)
	{
		*(pins[i].ddr) &= ~(1<<(pins[i].pinnumber)); // make input before possibly changing to output
		if(pins[i].isOutput == true)
		{
			*(pins[i].ddr) |= 1<<(pins[i].pinnumber);
		}
		else
		{
			// input already set by preclear
		}
	}
}

void GPIO_init(void)
{
	for(uint8_t i=0;i<PINS_COUNT;i++)
	{
		*(pins[i].ddr) &= ~(1<<(pins[i].pinnumber)); // make input before possibly changing to output
		if(pins[i].isOutput == true)
		{
			*(pins[i].ddr) |= 1<<(pins[i].pinnumber);
		}
		else
		{
			// input already set by preclear
		}
	}
	#if ARDUINO == 1
		DDRB |= 1<<1; // supply display logic -
		DDRB |= 1<<3; // supply display logic +
		DDRA |= 1<<2; // supply backlight +
		DDRA |= 1<<0; // supply backlight -
		PORTB &= ~(1<<1); // supply display logic - == low
		PORTB |= 1<<3; // supply display logic + == high
		PORTA |= 1<<2; // supply backlight + == high
		PORTA &= ~(1<<0);// supply backlight - == low
	#endif
}

static void GPIO_setPinTo(const pins_e whichPin, const bool enable)
{
	const uint8_t mask = 1<<pins[whichPin].pinnumber;
	*(pins[whichPin].port) &= ~mask;
	if(enable == true)
	{
		*(pins[whichPin].port) |= mask;
	}
	else
	{
		// not to be set high thus keep at low as done by nand before if else
	}
}

void GPIO_setVBatMeasEn_to(const bool enable)
{
	GPIO_setPinTo(VBatMeasEn,enable);
}

void GPIO_setRW_to(const bool enable)
{
	GPIO_setPinTo(RW,enable);
}

void GPIO_setE_to(const bool enable)
{
	GPIO_setPinTo(EN,enable);
}

void GPIO_setDispEn_to(const bool enable)
{
#if 0
	if(
		   (enable) 
		 &&((*(pins[DispEn].ddr) & (1<<(pins[DispEn].pinnumber))) != 0) // shall be high and is output (ie. output low) --> make input pullup ie high
	  )
	{
		*(pins[DispEn].ddr) &= ~(1<<(pins[DispEn].pinnumber));
		*(pins[DispEn].port) |= 1<<(pins[DispEn].pinnumber);
	}
	else if(enable)
	{
		// should be high and is input pullup .. nothing to do
	}
	else if(
				  (!enable) // should be low but is input pullup ie high
				&&((*(pins[DispEn].ddr) & (1<<(pins[DispEn].pinnumber))) == 0)
	       )
	{
		*(pins[DispEn].ddr) |= (1<<(pins[DispEn].pinnumber));
		*(pins[DispEn].port) &= ~(1<<(pins[DispEn].pinnumber));
	}
	else
	{
		// should be low and is low... nothing to do
	}
#else
	GPIO_setPinTo(DispEn,enable);
#endif
}

void GPIO_setRS_to(const bool enable)
{
	GPIO_setPinTo(RS,enable);
}

void GPIO_setSensSupP_to(const bool enable)
{
	GPIO_setPinTo(SupP,enable);
}

void GPIO_setSensSupM_to(const bool enable)
{
	GPIO_setPinTo(SupM,enable);
}

void GPIO_setSensTrig_to(const bool enable)
{
	GPIO_setPinTo(SensTrig,enable);
}

void GPIO_setSensSig_to(const bool enable)
{
	GPIO_setPinTo(SensSig,enable);
}

void GPIO_setDPins_to(const uint8_t value)
{
	for(uint8_t i=0;i<8;i++)
	{
		if((value & (1<<i)) != 0)
		{
			GPIO_setPinTo(D0-i,true);
		}
		else
		{
			GPIO_setPinTo(D0-i,false);
		}
	}
}

uint8_t GPIO_getPin(const pins_e whichPin) //< 1 = high 0=low
{
	return (((*pins[whichPin].pin)&(1<<pins[whichPin].pinnumber))!=0)?1:0;
}

