/*******************************************************************************
 *  Copyright (c) 2015 protos software gmbh (http://www.protos.de).
 *
 *  Created on: 10.01.2015
 *      Author: Thomas Jung, Thomas Schuetz (initial contribution)
 *******************************************************************************/
//-------------CAN Service--------------------
// channel 0xXXYYZZZZ  => XX = Node Id
//                        YY = CAN Interface ID
//						  ZZ = Message Object Number

#ifndef PCLCANSERVICE_H_
#define PCLCANSERVICE_H_

#include "stdint.h"
// MO => Message Object

#define PCL_TRUE	1
#define PCL_FALSE 	0

typedef struct _pclCANMsg pclCANMsg;
struct _pclCANMsg {
	uint32_t id;
	uint8_t len;
	uint8_t data[8];
	};

void pclCANInitNodes();
void pclCANSendMsg(uint32_t channel, pclCANMsg *msg);
void pclCANInitMO(uint32_t channel);
void pclCANListenOnMsg(uint32_t channel, pclCANMsg *msg);
uint8_t pclCANCheckReception(uint32_t channel, pclCANMsg *msg);
void pclCANReadAllMsgs();


#endif /* PCLCANSERVICE_H_ */
