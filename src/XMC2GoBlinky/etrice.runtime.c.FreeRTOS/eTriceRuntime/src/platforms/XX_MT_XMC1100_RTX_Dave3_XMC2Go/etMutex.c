/*******************************************************************************
 * Copyright (c) 2013 protos software gmbh (http://www.protos.de).
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * CONTRIBUTORS:
 * 		Thomas Jung (initial contribution)
 *
 *******************************************************************************/

/**
 *
 * etMutex.c MinGW implementation of etMutex
 *
 */

#include "osal/etMutex.h"

#include "debugging/etLogger.h"
#include "debugging/etMSCLogger.h"
#include <Dave3.h>
#define ET_MAX_NUMBER_MUTEX	10

	osMutexDef_t rtxMutex[ET_MAX_NUMBER_MUTEX];
	uint32_t rtxMutexData[ET_MAX_NUMBER_MUTEX][3];
	uint32_t rtxMutexCounter = 0;

void etMutex_construct(etMutex* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etMutex", "construct")
		rtxMutex[rtxMutexCounter].mutex=rtxMutexData[rtxMutexCounter];
		self->osData=osMutexCreate(&(rtxMutex[rtxMutexCounter]));
		rtxMutexCounter++;
		if (rtxMutexCounter >= ET_MAX_NUMBER_MUTEX){
			while(1){}
		}

	ET_MSC_LOGGER_SYNC_EXIT
}
void etMutex_destruct(etMutex* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etMutex", "destruct")

	ET_MSC_LOGGER_SYNC_EXIT
}

void etMutex_enter(etMutex* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etMutex", "enter")
		osStatus status;
		if (osKernelRunning()){
			status=osMutexWait(self->osData,osWaitForever);
			if(status != osOK){
			//	while(1){};
			}
		}
	ET_MSC_LOGGER_SYNC_EXIT
}
void etMutex_leave(etMutex* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etMutex", "leave")
		osStatus status;
		if (osKernelRunning()){
			status = osMutexRelease(self->osData);
			if(status != osOK){
			//	while(1){};
			}
		}
	ET_MSC_LOGGER_SYNC_EXIT
}
