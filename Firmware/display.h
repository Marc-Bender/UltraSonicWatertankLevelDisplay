/*
 * display.h
 *
 * Created: 02.06.2024 19:34:41
 *  Author: marc
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

typedef enum
{
	DisplayInstruction_clearDisplay,
	DisplayInstruction_returnHome,
	DisplayInstruction_entryModeSet,
	DisplayInstruction_displayOn,
	DisplayInstruction_displayOff,
	DisplayInstruction_cursorOrDisplayShift,
	DisplayInstruction_functionSet,
	DisplayInstruction_setCGRAMAddress,
	DisplayInstruction_setDDRAMAddress,
	DisplayInstruction_readBusyFlagAndAddress,
	DisplayInstruction_writeDataToCGorDDRAM,
	DisplayInstruction_readDataFromCGorDDRAM,
}   DisplayInstruction_t;

void Disp_init(void);
void Disp_deinit(void);

uint8_t Disp_sendInstruction(const DisplayInstruction_t whichInstruction, const uint8_t data);

void Disp_printStringRightAligned(const char * const string, const uint8_t length);
void Disp_printString(const char * const string, const uint8_t length);




#endif /* DISPLAY_H_ */