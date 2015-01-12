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



#include "osal/etPlatformLifecycle.h"
#include "osal/etThread.h"
#include "etPlatform.h"
#include "XMC4500.h"

/* implemenatation for eTrice interfaces*/

extern etThread * noThread;
void etThread_execute(etThread* self);

void DAVE_Init(void);
void StartDaveTimer(void);

void etUserEntry(void){
	DAVE_Init();
//	initHw();
}

void etUserPreRun(void){
	__enable_irq();
	StartDaveTimer();
	etThread_execute(noThread);
}

void etUserPostRun(void){ }
void etUserExit(void){ }

