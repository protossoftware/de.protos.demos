/*******************************************************************************
 *  Copyright (c) 2015 protos software gmbh (http://www.protos.de).
 *
 *  Created on: 07.01.2015
 *      Author: Thomas Jung, Thomas Schuetz (initial contribution)
 *******************************************************************************/


//-------------IO Service--------------------
// channel 0x00xx00yy  => xx = Floor
//                        yy = Id


#include "pclGPIOService.h"

unsigned char getButtonStatus(unsigned char floor, unsigned int id);
void writeToButtonLed(unsigned char floor, unsigned char id, unsigned char onOff);
void writeTo7Seg(unsigned char data);
void writeToDoor(unsigned char floor, unsigned char data);

#define ON		0x01
#define OFF		0x02


uint8_t pclGetIOBit(uint32_t channel){
		return getButtonStatus((uint8_t)(channel>>16),(uint16_t)(channel&0x0000FFFF));
}

void pclSetIOBitAsInput(uint32_t channel){
}

void pclSetIOBitAsOutput(uint32_t channel){
}

void pclSetIOBit(uint32_t channel){
	writeToButtonLed((uint8_t)(channel>>16),(uint8_t)(channel&0x000000FF), ON);
}

void pclResetIOBit(uint32_t channel){
	writeToButtonLed((uint8_t)(channel>>16),(uint8_t)(channel&0x000000FF), OFF);
}

void pclToggleIOBit(uint32_t channel){
}

void pclCtrlIOBit(uint32_t channel, uint32_t ctrl){}

//---------etIORegister8
uint8_t pclGetIORegister8(uint32_t channel){
return 0;
}

void pclSetIORegister8AsInput(uint32_t channel){
}

void pclSetIORegister8AsOutput(uint32_t channel){
}

void pclSetIORegister8(uint32_t channel, uint8_t value){
writeToDoor((uint8_t)(channel>>16),value);
}

void pclCtrlIORegister8(uint32_t channel, uint32_t ctrl){}

