/*******************************************************************************
**  DAVE App Name : ADC001       App Version: 1.0.22               
**  This file is generated by DAVE, User modification to this file will be    **
**  overwritten at the next code generation.                                  **
*******************************************************************************/

/*CODE_BLOCK_BEGIN[ADC001_Conf.c]*/

/*******************************************************************************
 Copyright (c) 2013, Infineon Technologies AG                                 **
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
** PLATFORM : Infineon XMC4000/XMC1000 Series                                 **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : DAVE App Developer                                              **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : Sep 27, 2013                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** CM           DAVE App Developer                                            **
*******************************************************************************/
/**
 * @file  ADC001_Conf.c
 * @App Version ADC001 <1.0.22>
 * @brief This file contains App parameter data as per GUI configurations
 *
 * Change History:
 *
 * Date       version       Details
 * 16-Dec-2012   1.0.4     Initial code added for XMC1000
 * 06-Mar-2013   1.0.6     App version changed for XMC1000 and XMC4400/XMC4200
 * 24-Apr-2013   1.0.8     Ported to XMC4500 step AB and 
 *                         Source Result selection Feature added 
 * 11-Jun-2013   1.0.10  1.In channel selection page Group C and Group D check
 *                         boxes made invisible for XMC1200/1300/4200 devices.
 *                       2.In the Header comment section device name changed
 *                         to XMC1000.
 *                       3.Tooltip for the Group channel selection is modified.
 *                       4.New api ADC001_GetFastResult() implemented.
 *                       5.Source Result register selection feature disabled
 *                         due to header file update not available.   
 * 27-Jun-2013   1.0.12    Source Result register selection feature removed to
 *                         simplify the app.   
 * 05-Sep-2013   1.0.14    Added support for the following devices under XMC1200
 *                         and XMC1300 Series XMC1201, XMC1202, XMC1301 
 * 27-Sep-13     1.0.16    Typos in API Documentation & .h comments is corrected. 
 */

#include <DAVE3.h>




ADC001_DynamicDataType ADC001_DynamicHandle =
{
  .State = ADC001_UNINITIALIZED
};

const ADC001_ChannelHandleType ADC001_ChannelAAHandle = {
  .kGroupNo = (uint8_t)0,
  .kChannelNo = (uint8_t)0,
  .kEnable = (uint8_t)1
};




const ADC001_ChannelHandleType* ADC001_ChannelHandlePtr[1] = {
  &ADC001_ChannelAAHandle,

};


const ADC001_HandleType ADC001_Handle0 =
{
  .kChannels = (uint8_t)1,
  .kGroup0ChSelect = (uint8_t)1, 
  .kGroup1ChSelect = (uint8_t)0,  
  .kGroup2ChSelect = (uint8_t)0,
  .kGroup3ChSelect = (uint8_t)0,
  .kGrpAChannels = (uint8_t)1,
  .kGrpBChannels = (uint8_t)0,
  .kGrpCChannels = (uint8_t)0,
  .kGrpDChannels = (uint8_t)0,
  
  .kActiveGroups = {(uint8_t)1, (uint8_t)0 , (uint8_t)0, (uint8_t)0 }, 
  
  .kActiveChannels = {{(uint8_t)1, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0 },
                      {(uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0 } ,
                      {(uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0 },
                      {(uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0 }
                     }, 
  
  .kAsenEnable = (uint8_t)ADC001_ARBITRATION_SLOT_ENABLE,
  .kPriority = (uint8_t)ADC001_PRIORITY0,  
  .kResultReadMode = (uint8_t)ADC001_WAIT_FOR_READ,
  .kStartmode = (uint8_t)ADC001_WAIT_FOR_START,
  .kTriggerMode = (uint8_t)ADC001_NOTRIGGER,
  .kGatingMode = (uint8_t)ADC001_GATING_ENABLED_ALWAYS,
  .kTriggerEn = (uint8_t)0,
  .kAutoScan =   (uint8_t)ADC001_AUTOSCAN_ENABLE,
  .kResultControl = (uint8_t)ADC001_LEFT_ALIGN,
  .kResultEvtEnable= (uint8_t)0,
  .kResourceEvtEnable= (uint8_t)0U,
  .kIpClassSel = (uint8_t)ADC001_GLOBAL_CLASS0,  
  .VADCGlobalPtr= (VADC_GLOBAL_TypeDef*)VADC,  
  .VADCGroup0Ptr= (VADC_G_TypeDef*)(void*) VADC_G0,
  .VADCGroup1Ptr= (VADC_G_TypeDef*)(void*) VADC_G1,
  .VADCGroup2Ptr= (VADC_G_TypeDef*)(void*) VADC_G2,
  .VADCGroup3Ptr= (VADC_G_TypeDef*)(void*) VADC_G3,
  .DynamicHandlePtr= &ADC001_DynamicHandle,
 };
 
/*CODE_BLOCK_END*/

