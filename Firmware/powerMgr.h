/*
 * powerMgr.h
 *
 * Created: 19.05.2024 17:40:04
 *  Author: marc
 */ 


#ifndef POWERMGR_H_
#define POWERMGR_H_

void PWR_disableAllPeripherals(void);
void PWR_disableUsedPeripherals(void);
void PWR_enableUsedPeripherals(void);

void PWR_setSlowestClockSpeed(void); // function to clock down the MCU into the lowest frequency possible for the case that the bat low case is reached
void PWR_setNormalClockSpeed(void); // function to set the clock speed back to normal operating speed for the application -> intention is to sleep as low power as possible and to then do the operations as quick as possible

#endif /* POWERMGR_H_ */