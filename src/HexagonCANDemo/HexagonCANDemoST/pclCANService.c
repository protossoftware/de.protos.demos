/*******************************************************************************
 *  Copyright (c) 2015 protos software gmbh (http://www.protos.de).
 *
 *  Created on: 10.01.2015
 *      Author: Thomas Jung, Thomas Schuetz (initial contribution)
 *******************************************************************************/


//-------------IO Service--------------------
// channel 0xXXYYYYYY  => XX = CAN Node Id
//                        YY = Message Object Number


//#include "../../../../de.protos.componentlib.hal.api/inc/pclCANService.h"
#include "pclCANService.h"
#include "Dave3.h"

void pclCANInitNodes(){}
void pclCANInitMO(uint32_t channel){}

void pclCANSendMsg(uint32_t channel, pclCANMsg *msg){
uint32_t ifNb = (channel >> 24);
uint8_t MoNb = (uint8_t) (channel & 0x000000FF);
uint32_t i;
uint32_t Status;
CAN001_MessageHandleType TempMsgHandle;

	TempMsgHandle.DataLength=msg->len;
	TempMsgHandle.IDExten=STANDARDTYPE;
	TempMsgHandle.Identifier=msg->id;
	TempMsgHandle.MsgObjEN = CAN001_ENABLE;
	TempMsgHandle.MsgObjType=TRANSMSGOBJ;
	for (i=0;i<msg->len;i++){
		TempMsgHandle.data[i]=msg->data[i];
	}

	//ToDo: Think about checking the flag before sending instead of behind
	// This would increase CAN performance significantly
	//while(!CAN001_GetMOFlagStatus(&CAN001_Handle0,MoNb,TRANSMIT_PENDING));
	CAN001_ClearMOFlagStatus(&CAN001_Handle0,MoNb,TRANSMIT_PENDING);
	Status = CAN001_ConfigMsgObj(&CAN001_Handle0,&TempMsgHandle, MoNb);
	if(Status != DAVEApp_SUCCESS) while(1);
	Status = CAN001_SendDataFrame(&CAN001_Handle0,MoNb);
	if(Status != DAVEApp_SUCCESS) while(1);
	while(!CAN001_GetMOFlagStatus(&CAN001_Handle0,MoNb,TRANSMIT_PENDING));
}

void pclCANListenOnMsg(uint32_t channel, pclCANMsg *msg){
uint32_t ifNb = (channel >> 24);
uint8_t MoNb = (uint8_t) (channel & 0x000000FF);
uint32_t i;
uint32_t Status;
CAN001_MessageHandleType TempMsgHandle;

		TempMsgHandle.IDExten=STANDARDTYPE;
		TempMsgHandle.IDMask=0x7FF;
		TempMsgHandle.Identifier=msg->id;
		TempMsgHandle.MsgObjEN = CAN001_ENABLE;
		TempMsgHandle.MsgObjType=RECMSGOBJ;

		Status = CAN001_ConfigMsgObj(&CAN001_Handle0,&TempMsgHandle, MoNb);
		if(Status != DAVEApp_SUCCESS) while(1);
}

uint8_t pclCANCheckReception(uint32_t channel, pclCANMsg *msg){
uint32_t ifNb = (channel >> 24);
uint8_t MoNb = (uint8_t) (channel & 0x000000FF);
uint8_t i;
uint32_t Status;
CAN001_MessageHandleType CanRecMsgObj;

 	 if (CAN001_GetMOFlagStatus(&CAN001_Handle0,MoNb,RECEIVE_PENDING)){
 		 // new message available
 		Status=CAN001_ReadMsgObj(&CAN001_Handle0,&CanRecMsgObj,MoNb);
 		if(Status != DAVEApp_SUCCESS) while(1);
 		Status=CAN001_ClearMOFlagStatus(&CAN001_Handle0,MoNb,RECEIVE_PENDING);
 		if(Status != DAVEApp_SUCCESS) while(1);
 		msg->id = CanRecMsgObj.Identifier;
 		msg->len = CanRecMsgObj.DataLength;
 		for (i=0; i<msg->len;i++){
 			msg->data[i]=CanRecMsgObj.data[i];
 		}
 		return PCL_TRUE;
 	 }
 	 return PCL_FALSE;
}


void pclCANUpdateMO(uint32_t channel){}
void pclCANUpdateMOData(uint32_t channel){}

void pclCANReadMsg(uint32_t channel){}


