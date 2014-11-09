/*******************************************************************************
**  DAVE App Name : DAVESupport       App Version: 1.0.44               
**  This file is generated by DAVE, User modification to this file will be    **
**  overwritten at the next code generation.                                  **
*******************************************************************************/


/*******************************************************************************
 Copyright (c) 2011, Infineon Technologies AG                                 **
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
** PLATFORM : Infineon <Microcontroller name, step>                           **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** MODIFICATION DATE : June 27, 2013                                       **
**                                                                            **
*******************************************************************************/
/**
 * @file  DAVE3.c
 *
 * @brief This file contains implementation of initialization functions calling sequence. 
 *
 * Revision History
 * 27 June 2013 v1.0.33 Initial Version
 */

/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include "../../inc/DAVESupport/DAVE3.h"

/*******************************************************************************
**                 Function declarations                                     **
*******************************************************************************/

//****************************************************************************
// @Function      void DAVE_Init(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the Apps Init Functions.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//****************************************************************************

void DAVE_Init(void)
{
     

//****************************************************************************
// @Initialization of APPs Init Functions
//****************************************************************************
	//  MUX configurations
	DAVE_MUX_PreInit(); 
	//  Initialization of app 'CLK002'		     
	CLK002_Init();
	 
	//  Initialization of app 'UART001'		     
	UART001_Init();
	 
	//  Initialization of app 'CCU4GLOBAL'		     
	CCU4GLOBAL_Init();
	 
	//  Initialization of app 'PWMSP001'		     
	PWMSP001_Init();
	 
	//  Initialization of app 'IO004'		     
	IO004_Init();
	 
	//  Initialization of app 'SYSTM001'		     
	SYSTM001_Init();
	
      
	//  MUX configurations
	DAVE_MUX_Init();	
} //  End of function DAVE_Init



