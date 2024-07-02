/*
 * eeprom.c
 *
 * Created: 19.05.2024 16:51:38
 *  Author: marc
 */ 

#include "eeprom.h"
#include <avr/io.h>
#include <util/atomic.h>
#include <stdlib.h>
#include <stddef.h>

uint16_t EEPROM_tankfull_cm, EEPROM_tankempty_cm;
uint8_t EEPROM_numOfTanks, EEPROM_areaEntriesUsed, EEPROM_areaEntrySpacing, EEPROM_averagingSampleCnt, EEPROM_sensorType;
uint16_t * EEPROM_areaEntries = NULL;

void EEPROM_writeByte(const uint16_t address, const uint8_t data)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		/* Wait for completion of previous write */
		while(EECR & (1<<EEPE))
		;
		/* Set up address and Data Registers */
		EEAR = address;
		EEDR = data;
		/* Write logical one to EEMPE */
		EECR |= (1<<EEMPE);
		/* Start eeprom write by setting EEPE */
		EECR |= (1<<EEPE);
	}
}

uint8_t EEPROM_readByte(const uint16_t address)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		/* Wait for completion of previous write */
		while(EECR & (1<<EEPE))
		;
		/* Set up address register */
		EEAR = address;
		/* Start eeprom read by writing EERE */
		EECR |= (1<<EERE);
		/* Return data from Data Register */
	}
	return EEDR;
}

uint16_t EEPROM_readUint16(const uint16_t address)
{
	const uint8_t lowByte = EEPROM_readByte(address);
	const uint8_t highByte = EEPROM_readByte(address+1);
	return (
				 ((uint16_t)lowByte << 0)
				|((uint16_t)highByte << 8)
		   );
}

void EEPROM_writeUint16(const uint16_t address, const uint16_t value)
{
	EEPROM_writeByte(address,((uint8_t)(value & 0x00FF)));
	EEPROM_writeByte(address + 1,((uint8_t)(value & 0xFF00)));
}

void EEPROM_init(void)
{
	EEPROM_tankfull_cm = EEPROM_readUint16(ADDR_TANKFULL_CM);
	EEPROM_tankempty_cm = EEPROM_readUint16(ADDR_TANKEMPTY_CM);
	EEPROM_numOfTanks = EEPROM_readByte(ADDR_NUM_OF_TANKS_IN_PARALELL);
	EEPROM_areaEntriesUsed = EEPROM_readByte(ADDR_AREA_ENTRIES_USED);
	EEPROM_areaEntrySpacing = EEPROM_readByte(ADDR_AREA_ENTRY_SPACING_CM);
	EEPROM_averagingSampleCnt = EEPROM_readByte(ADDR_AVERAGING_SAMPLE_CNT);
	EEPROM_sensorType = EEPROM_readByte(ADDR_SENSOR_TYPE);
	
	if(
		   (EEPROM_areaEntriesUsed != 0xFF)
		&& (EEPROM_areaEntriesUsed != 0)
	  )
	{
		EEPROM_areaEntries = (uint16_t*)malloc(sizeof(uint16_t) * EEPROM_areaEntriesUsed);
	}
	else
	{
		// apparently not initialized or initialized wrong... 
		EEPROM_areaEntriesUsed = 0; // since that is used in the rest of the code as a checker value and if not it should not do much harm 
	}
	if(EEPROM_areaEntries != NULL)
	{
		// initialization of array has worked (ie. malloc did not fail)
		for(uint8_t i=0;i<EEPROM_areaEntriesUsed;i++)
		{
			const uint16_t helper = EEPROM_readUint16(ADDR_AREA_ENTRY_0 + (i * sizeof(uint16_t)));
			if(helper != 0xFFFF)
			{
				EEPROM_areaEntries[i] = helper;
			}
			else
			{
				EEPROM_areaEntries[i] = 0;
			}
		}
	}
	else
	{
		// do not retrieve area entries
		#ifdef DEBUG_LITER_ALGO
		EEPROM_areaEntriesUsed = 10;
		EEPROM_areaEntries = (uint16_t*)malloc(sizeof(uint16_t) * EEPROM_areaEntriesUsed);
		EEPROM_areaEntries[0] = 50;
		EEPROM_areaEntries[1] = 45;
		EEPROM_areaEntries[2] = 40;
		EEPROM_areaEntries[3] = 35;
		EEPROM_areaEntries[4] = 40;
		EEPROM_areaEntries[5] = 45;
		EEPROM_areaEntries[6] = 50;
		EEPROM_areaEntries[7] = 50;
		EEPROM_areaEntries[8] = 50;
		EEPROM_areaEntries[9] = 50;
		#endif
	}

	if(EEPROM_tankfull_cm == 0xFFFF)
	{
		// uninitialized --> replace the value with a default value	for the opearation of the application
		EEPROM_tankfull_cm = 10; // 10cm for testing purposes.
	}else {/*initialized no need to change value*/}

	if(EEPROM_tankempty_cm == 0xFFFF)
	{
		// uninitialized --> replace the value with a default value	for the opearation of the application
		EEPROM_tankempty_cm = 100; // 1m for testing purposes.
	}else {/*initialized no need to change value*/}

	if(EEPROM_sensorType == 0xFF)
	{
		// uninitialized --> replace the value with a default value	for the opearation of the application
		EEPROM_sensorType = sensorType_triggerEcho; // assume trigger and echo type if nothing else is given.
	}else {/*initialized no need to change value*/}

	if(EEPROM_numOfTanks == 0xFF)
	{
		// uninitialized --> replace the value with a default value	for the opearation of the application
		EEPROM_numOfTanks = 1; // do the maths with only one tank being considered for testing purposes
	}else {/*initialized no need to change value*/}

	if(EEPROM_averagingSampleCnt == 0xFF)
	{
		// uninitialized --> replace the value with a default value	for the opearation of the application
		EEPROM_averagingSampleCnt = 1; // do not average any samples and instead go with only one measurement
	}else {/*initialized no need to change value*/}

	if(EEPROM_areaEntrySpacing == 0xFF)
	{
		// uninitialized --> replace the value with a default value	for the opearation of the application
		EEPROM_areaEntrySpacing = 10; // if spacing of area entries not initialized assume 10cm spacing.
	}else {/*initialized no need to change value*/}
}

void EEPROM_syncToEEPROM(void)
{
	if (EEPROM_tankfull_cm != EEPROM_readUint16(ADDR_TANKFULL_CM))
	{
		EEPROM_writeUint16(ADDR_TANKFULL_CM,EEPROM_tankfull_cm);
	} else {/*not needed*/}
	if (EEPROM_tankempty_cm != EEPROM_readUint16(ADDR_TANKEMPTY_CM))
	{
		EEPROM_writeUint16(ADDR_TANKEMPTY_CM,EEPROM_tankempty_cm);
	} else {/*not needed*/}
	if (EEPROM_numOfTanks != EEPROM_readByte(ADDR_NUM_OF_TANKS_IN_PARALELL))
	{
		EEPROM_writeByte(ADDR_NUM_OF_TANKS_IN_PARALELL,EEPROM_numOfTanks);
	} else {/*not needed*/}
	if (EEPROM_areaEntriesUsed != EEPROM_readByte(ADDR_AREA_ENTRIES_USED))
	{
		EEPROM_writeByte(ADDR_AREA_ENTRIES_USED,EEPROM_areaEntriesUsed);
	} else {/*not needed*/}
	if (EEPROM_areaEntrySpacing != EEPROM_readByte(ADDR_AREA_ENTRY_SPACING_CM))
	{
		EEPROM_writeByte(ADDR_AREA_ENTRY_SPACING_CM,EEPROM_areaEntrySpacing);
	} else {/*not needed*/}
	if (EEPROM_averagingSampleCnt != EEPROM_readByte(ADDR_AVERAGING_SAMPLE_CNT))
	{
		EEPROM_writeByte(ADDR_AVERAGING_SAMPLE_CNT,EEPROM_averagingSampleCnt);
	} else {/*not needed*/}
	if (EEPROM_sensorType != EEPROM_readByte(ADDR_SENSOR_TYPE))
	{
		EEPROM_writeByte(ADDR_SENSOR_TYPE,EEPROM_sensorType);
	} else {/*not needed*/}
	for(uint8_t i=0;i<EEPROM_areaEntriesUsed;i++)
	{
		if (EEPROM_areaEntries[i] != EEPROM_readUint16(ADDR_AREA_ENTRY_0 + (i * AREA_ENTRY_SIZE)))
		{
			EEPROM_writeUint16(ADDR_AREA_ENTRY_0 + (i*AREA_ENTRY_SIZE),EEPROM_areaEntries[i]);
		} else {/*not needed*/}
	}
}
