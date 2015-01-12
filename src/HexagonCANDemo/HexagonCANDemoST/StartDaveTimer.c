/*
 * StartDaveTimer.c
 *
 *  Created on: 09.11.2014
 *      Author: TJung
 */

#include "DAVE3.h"

void etTick_Handler(void);

void timerCallback(void * arg){
	etTick_Handler();
}

typedef void (*SYSTM001_TimerCallBackPtr)(void* ParamToCallBack);

void StartDaveTimer(void){
handle_t timer;

	timer = SYSTM001_CreateTimer(1,SYSTM001_PERIODIC,(SYSTM001_TimerCallBackPtr*) timerCallback,(void*) 0);
	SYSTM001_StartTimer(timer);
}
