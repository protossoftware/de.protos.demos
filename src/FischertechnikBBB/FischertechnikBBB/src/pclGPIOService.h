/*******************************************************************************
 *  Copyright (c) 2015 protos software gmbh (http://www.protos.de).
 *
 *  Created on: 07.01.2015
 *      Author: Thomas Jung, Thomas Schuetz (initial contribution)
 *******************************************************************************/

#ifndef PCLGPIOSERVICE_H_
#define PCLGPIOSERVICE_H_

#include "stdint.h"

//----------- Prototypes for Init node ----
void pclGPIOInitNode();

//----------- Prototypes for Bit access ----
void pclSetIOBitAsOutput(uint32_t channel);
void pclSetIOBitAsInput(uint32_t channel);
void pclCtrlIOBit(uint32_t channel, uint32_t value);
void pclSetIOBit(uint32_t channel);
void pclResetIOBit(uint32_t channel);
void pclToggleIOBit(uint32_t channel);
void pclReadAllInputs();
uint8_t pclGetIOBit(uint32_t channel);

//----------- Prototypes for Register8 access ----
void pclSetIORegister8AsOutput(uint32_t channel);
void pclSetIORegister8AsInput(uint32_t channel);
void pclCtrlIORegister8(uint32_t channel, uint32_t value);
void pclSetIORegister8(uint32_t channel, uint8_t value);
void pclResetIORegister8(uint32_t channel);
uint8_t pclGetIORegister8(uint32_t channel);

#endif /* PCLGPIOSERVICE_H_ */
