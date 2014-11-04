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
/* Standard Stellaris includes */
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "osal/etTime.h"
#include "driverlib/interrupt.h"

etTime targetTime;

void etTime_init(void){
	targetTime.nSec=0;
	targetTime.sec=0;
}


void getTimeFromTarget(etTime *t) {
	IntMasterDisable();
	*t = targetTime;
	IntMasterEnable();
}

/* the timer interrupt */
void SysTickIntHandler(void) {
// this interrupt will be called every 1ms
	targetTime.nSec += 1000000L;

	if (targetTime.nSec >= 1000000000L) {
		targetTime.nSec -= 1000000000L;
		targetTime.sec++;
	}
}


