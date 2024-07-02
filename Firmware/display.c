/*
 * display.c
 *
 * Created: 02.06.2024 19:34:53
 *  Author: marc
 */ 

#include "display.h"
#include "gpio.h"
#include <util/delay.h>

typedef struct  
{
	uint8_t :6;
	uint8_t rs:1;
	uint8_t rw:1;
	uint8_t D:8;
} Instructions_t;

static const Instructions_t instructions [] = 
	{
		{.rs=0,.rw=0,.D=1}, // clear display
		{.rs=0,.rw=0,.D=2}, // return home
		{.rs=0,.rw=0,.D=6}, // Entrymode set
		{.rs=0,.rw=0,.D=12}, // Display on
		{.rs=0,.rw=0,.D=8}, // display off
		{.rs=0,.rw=0,.D=(1<<2)|(1<<4)}, // cursor or display shift
		{.rs=0,.rw=0,.D=(1<<5)|(1<<4)|(1<<3)}, // function set
		{.rs=0,.rw=0,.D=(1<<6)}, // set cg ram address
		{.rs=0,.rw=0,.D=(1<<7)}, // set dd ram address
		{.rs=0,.rw=1,.D=0}, // read busy flag and address
		{.rs=1,.rw=0,.D=0}, // write data to CG or DDRAM
		{.rs=1,.rw=1,.D=0}, // read data from CG or DDRAM
	};

uint8_t Disp_sendInstruction(const DisplayInstruction_t whichInstruction, const uint8_t data)
{
	volatile uint8_t returnValue = 0;

	GPIO_setRS_to(instructions[whichInstruction].rs);
	GPIO_setRW_to(instructions[whichInstruction].rw);
	
	const bool isReadInstruction = (instructions[whichInstruction].rw == 1);
	const bool instructionUsesData = (
										  (instructions[whichInstruction].rs == 1)
										||(whichInstruction == DisplayInstruction_setDDRAMAddress)
										||(whichInstruction == DisplayInstruction_setCGRAMAddress)
									 );

	for(uint8_t i=0;i<8;i++)
	{
		pins[D0-i].isOutput = !isReadInstruction; // if no read instruction ie write instruction (rw = 0) the data pins must be set to output for the communication to work
	}
	GPIO_DPinReinit();

	if(instructionUsesData == true)
	{
		GPIO_setDPins_to(instructions[whichInstruction].D | data);
	}
	else
	{
		// does not use data so ommit data and just output the D member to the D pins
		GPIO_setDPins_to(instructions[whichInstruction].D);
	}

	GPIO_setE_to(false);
	GPIO_setE_to(true);

	_delay_us(10); // some high time is required.. 

	if(isReadInstruction == true) // read command
	{
		for(uint8_t i=0;i<8;i++)
		{
			returnValue |= GPIO_getPin(D0-i) << i;
		}
	}
	else
	{
		// on write instruction no need to read a returnvalue since there is none to be feasably communicated any way
	}
	
	GPIO_setE_to(false);
	_delay_ms(5);

	return returnValue; // if read command it will be initialized with the read data, else with 0
}

void Disp_init(void)
{
	GPIO_setDispEn_to(true);
	_delay_ms(50); // display needs some start up time > 40ms after vcc to 2.7 

	Disp_sendInstruction(DisplayInstruction_functionSet, 0);
	Disp_sendInstruction(DisplayInstruction_displayOn, 0);
	Disp_sendInstruction(DisplayInstruction_entryModeSet, 0);
}

void Disp_deinit(void)
{
	static const pins_e dispPins[] = {RS, RW, EN, D0, D1, D2,D3,D4,D5,D6,D7};
	for(uint8_t i=0;i<3+8;i++)
	{
		*(pins[dispPins[i]].ddr) &= ~(1<<pins[dispPins[i]].pinnumber);
	}
	GPIO_setDispEn_to(false);
}

void Disp_printStringRightAligned(const char * const string, const uint8_t length)
{
	for(uint8_t i=0;i<length;i++)
	{
		if(string[i] != '\0')
		{
			continue;
		}
		else
		{
			// found index of null terminator 
			// print spaces for the remaining number of digits in the string to have a shorter string be right aligned
			Disp_sendInstruction(DisplayInstruction_writeDataToCGorDDRAM,' ');
		}
	}

	for(uint8_t i=0;i<length;i++)
	{
		if(string[i] != '\0') // null termination character looks odd
		{
			Disp_sendInstruction(DisplayInstruction_writeDataToCGorDDRAM,string[i]);
		}
		else
		{
			break;
		}
	}
}

void Disp_printString(const char * const string, const uint8_t length)
{
	for(uint8_t i=0;i<length;i++)
	{
		Disp_sendInstruction(DisplayInstruction_writeDataToCGorDDRAM,string[i]);
	}
}
