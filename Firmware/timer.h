/*
 * timer.h
 *
 * Created: 13.06.2024 19:57:46
 *  Author: marc
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>

void Timer_init(void);
void Timer_deinit(void);

extern bool wakeupByTimer;


#endif /* TIMER_H_ */