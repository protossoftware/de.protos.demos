/*******************************************************************************
 * Copyright (c) 2013 protos software gmbh (http://www.protos.de).
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * CONTRIBUTORS:
 * 		Thomas Schuetz (initial contribution), Thomas Jung
 *
 *******************************************************************************/

#include "osal/etTimer.h"
#include "helpers/etTimeHelpers.h"

#include "debugging/etLogger.h"
#include "debugging/etMSCLogger.h"
#include <Dave3.h>
#define ET_MAX_NUMBER_TIMERS 5


osTimerDef_t rtxTimer[ET_MAX_NUMBER_TIMERS];
uint32_t rtxTimerData[ET_MAX_NUMBER_TIMERS][5];
uint32_t rtxTimerCounter=0;
etTimer *timers[ET_MAX_NUMBER_TIMERS];

void etTimer_callback(void const *arg);

void etTimer_construct(etTimer* self, etTime* timerInterval, etTimerFunction timerFunction, void* timerFunctionData){
	ET_MSC_LOGGER_SYNC_ENTRY("etTimer", "construct")
	{
		self->osTimerData = NULL;
		self->timerInterval.sec = timerInterval->sec;
		self->timerInterval.nSec = timerInterval->nSec;
		self->timerFunction = timerFunction;
		self->timerFunctionData = timerFunctionData;
	}

	// store the et self pointer to start all timers from idle
	timers[rtxTimerCounter]=self;
	rtxTimer[rtxTimerCounter].ptimer=etTimer_callback;
	rtxTimer[rtxTimerCounter].timer=rtxTimerData[rtxTimerCounter];

    self->osTimerData=osTimerCreate(&(rtxTimer[rtxTimerCounter]),osTimerPeriodic,(void *)self);
    rtxTimerCounter++;
	if (rtxTimerCounter >= ET_MAX_NUMBER_TIMERS){
		while(1){}
	}


	ET_MSC_LOGGER_SYNC_EXIT
}

void etTimer_start(etTimer* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etTimer", "start")
		osStatus status;
		uint32_t period = (self->timerInterval.sec*1000) + (self->timerInterval.nSec / (1000000));
		if(osKernelRunning()){
			status=osTimerStart(self->osTimerData,period);
			if (status != osOK){
			while(1){}
			}
		}

	ET_MSC_LOGGER_SYNC_EXIT
}

void etTimer_startAllTimers(void){
	int i;
	for (i=0;i<rtxTimerCounter;i++){
		etTimer_start(timers[i]);
	}
}

void etTimer_stop(etTimer* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etTimer", "stop")

	ET_MSC_LOGGER_SYNC_EXIT
}

void etTimer_destruct(etTimer* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etTimer", "destruct")

	ET_MSC_LOGGER_SYNC_EXIT
}


void etTimer_callback(void const *arg){
	{
		etTimer* self = (etTimer *)arg;
		self->timerFunction(self->timerFunctionData);
	}
}
