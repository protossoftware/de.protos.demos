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

/* Standard Stellaris includes */
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"


#include "driverlib/interrupt.h"
#include "driverlib/systick.h"

/* implemenatation for eTrice interfaces*/

extern etThread * noThread;
void etThread_execute(etThread* self);

void etUserEntry(void){
	initHw();
}

void etUserPreRun(void){
	/* Start the scheduler. */
	SysTickEnable();
	SysTickIntEnable();
	IntMasterEnable();
	etThread_execute(noThread);
}

void etUserPostRun(void){ }
void etUserExit(void){ }

