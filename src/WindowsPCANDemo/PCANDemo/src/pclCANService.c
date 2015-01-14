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

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdBool.h>
#include <windows.h>
#include "pcanbasic.h"

// Function declaration
int LoadDLL();
int UnloadDLL();
bool GetFunctionAdress(HINSTANCE h_module);

#define pclCAN_MAX_MSG_COUNT 0x20

typedef struct _pclPCANMsg pclPCANMsg;
struct _pclPCANMsg {
	uint8_t id;
	uint8_t new;
	pclCANMsg msg;
	};


pclPCANMsg allMsgs[pclCAN_MAX_MSG_COUNT];

// Function declaration
int LoadDLL();
int UnloadDLL();
bool GetFunctionAdress(HINSTANCE h_module);

//typdef of Functions
typedef TPCANStatus (__stdcall *PCAN_Initialize)(TPCANHandle Channel, TPCANBaudrate Btr0Btr1, TPCANType HwType , DWORD IOPort , WORD Interrupt);
typedef TPCANStatus (__stdcall *PCAN_Uninitialize)( TPCANHandle Channel);
typedef TPCANStatus (__stdcall *PCAN_Reset)(TPCANHandle Channel);
typedef TPCANStatus (__stdcall *PCAN_GetStatus)(TPCANHandle Channel);
typedef TPCANStatus (__stdcall *PCAN_Read)(TPCANHandle Channel, TPCANMsg* MessageBuffer, TPCANTimestamp* TimestampBuffer);
typedef TPCANStatus (__stdcall *PCAN_Write)(TPCANHandle Channel, TPCANMsg* MessageBuffer);
typedef TPCANStatus (__stdcall *PCAN_FilterMessages)(TPCANHandle Channel, DWORD FromID, DWORD ToID, TPCANMode Mode);
typedef TPCANStatus (__stdcall *PCAN_GetValue)(TPCANHandle Channel, TPCANParameter Parameter, void* Buffer, DWORD BufferLength);
typedef TPCANStatus (__stdcall *PCAN_SetValue)(TPCANHandle Channel, TPCANParameter Parameter, void* Buffer, DWORD BufferLength);
typedef TPCANStatus (__stdcall *PCAN_GetErrorText)(TPCANStatus Error, WORD Language, LPSTR Buffer);

//declaration
PCAN_Initialize g_CAN_Initialize;
PCAN_Uninitialize g_CAN_Uninitialize;
PCAN_Reset g_CAN_Reset;
PCAN_GetStatus  g_CAN_GetStatus;
PCAN_Read g_CAN_Read;
PCAN_Write  g_CAN_Write;
PCAN_FilterMessages  g_CAN_FilterMessages;
PCAN_GetValue  g_CAN_GetValue;
PCAN_SetValue  g_CAN_SetValue;
PCAN_GetErrorText  g_CAN_GetErrorText;

// name of DLL
char g_LibFileName[] = "PCANBasic";
//DLL Instance Handle
HINSTANCE g_i_DLL;
// TPCANHandle
TPCANHandle g_hChannel;
TPCANBaudrate g_Baudrate;
// nur für non PNP
TPCANType g_CANType;
DWORD g_IOPort;
WORD g_Int;


void pclCANInitNodes(){
int ret;
TPCANStatus CANStatus;

	g_hChannel = PCAN_USBBUS1;

	ret = LoadDLL();
	if(ret != 0)
	{
		printf("Load DLL: %i", ret);
		exit(-1);
	}

	// Init der PCANBasic Applikation
	CANStatus = g_CAN_Initialize(g_hChannel, PCAN_BAUD_500K , 0, 0, 0);
	if(CANStatus!=PCAN_ERROR_OK)
	{
		printf("Error while Init CAN Interface: 0x%x \n",CANStatus);
		//DLL entladen..
		UnloadDLL();
		printf("press any key to close");
		_getch();
		//und raus
		exit(-1);
	}
}

void pclCANDeiniteNode(){
	g_CAN_Uninitialize(g_hChannel);
	UnloadDLL();
}


void pclCANInitMO(uint32_t channel){}
void pclCANReadAllMsgs(void){
TPCANMsg msg;
TPCANTimestamp time;
TPCANStatus CANStatus;
uint32_t i,j;

	while ((CANStatus=g_CAN_Read(g_hChannel, &msg, &time)) == PCAN_ERROR_OK){
		for (i=0; i<pclCAN_MAX_MSG_COUNT-1; i++){
			if (msg.ID == allMsgs[i].id){
				allMsgs[i].new = PCL_TRUE;
				allMsgs[i].msg.len = msg.LEN;
				allMsgs[i].msg.id = msg.ID;
				for (j=0;j<msg.LEN;j++){
					allMsgs[i].msg.data[j] = msg.DATA[j];
				}
			}
		}
	}
}


void pclCANSendMsg(uint32_t channel, pclCANMsg *msg){
TPCANMsg pmsg;
TPCANStatus CANStatus;
uint8_t i;

	pmsg.ID = msg->id;
	pmsg.LEN=msg->len;
	pmsg.MSGTYPE = PCAN_MESSAGE_STANDARD;
	for (i=0;i<msg->len;i++){
		pmsg.DATA[i]=msg->data[i];
	}
	CANStatus=g_CAN_Write(g_hChannel, &pmsg);
}

void pclCANListenOnMsg(uint32_t channel, pclCANMsg *msg){
uint32_t ifNb = (channel >> 24);
uint8_t MoNb = (uint8_t) (channel & 0x000000FF);
	allMsgs[MoNb].id = msg->id;
	allMsgs[MoNb].new = PCL_FALSE;

}

uint8_t pclCANCheckReception(uint32_t channel, pclCANMsg *msg){
uint32_t ifNb = (channel >> 24);
uint8_t MoNb = (uint8_t) (channel & 0x000000FF);

	if(allMsgs[MoNb].new == PCL_TRUE){
		allMsgs[MoNb].new = PCL_FALSE;
		*msg=allMsgs[MoNb].msg;
		return PCL_TRUE;
	}
	return PCL_FALSE;
}


/***************************************************************************************

 Dynamic Load of the DLL and all function pointer

****************************************************************************************/

//
// Function: Load DLL
// Parameter: none
// ret value: 0 if OK, -1 if DLL not found or can not open, -2 if function pointer not found
//
// load the DLL and get function pointers
//


int LoadDLL()
{
	if(g_i_DLL==NULL)
	{
		g_i_DLL = LoadLibrary("PCANBasic");
		if(g_i_DLL == NULL)
		{
			printf("ERROR: can not load pcanbasic.dll\n");
			return -1;
		}
		else
		{
			printf("DLL Handle: 0x%x\n",g_i_DLL);
			if(GetFunctionAdress( g_i_DLL )==true)
			{
				printf("Load function adress for pcan_basic.dll\n");
			}
			else
			{
				printf("ERROR: can not load Function Adress\n");
				return -2;
			}
		}
	}
	return 0;
}


//
// Function: GetFunctionAdress
// Parameter: instance of DLL
// ret value: true if OK false if pointer not vallid
//
// load the function pointer from the DLL spec. by handle
//



bool GetFunctionAdress(HINSTANCE h_module)
{
  //Lade alle Funktionen
  if(h_module == NULL)
   return false;

  g_CAN_Initialize = (PCAN_Initialize) GetProcAddress(h_module, "CAN_Initialize");
  if(g_CAN_Initialize == NULL)
   return false;

  g_CAN_Uninitialize = (PCAN_Uninitialize) GetProcAddress(h_module, "CAN_Uninitialize");
  if(g_CAN_Uninitialize == NULL)
   return false;

  g_CAN_Reset = (PCAN_Reset) GetProcAddress(h_module, "CAN_Reset");
  if(g_CAN_Reset == NULL)
   return false;

  g_CAN_GetStatus = (PCAN_GetStatus) GetProcAddress(h_module, "CAN_GetStatus");
  if(g_CAN_GetStatus == NULL)
   return false;

  g_CAN_Read = (PCAN_Read) GetProcAddress(h_module, "CAN_Read");
  if(g_CAN_Read == NULL)
   return false;

  g_CAN_Write = (PCAN_Write) GetProcAddress(h_module, "CAN_Write");
  if(g_CAN_Write == NULL)
   return false;

  g_CAN_FilterMessages = (PCAN_FilterMessages) GetProcAddress(h_module, "CAN_FilterMessages");
  if(g_CAN_FilterMessages == NULL)
   return false;

  g_CAN_GetValue = (PCAN_GetValue) GetProcAddress(h_module, "CAN_GetValue");
  if(g_CAN_GetValue == NULL)
   return false;

  g_CAN_SetValue = (PCAN_SetValue) GetProcAddress(h_module, "CAN_SetValue");
  if(g_CAN_SetValue == NULL)
   return false;

  g_CAN_GetErrorText = (PCAN_GetErrorText) GetProcAddress(h_module, "CAN_GetErrorText");
  if(g_CAN_GetErrorText == NULL)
   return false;

  return true;
}
//
// Function: Unload DLL
// Parameter: none
// ret value: 0 if OK
//
// unload the DLL and free all pointers
//

int UnloadDLL()
{
 if(g_i_DLL)
 {
  FreeLibrary(g_i_DLL);
  g_CAN_Initialize = NULL;
  g_CAN_Uninitialize = NULL;
  g_CAN_Reset = NULL;
  g_CAN_GetStatus = NULL;
  g_CAN_Read = NULL;
  g_CAN_Write = NULL;
  g_CAN_FilterMessages = NULL;
  g_CAN_GetValue = NULL;
  g_CAN_SetValue = NULL;
  g_CAN_GetErrorText = NULL;
  return 0;
 }
 return -1;
}
