/*
 * systemStates.h
 *
 * Created: 19.05.2024 14:28:37
 *  Author: marc
 */ 


#ifndef SYSTEMSTATES_H_
#define SYSTEMSTATES_H_

typedef enum 
{
	systemState_boot,
	systemState_measure,
	systemState_sleepDisplayOn,
	systemState_sleepDisplayOff,
	systemState_batLowFault,
	systemState_parametrization,
}	systemState_t;

void Appl_systemStateMachine_execute(void);


#endif /* SYSTEMSTATES_H_ */