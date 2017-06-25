/*******************************************************************************
 * Copyright (c) 2011 protos software gmbh (http://www.protos.de).
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * CONTRIBUTORS:
 * 		Thomas Jung (initial contribution)
 *
 *******************************************************************************/

/*******************************************************************************
 * This file implements the project specific part of teh single threaded
 * runtime for a XMC ARM Cortex microcontroller from Infineon.
 *
 * It demonstrates how to adapt to your specific microcontroller. The only thing
 * you need is a periodic interrupt which maintains the etTime. This is the base
 * for all the modeltimers you can use in your eTrice model.
 *
 * This implementation gives you a 1ms accurate time. For most applications this
 * resolution is sufficient and the implementation is much simpler. This version
 * could serve as a starting point for your own project with any other microcontroller.
 *
 ********************************************************************************/

#include "osal/etTime.h"
#include "helpers/etTimeHelpers.h"
#include "stm32f7xx_hal.h"

extern etTime etTargetTime;

const SysTick_Type *ppb=(SysTick_Type *)SysTick_BASE;

void getTimeFromTarget(etTime *t) {
// return the time
// make sure that reading the time is an atomic operation
// => the timer interrupt should not interrupt this operation

//	__disable_irq();
//	*t = etTargetTime;
//	__enable_irq();


etTime t1={0,0};

	/* keep in mind that it is not possible to stop the timer counter itself */
	/* overflow must be checked after reading the counter */
	/* if an overflow occurs do it again */

	/* the count flag is clear on read, read it */
	t1.nSec=ppb->CTRL;
	do {
		/* amount of ticks = reloadRegister - countRegister */
		t1.nSec=(ppb->LOAD-ppb->VAL);
		*t = etTargetTime;
	}while(ppb->CTRL & 0x00010000);

	/* nSec = amount of ticks * 1000 / 120; if CPUCLK == 120Mhz */
	t1.nSec*=1000;
	t1.nSec/=(HAL_RCC_GetHCLKFreq()/1000000);
	/* add t1 to time */
	etTimeHelpers_add(t,&t1);
}

// the timer interrupt
void etTick_Handler(uint32_t nanoSecPerTick) {
// this interrupt will be called every 1ms

	etTargetTime.nSec += (uint32_t)nanoSecPerTick;
	etTimeHelpers_normalize(&etTargetTime);

//	if (etTargetTime.nSec >= 1000000000L) {
//		etTargetTime.nSec -= 1000000000L;
//		etTargetTime.sec++;
//	}
}

// this function will be called during initialization
void etSingleThreadedProjectSpecificUserEntry(void){
}
