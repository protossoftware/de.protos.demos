/*******************************************************************************
 *  Copyright (c) 2015 protos software gmbh (http://www.protos.de).
 *
 *  Created on: 07.01.2015
 *      Author: Thomas Jung, Thomas Schuetz (initial contribution)
 *******************************************************************************/


//-------------IO Service--------------------
// channel 0x000000yy  => yy = Id


#include "pclGPIOService.h"
#include "gacommon/common.h"
#include "gaapi/api.h"

#define ON		0x01
#define OFF		0x02

uint32_t inputs;

ga_PV pvi[10];
ga_PV pvo[16];

static char gammaStringsOutputs[16][256]={
	{"Node.Memory.InputStation.Band1Direction"},
	{"Node.Memory.InputStation.Band1Power"},
	{"Node.Memory.PusherStation1.Pusher1Direction"},
	{"Node.Memory.PusherStation1.Pusher1Power"},
	{"Node.Memory.ProductStation1.Band2Direction"},
	{"Node.Memory.ProductStation1.Band2Power"},
	{"Node.Memory.ProductStation1.FraeseDirection"},
	{"Node.Memory.ProductStation1.FraesePower"},
	{"Node.Memory.ProductStation2.Band3Direction"},
	{"Node.Memory.ProductStation2.Band3Power"},
	{"Node.Memory.ProductStation2.BorerDirection"},
	{"Node.Memory.ProductStation2.BorerPower"},
	{"Node.Memory.PusherStation2.Pusher2Direction"},
	{"Node.Memory.PusherStation2.Pusher2Power"},
	{"Node.Memory.EndStation.Band4Direction"},
	{"Node.Memory.EndStation.Band4Power"}
};

static char gammaStringsInputs[9][256]={
	{"Node.Memory.InputStation.InSensor1"},
	{"Node.Memory.InputStation.InSensor2"},
	{"Node.Memory.PusherStation1.SensorP1Front"},
	{"Node.Memory.PusherStation1.SensorP1Back"},
	{"Node.Memory.ProductStation1.SensorFraese"},
	{"Node.Memory.ProductStation2.SensorBohrer"},
	{"Node.Memory.PusherStation2.SensorP2Front"},
	{"Node.Memory.PusherStation2.SensorP2Back"},
	{"Node.Memory.EndStation.EndSensor"}
};
void setOutput(uint32_t channel, uint8_t value);




void setOutput(uint32_t channel, uint8_t value) {
//	ga_PV pv;
	gc_NumericValue val;
	val.uint8 = value;
//	int32_t errorId = ga_pv_open(&pv, gammaStringsOutputs[channel], 0);
	printf("setOutput(%s, %d)\n", gammaStringsOutputs[channel], value);
	ga_pv_putValue(pvo[channel],&val);

	//	ga_pv_putValue(pv, &val);
//	ga_pv_close(&pv);
}

void pclGPIOInitNode(){
int32_t i;
	printf("Connect to Gamma Service !\n");
	int32_t errorId = gc_attachToService( 0, 0 );
	printf("gc_attachToService: ErrorId: %d\n", errorId);

	for (i=0; i<9; i++){
		int32_t errorId = ga_pv_open(&(pvi[i]), gammaStringsInputs[i], ga_PV_PROPERTY_ACC_NON_BLOCKING);
		printf("Open PV[%d]: %s : %d !\n",i,gammaStringsInputs[i],errorId);
	}

	for (i=0; i<16; i++){
		int32_t errorId = ga_pv_open(&(pvo[i]), gammaStringsOutputs[i], 0);
		printf("Open PV[%d]: %s : %d !\n",i,gammaStringsOutputs[i],errorId);
	}

}

void pclReadAllInputs(){

}

uint8_t pclGetIOBit(uint32_t channel){
//	ga_PV pv;
	gc_NumericValue val;

//	int32_t errorId = ga_pv_open(&pv, gammaStringsInputs[channel], ga_PV_PROPERTY_ACC_NON_BLOCKING);
	ga_pv_getValue(pvi[channel], &val);
//	ga_pv_close(&pv);

//	printf("readInput(%s, %d, %d)\n", gammaStringsInputs[channel], val.uint8, errorId);
	if (val.uint8){
		return 1;
	}else{
		return 0;
	}
}

void pclSetIOBitAsInput(uint32_t channel){
}

void pclSetIOBitAsOutput(uint32_t channel){
}

void pclSetIOBit(uint32_t channel){
	setOutput(channel, 1);
}

void pclResetIOBit(uint32_t channel){
	setOutput(channel,0);
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
}

void pclCtrlIORegister8(uint32_t channel, uint32_t ctrl){}

