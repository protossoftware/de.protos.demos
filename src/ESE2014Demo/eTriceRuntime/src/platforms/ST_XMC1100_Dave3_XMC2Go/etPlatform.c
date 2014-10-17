/*******************************************************************************
 * Copyright (c) 2012 protos software gmbh (http://www.protos.de).
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * CONTRIBUTORS:
 * 		Thomas Schuetz (initial contribution), Thomas Jung
 *
 *******************************************************************************/

#include "etPlatform.h"
#include "etDatatypes.h"
#include "osal/etTime.h"

#include "XMC1100.h"
//#include "GPIO.h"

// Ticks are generated every 100ms
#define TICKS_PER_SECOND 1000UL


void initHw(void) {
/*
	// Clock configuration
	SCU_GENERAL->PASSWD = 0x000000C0UL; // disable bit protection
	SCU_CLK->CLKCR = 0x3FF00100UL; // MCLK = 32MHz, PCLK = 32MHz
	while((SCU_CLK->CLKCR & SCU_CLK_CLKCR_VDDC2LOW_Msk));
	SCU_GENERAL->PASSWD = 0x000000C3UL; // enable bit protection
	SystemCoreClockUpdate();


	// LEDs configuration

	P1_0_set_mode(OUTPUT_PP_GP);
	P1_1_set_mode(OUTPUT_PP_GP);

	// Switch analog pin to digital
	P2_1_enable_digital();
	P2_2_enable_digital();

	// Turn one LEDs on, the other LED off
	P1_0_reset();
	P1_1_set();

	// System Timer initialization
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);
*/
	etTime_init();
}
/*
void toggleLED1(void){
	P1_1_toggle();
}

void toggleLED0(void){
	P1_0_toggle();

}
*/
