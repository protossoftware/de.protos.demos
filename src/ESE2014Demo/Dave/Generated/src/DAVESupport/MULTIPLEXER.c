/*******************************************************************************
**  DAVE App Name : DAVESupport       App Version: 1.0.44               
**  This file is generated by DAVE, User modification to this file will be    **
**  overwritten at the next code generation.                                  **
*******************************************************************************/


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
** PLATFORM : Infineon <Microcontroller name, step>                           **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** MODIFICATION DATE : April 23, 2014                                     **
**                                                                            **
*******************************************************************************/
/**
 * @file  MULTIPLEXER.c
 *
 * @brief This file contains implementation of DAVE Support function which 
 * uses to configure multiplexer register values.
 * 24 July 2013 v1.0.34 Initial Version
 * 06 sep 2013 v1.0.36  UART001 : Mux : One instruction for output pins 
 *                      initialisation.
 *                      CAN001 & CAN002 : Avoid twice reset of the INIT bit in 
 *                      Can001_lNodeInit & DAVE_MUX_Init.
 *                      WR_REGHIB Macro definition has been changed.
 * 23 April 2014 v1.0.44 HRPWM MUX configuration supported.                      
 *                      
 */

/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include "../../inc/DAVESupport/DAVE3.h"

/*******************************************************************************
**                 Function declarations                                     **
*******************************************************************************/
/*******************************************************************************
** Syntax           : void DAVE_MUX_Init(void)                                **
**                                                                            **
** Reentrancy       : None                                                    **
**                                                                            **
** Parameters (in)  : void                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This is the Mux configuration                           **
**                                                                            **
*******************************************************************************/
           
void DAVE_MUX_Init(void)
{  
   	 
            	         
                                     
       /*        SCU Macro definitions     */                        
   	 
      
//********* MODULE USIC CONFIGURATIONS *************************	        
        
           
   /* Disable mode before configuring all USIC registers to avoid unintended edges */   
      /* Variable to store the CCR_MODE values for various USIC channels */ 
      uint32_t UsicCcrMode[6] = {0};
           
    UsicCcrMode[0] |= (uint32_t) RD_REG(USIC0_CH0->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos);
    WR_REG(USIC0_CH0->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos,0);  
                        
    UsicCcrMode[1] |= (uint32_t) RD_REG(USIC0_CH1->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos); 
    WR_REG(USIC0_CH1->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos,0);   
                  
    UsicCcrMode[2] |= (uint32_t) RD_REG(USIC1_CH0->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos);   
    WR_REG(USIC1_CH0->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos,0);
                  
      
    						
   /*USIC 0 Channel 0 Mux Related SFR/Bitfields Configurations*/ 						         
 WR_REG(USIC0_CH0->DX0CR, USIC_CH_DX0CR_DSEL_Msk, USIC_CH_DX0CR_DSEL_Pos,1); 
  			  					 				 				 		       				              				  					    					 					   				  					 				 				       				  										 									 					 					  									      					              					  						    					      
                 
   // Data Pointer & Buffer Size for Transmitter Buffer Control  
 WR_REG(USIC0_CH0->TBCTR, USIC_CH_TBCTR_DPTRSIZE_Msk, USIC_CH_TBCTR_DPTRSIZE_Pos,0x04000010);		/*    DPTR = 16,  SIZE = 4 */ 
         
  // Data Pointer & Buffer Size for Receiver Buffer Control  
 WR_REG(USIC0_CH0->RBCTR, USIC_CH_RBCTR_DPTRSIZE_Msk, USIC_CH_RBCTR_DPTRSIZE_Pos,0x04000000);		/*    DPTR = 0,  SIZE = 4 */ 
 						
   /*USIC 0 Channel 1 Mux Related SFR/Bitfields Configurations*/ 						         
 WR_REG(USIC0_CH1->DX0CR, USIC_CH_DX0CR_DSEL_Msk, USIC_CH_DX0CR_DSEL_Pos,1); 
  			  					 				 				 		       				              				  					    					 					   				  					 				 				       				  										 									 					 					  									      					              					  						    					      
                 
   // Data Pointer & Buffer Size for Transmitter Buffer Control  
 WR_REG(USIC0_CH1->TBCTR, USIC_CH_TBCTR_DPTRSIZE_Msk, USIC_CH_TBCTR_DPTRSIZE_Pos,0x01000022);		/*    DPTR = 34,  SIZE = 1 */ 
           
  // Data Pointer & Buffer Size for Receiver Buffer Control  
 WR_REG(USIC0_CH1->RBCTR, USIC_CH_RBCTR_DPTRSIZE_Msk, USIC_CH_RBCTR_DPTRSIZE_Pos,0x01000020);		/*    DPTR = 32,  SIZE = 1 */ 
   						
   /*USIC 1 Channel 0 Mux Related SFR/Bitfields Configurations*/ 						         
 WR_REG(USIC1_CH0->DX0CR, USIC_CH_DX0CR_DSEL_Msk, USIC_CH_DX0CR_DSEL_Pos,3); 
  			                  
 WR_REG(USIC1_CH0->DX1CR, USIC_CH_DX1CR_DSEL_Msk, USIC_CH_DX1CR_DSEL_Pos,1);  
  					 				 				 		       				              				  					    					 					   				  					 				 				       				  										 									 					 					  									      					              					  						    					      
          
   // Data Pointer & Buffer Size for Transmitter Buffer Control  
 WR_REG(USIC1_CH0->TBCTR, USIC_CH_TBCTR_DPTRSIZE_Msk, USIC_CH_TBCTR_DPTRSIZE_Pos,0x02000000);		/*    DPTR = 0,  SIZE = 2 */ 
           
  // Data Pointer & Buffer Size for Receiver Buffer Control  
 WR_REG(USIC1_CH0->RBCTR, USIC_CH_RBCTR_DPTRSIZE_Msk, USIC_CH_RBCTR_DPTRSIZE_Pos,0x01000004);		/*    DPTR = 4,  SIZE = 1 */ 
 						
   /*USIC 1 Channel 1 Mux Related SFR/Bitfields Configurations*/ 									  					 				 				 		       				              				  					    					 					   				  					 				 				       				  										 									 					 					  									      					              					  						    					      
         						
   /*USIC 2 Channel 0 Mux Related SFR/Bitfields Configurations*/ 									  					 				 				 		       				              				  					    					 					   				  					 				 				       				  										 									 					 					  									      					              					  						    					      
       						
   /*USIC 2 Channel 1 Mux Related SFR/Bitfields Configurations*/ 									  					 				 				 		       				              				  					    					 					   				  					 				 				       				  										 									 					 					  									      					              					  						    					      
         
  
  /* Enable mode after configuring all USIC registers to avoid unintended edges */  
            
   WR_REG(USIC0_CH0->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos,UsicCcrMode[0]); 
         
   WR_REG(USIC0_CH1->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos,UsicCcrMode[1]);   
              
   WR_REG(USIC1_CH0->CCR, USIC_CH_CCR_MODE_Msk, USIC_CH_CCR_MODE_Pos,UsicCcrMode[2]);
                        	         
                                              
   	 
            	         
                                          

/*        PORT Macro definitions for IOCR_OE, IOCR_PCR & HWSEL_HW     */                                      
  WR_REG(PORT1->IOCR4, 0xb800U, PORT_IOCR_PC1_PCR_Pos, 0x12U);                /*P1.5 : PORT1_IOCR4_PC5_PCR and PORT1_IOCR4_PC5_OE */					   
					                         
  WR_REG(PORT2->IOCR12, 0xb80000U, PORT_IOCR_PC2_PCR_Pos, 0x12U);                /*P2.14 : PORT2_IOCR12_PC14_PCR and PORT2_IOCR12_PC14_OE */					   
					                         
  WR_REG(PORT3->IOCR0, 0xb8U, PORT_IOCR_PC0_PCR_Pos, 0x12U);                /*P3.0 : PORT3_IOCR0_PC0_PCR and PORT3_IOCR0_PC0_OE */					   
					                         
  WR_REG(PORT3->IOCR8, PORT_IOCR_PC1_OE_Msk, PORT_IOCR_PC1_OE_Pos, PORT_IOCR_OE1);                /*    P3.9 : PORT3_IOCR8_PC9_OE */					   
					                         
  WR_REG(PORT3->IOCR12, 0xb8U, PORT_IOCR_PC0_PCR_Pos, 0x12U);                /*P3.12 : PORT3_IOCR12_PC12_PCR and PORT3_IOCR12_PC12_OE */					   
					                         
  WR_REG(PORT3->IOCR12, 0xb800U, PORT_IOCR_PC1_PCR_Pos, 0x12U);                /*P3.13 : PORT3_IOCR12_PC13_PCR and PORT3_IOCR12_PC13_OE */					   
					                         
  WR_REG(PORT5->IOCR8, 0xb8U, PORT_IOCR_PC0_PCR_Pos, 0x12U);                /*P5.8 : PORT5_IOCR8_PC8_PCR and PORT5_IOCR8_PC8_OE */					   
					                         
  WR_REG(PORT5->IOCR8, PORT_IOCR_PC3_OE_Msk, PORT_IOCR_PC3_OE_Pos, PORT_IOCR_OE1);                /*    P5.11 : PORT5_IOCR8_PC11_OE */					   
					      
   	 
            	         
                                              
   	 
            	         
                                  
                  /*VADC GROUP0 Mux Related SFR/Bitfields Configurations*/  						                                                   						         						                         						                          						         						                                   						          						          						          						                                    						         
  WR_REG(VADC_G0->ALIAS, VADC_G_ALIAS_ALIAS0_Msk, VADC_G_ALIAS_ALIAS0_Pos,1); 
   						          

					 						          						          						          						          						          						          						          						                
                                                                                                                						                            						                          						                            						                             						                          						                             						                           						                          						                            						                    						                         						                         						                       						                       						                          						                          						                                         						                             						                        						                            						                     						                         						                       						                               
                  /*VADC GROUP1 Mux Related SFR/Bitfields Configurations*/  						                                                   						         						                         						                          						         						                                   						          						          						          						                                    						         						          

					 						          						          						          						          						          						          						          						                
                                                                                                                						                            						                          						                            						                             						                          						                             						                           						                          						                            						                    						                         						                         						                       						                       						                          						                          						                                         						                             						                        						                            						                     						                         						                       						                               
                  /*VADC GROUP2 Mux Related SFR/Bitfields Configurations*/  						                                                   						         						                         						                          						         						                                   						          						          						          						                                    						         						          

					 						          						          						          						          						          						          						          						                
                                                                                                                						                            						                          						                            						                             						                          						                             						                           						                          						                            						                    						                         						                         						                       						                       						                          						                          						                                         						                             						                        						                            						                     						                         						                       						                               
                  /*VADC GROUP3 Mux Related SFR/Bitfields Configurations*/  						                                                   						         						                         						                          						         						                                   						          						          						          						                                    						         						          

					 						          						          						          						          						          						          						          						                
                                                                                                                						                            						                          						                            						                             						                          						                             						                           						                          						                            						                    						                         						                         						                       						                       						                          						                          						                                         						                             						                        						                            						                     						                         						                       						                                 
               /*VADC GLOBAL RESULT Mux Related SFR/Bitfields Configurations*/  						          
  WR_REG(VADC->GLOBEVNP, VADC_GLOBEVNP_REV0NP_Msk, VADC_GLOBEVNP_REV0NP_Pos,2); 
                 						                     						                                 
               /*VADC BACKGROUND Source Mux Related SFR/Bitfields Configurations*/  						                  						                						                                                                          
}


/*******************************************************************************
** Syntax           : void DAVE_MUX_PreInit(void)                             **
**                                                                            **
** Reentrancy       : None                                                    **
**                                                                            **
** Parameters (in)  : void                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This is the Mux configuration                           **
**                                                                            **
*******************************************************************************/
 
void DAVE_MUX_PreInit(void)
{        

/*        PORT Macro definitions for IOCR_OE, IOCR_PCR & HWSEL_HW     */                           
}

