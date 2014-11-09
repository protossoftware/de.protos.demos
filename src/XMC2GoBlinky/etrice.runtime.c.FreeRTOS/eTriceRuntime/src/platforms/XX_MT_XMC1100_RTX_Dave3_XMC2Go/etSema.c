/*******************************************************************************
 * Copyright (c) 2013 protos software gmbh (http://www.protos.de).
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * CONTRIBUTORS:
 * 		Thomas Schuetz, Thomas Jung (initial contribution)
 *
 *******************************************************************************/


#include "osal/etSema.h"
#include "osal/etTimer.h"
#include <Dave3.h>

#include "debugging/etMSCLogger.h"

//extern etTimer * singleThreadedTimer;
#define ET_MAX_NUMBER_SEMA 5

osSemaphoreDef_t sema[ET_MAX_NUMBER_SEMA];
uint32_t rtxSemaData[ET_MAX_NUMBER_SEMA][2];
uint32_t rtxSemaCounter = 0;
osSemaphoreDef(semaphore);

void etSema_construct(etSema* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etSema", "construct")
//			sema[rtxSemaCounter].semaphore = rtxSemaData[rtxSemaCounter];
//			self->osData = osSemaphoreCreate(&(sema[rtxSemaCounter]),0);
			self->osData = osSemaphoreCreate(osSemaphore(semaphore),1);
			rtxSemaCounter++;
			if (rtxSemaCounter >= ET_MAX_NUMBER_SEMA){
				while(1){}
			}


	ET_MSC_LOGGER_SYNC_EXIT
}
void etSema_destruct(etSema* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etSema", "destruct")

	ET_MSC_LOGGER_SYNC_EXIT
}

void etSema_wakeup(etSema* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etSema", "wakeup")
		volatile osStatus status;
		if (osKernelRunning()){
			status = osSemaphoreRelease(self->osData);
			if(status != osOK){
				while(1){}
			}
		}
	ET_MSC_LOGGER_SYNC_EXIT
}

void etSema_waitForWakeup(etSema* self){
	ET_MSC_LOGGER_SYNC_ENTRY("etSema", "waitForWakeup")
		volatile osStatus status;
		if (osKernelRunning()){
			status = osSemaphoreWait (self->osData, osWaitForever);
//			if(status != osOK){
//				while(1){}
//			}
		}

	ET_MSC_LOGGER_SYNC_EXIT
}
