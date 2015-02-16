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


//#include "../../../../de.protos.componentlib.hal.api/inc/pclCANService.h"
#include "pclCANService.h"
#include "Dave3.h"

#define pclCAN_MAX_MO_COUNT 15

typedef struct _pclCANMO pclCANMO;
struct _pclCANMO {
	uint8_t id;
	uint8_t changed;
	pclCANMsg msg;
	};


uint8_t pclCANCheckOtherMOsRecall(uint8_t MoNb, pclCANMsg *msg);
void pclCANCheckOtherMOsSave(uint8_t MoNb, pclCANMsg *msg);

pclCANMO allRxMOs[pclCAN_MAX_MO_COUNT];

void pclCANInitNodes(){}

#define RESET_PNDING_MASK	0x00020000
#define CAN_MO_BASE_ADDR	0x4801501C

uint32_t getCANInterfaceIdFromChannel(uint32_t channel){
	return ((channel >> 16) & 0x000000FF);
}

uint32_t getCANMOIdFromChannel(uint32_t channel){
	return ((channel & 0x0000FFFF)+1);
}

uint32_t getNodeIdFromChannel(uint32_t channel){
	return ((channel >> 24) & 0x000000FF);
}


void pclCANInitMO(uint32_t channel){
uint8_t MoNb = (uint8_t) getCANMOIdFromChannel(channel);
uint32_t i;
	allRxMOs[MoNb].changed=0;
	allRxMOs[MoNb].msg.id=0;
	allRxMOs[MoNb].msg.len=0;
	for (i=0;i<8;i++){
		allRxMOs[MoNb].msg.data[i]=0;
	}
}
/*
uint32_t ifNb = (channel >> 24);
uint8_t MoNb = (uint8_t) (channel & 0x000000FF);
uint32_t *p;

	p=(uint32_t *) ((uint32_t) (CAN_MO_BASE_ADDR + ((MoNb-1)*0x20)));
//	*p = RESET_PNDING_MASK;
}*/
void pclCANReadAllMsgs(){}

void pclCANSendMsg(uint32_t channel, pclCANMsg *msg){
uint32_t ifNb = getCANInterfaceIdFromChannel(channel);
uint8_t MoNb = (uint8_t) getCANMOIdFromChannel(channel);
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
//	while(!CAN001_GetMOFlagStatus(&CAN001_Handle0,MoNb,TRANSMIT_PENDING));
	CAN001_ClearMOFlagStatus(&CAN001_Handle0,MoNb,TRANSMIT_PENDING);
	Status = CAN001_ConfigMsgObj(&CAN001_Handle0,&TempMsgHandle, MoNb);
	if(Status != DAVEApp_SUCCESS) while(1);
	Status = CAN001_SendDataFrame(&CAN001_Handle0,MoNb);
	if(Status != DAVEApp_SUCCESS) while(1);
	while(!CAN001_GetMOFlagStatus(&CAN001_Handle0,MoNb,TRANSMIT_PENDING));
}

void pclCANListenOnMsg(uint32_t channel, pclCANMsg *msg){
uint32_t ifNb = getCANInterfaceIdFromChannel(channel);
uint8_t MoNb = (uint8_t) getCANMOIdFromChannel(channel);
uint32_t i;
uint32_t Status;
CAN001_MessageHandleType TempMsgHandle;

/*---------------------------------------------*/
		allRxMOs[MoNb].changed=0;
		allRxMOs[MoNb].msg=*msg;
/*---------------------------------------------*/

		TempMsgHandle.IDExten=STANDARDTYPE;
		TempMsgHandle.IDMask=0x7FF;
		TempMsgHandle.Identifier=msg->id;
		TempMsgHandle.MsgObjEN = CAN001_ENABLE;
		TempMsgHandle.MsgObjType=RECMSGOBJ;
		TempMsgHandle.DataLength=8;

//		Status = CAN001_ConfigMsgObj(&CAN001_Handle0,&TempMsgHandle, MoNb);
//		if(Status != DAVEApp_SUCCESS) while(1);
}

void pclCANCheckOtherMOsSave(uint8_t MoNb, pclCANMsg *msg){
uint32_t i;
	for(i=0;i<pclCAN_MAX_MO_COUNT;i++){
		if (allRxMOs[i].msg.id == msg->id){
			allRxMOs[i].msg=*msg;
			allRxMOs[i].changed=1;
		}
	}
}

uint8_t pclCANCheckOtherMOsRecall(uint8_t MoNb, pclCANMsg *msg){

	if(allRxMOs[MoNb].changed == 1){
		*msg=allRxMOs[MoNb].msg;
		allRxMOs[MoNb].changed=0;
		return PCL_TRUE;
	}
	return PCL_FALSE;
}

uint8_t pclCANCheckReception(uint32_t channel, pclCANMsg *msg){
uint32_t ifNb = getCANInterfaceIdFromChannel(channel);
uint8_t MoNb = (uint8_t) getCANMOIdFromChannel(channel);
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
 		pclCANCheckOtherMOsSave(MoNb,msg);
 		allRxMOs[MoNb].changed=0;
 		return PCL_TRUE;
 	 }
 	 return pclCANCheckOtherMOsRecall(MoNb,msg);
 	 //return PCL_FALSE;
}
