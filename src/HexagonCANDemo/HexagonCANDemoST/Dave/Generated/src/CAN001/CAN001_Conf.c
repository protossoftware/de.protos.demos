/*******************************************************************************
**  DAVE App Name : CAN001       App Version: 1.0.12               
**  This file is generated by DAVE, User modification to this file will be    **
**  overwritten at the next code generation.                                  **
*******************************************************************************/

/*CODE_BLOCK_BEGIN[CAN001_Conf.c]*/
/*******************************************************************************
 Copyright (c) 2014, Infineon Technologies AG                                 **
 All rights reserved.                                                         **
                                                                              **
 Redistribution and use in source and binary forms, with or without           **
 modification,are permitted provided that the following conditions are met:   **
                                                                              **
 *Redistributions of source code must retain the above copyright notice,      **
 this list of conditions and the following disclaimer.                        **
 *Redistributions in binary form must reproduce the above copyright notice,   **
 this list of conditions and the following disclaimer in the documentation    **
 and/or other materials provided with the distribution.                       **
 *Neither the name of the copyright holders nor the names of its contributors **
 may be used to endorse or promote products derived from this software without** 
 specific prior written permission.                                           **
                                                                              **
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  **
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **
 ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **
 LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **
 SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **
 CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **
 POSSIBILITY OF SUCH DAMAGE.                                                  **
                                                                              **
 To improve the quality of the software, users are encouraged to share        **
 modifications, enhancements or bug fixes with Infineon Technologies AG       **
 dave@infineon.com).                                                          **
                                                                              **
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC4000 Series   			                          **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : App Developer                                                   **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
**                                                                            **
*******************************************************************************/
/**
 * @file CAN001_Conf.c
 *
 * @App Version CAN001 <1.0.12> 
 * @brief  CAN001 App Handle definition based on UI selection.
 *
 */
#include <DAVE3.h>

/* Node2 Handle structure */
const CAN001_HandleType CAN001_Handle0 =
{
	.BaudRate = {0x17, /* Baud rate Prescaler value */
	             0x1, /* Synchronization Jump Width */
	             0x6, /* Time segment 1 */
	             0x1, /* Time segment 2 */
	             0,  /* Divide prescaler by 8 */
	             },
	.CanNodeRegs = CAN_NODE2, /* Node register offset value */
	.NodeID = 2,              /* Current node number */
	.LoopBackModeEn = 0, /* Loop back mode selection*/
	.NodeMONo = 10, /* Total message object allocated to node list */   
	.FirstMOMapping = 0
};

/* Node2 LMO1 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_1 =
{
  	.Identifier = 0x101,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)1
};

/* Node2 LMO2 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_2 =
{
  	.Identifier = 0x102,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)0
};

/* Node2 LMO3 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_3 =
{
  	.Identifier = 0x103,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)1
};

/* Node2 LMO4 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_4 =
{
  	.Identifier = 0x14,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)0
};

/* Node2 LMO5 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_5 =
{
  	.Identifier = 0x13,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)0
};

/* Node2 LMO6 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_6 =
{
  	.Identifier = 0x12,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)0
};

/* Node2 LMO7 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_7 =
{
  	.Identifier = 0x11,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)0
};

/* Node2 LMO8 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_8 =
{
  	.Identifier = 0x14,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)0
};

/* Node2 LMO9 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_9 =
{
  	.Identifier = 0x12,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)0
};

/* Node2 LMO10 handle structure */
CAN001_MessageHandleType CAN001_MessageHandle0_10 =
{
  	.Identifier = 0x11,	
	
	
  	.IDMask = 0x7ff,
		
	.IDEMask = 1,	
	.IDExten = 0, /* Message identifier Type */
	.DataLength = 0,
	.MsgObjEN = CAN001_ENABLE,
	.MsgObjType = (CAN_MsgType)0
};




/*CODE_BLOCK_END*/ 


