/*
 * eeprom.h
 *
 * Created: 19.05.2024 16:50:10
 *  Author: marc
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

#define ADDR_TANKFULL_CM (0x0000) // 2bytes
#define ADDR_TANKEMPTY_CM (0x0002) // 2bytes
#define ADDR_NUM_OF_TANKS_IN_PARALELL (0x0004) // 1 byte
#define ADDR_AREA_ENTRIES_USED (0x0005) // 1byte
#define ADDR_AREA_ENTRY_SPACING_CM (0x0006) // 1 byte
#define ADDR_AVERAGING_SAMPLE_CNT (0x0007) // 1 byte
#define ADDR_SENSOR_TYPE (0x0008) // 1 byte
#define ADDR_RESERVED (0x0009) // 1byte; for aligning the area entryies at a 2byte boundary (likely unneccessary)
#define ADDR_AREA_ENTRY_0 (0x000A) // 2 bytes
#define AREA_ENTRY_SIZE (2)

extern uint16_t EEPROM_tankfull_cm, EEPROM_tankempty_cm;
extern uint8_t EEPROM_numOfTanks, EEPROM_areaEntriesUsed, EEPROM_areaEntrySpacing, EEPROM_averagingSampleCnt, EEPROM_sensorType;
extern uint16_t * EEPROM_areaEntries;

typedef enum
{
	sensorType_triggerEcho,
	sensorType_grove,
}   sensorType_t;

void EEPROM_init(void);
void EEPROM_writeByte(const uint16_t address, const uint8_t data);
uint8_t EEPROM_readByte(const uint16_t address);
uint16_t EEPROM_readUint16(const uint16_t address);
void EEPROM_writeUint16(const uint16_t address, const uint16_t value);
void EEPROM_syncToEEPROM(void);

#endif /* EEPROM_H_ */