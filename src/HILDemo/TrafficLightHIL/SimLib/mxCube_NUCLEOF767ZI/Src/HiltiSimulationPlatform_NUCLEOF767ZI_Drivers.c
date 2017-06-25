/*
 * HiltiSimulationPlatform_NUCLEOF767ZI_Drivers.c
 *
 *  Created on: 06.12.2016
 *      Author: JUNGTHOM
 */

#include "stm32f7xx_hal.h"
#include "mxconstants.h"
#include "HiltiSimulationPlatform_NUCLEOF767ZI_Drivers.h"
#include "base\etMemory_FixedSize.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
//extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart8;
extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi4;
extern DAC_HandleTypeDef hdac;

extern I2C_HandleTypeDef hi2c4;
extern DMA_HandleTypeDef hdma_i2c4_rx;
extern DMA_HandleTypeDef hdma_i2c4_tx;
extern ADC_HandleTypeDef hadc1;


#define DUTY_CAPTURE_ARRAY_SIZE			0x04

#define DEBUG_PRINT_BUFFER_SIZE				300
#define DEBUG_AMOUNT_OF_PRINT_BUFFERS   	20
#define ETUNIT_AMOUNT_OF_PRINT_BUFFERS   	20

#define pi	3.14159265359


//********************Patterns for HALL generation***************************************************
static uint8_t halPatternLinks[]={0x05, 0x01, 0x03, 0x02, 0x06, 0x04};
static uint8_t halPatternRechts[]={0x05, 0x04, 0x06, 0x02, 0x03, 0x01};
//***************************************************************************************************
static uint32_t ccr1Values[DUTY_CAPTURE_ARRAY_SIZE];
static uint16_t ccr1Index=0;
//***************************************************************************************************
static uint8_t debugUartIdle = 1;
static uint8_t etUnitUartIdle = 1;

//*******************sin wave and net clock**********************************************************
static const int16_t DAC_sinWave[200]={
		0,31,63,94,125,156,187,218,249,279,
		309,339,368,397,426,454,482,509,536,562,
		588,613,637,661,685,707,729,750,771,790,
		809,827,844,861,876,891,905,918,930,941,
		951,960,969,976,982,988,992,996,998,1000,
		1000,1000,998,996,992,988,982,976,969,960,
		951,941,930,918,905,891,876,861,844,827,
		809,790,771,750,729,707,685,661,637,613,
		588,562,536,509,482,454,426,397,368,339,
		309,279,249,218,187,156,125,94,63,31,
		0,-31,-63,-94,-125,-156,-187,-218,-249,-279,
		-309,-339,-368,-397,-426,-454,-482,-509,-536,-562,
		-588,-613,-637,-661,-685,-707,-729,-750,-771,-790,
		-809,-827,-844,-861,-876,-891,-905,-918,-930,-941,
		-951,-960,-969,-976,-982,-988,-992,-996,-998,-1000,
		-1000,-1000,-998,-996,-992,-988,-982,-976,-969,-960,
		-951,-941,-930,-918,-905,-891,-876,-861,-844,-827,
		-809,-790,-771,-750,-729,-707,-685,-661,-637,-613,
		-588,-562,-536,-509,-482,-454,-426,-397,-368,-339,
		-309,-279,-249,-218,-187,-156,-125,-94,-63,-31
};
static uint16_t DAC_shiftedSin[2][200];
static uint8_t DAC_sinWaveGenEnable[2] = {0,0};
static uint16_t DAC_sinWaveGenOffset[2] = {1500, 1500};
static uint16_t DAC_sinWaveGenAmplitude[2] = {1000,1000};
static uint16_t DAC_sinWaveGenStartIndex[2] = {30,0};
static uint16_t DAC_sinWaveGenIndexOffset[2] = {20,0};

//***************************************************************************************************
typedef struct printQueueObj{
	etQueueObj	queueElem;
	uint16_t	len;
	uint8_t 	charBuffer[DEBUG_PRINT_BUFFER_SIZE];
}printQueueObj;

printQueueObj printBuffers[DEBUG_AMOUNT_OF_PRINT_BUFFERS];

etQueue printFreeQueue;
etQueue printUsedQueue;

printQueueObj etUnitPrintBuffers[DEBUG_AMOUNT_OF_PRINT_BUFFERS];

etQueue etUnitPrintFreeQueue;
etQueue etUnitPrintUsedQueue;


//***************************************************************************************************

static void SPI4_init(void);
static void SPI4_write(uint32_t channel, uint32_t data);
static void HALL_setHallPattern(uint8_t pattern);

//*******************************************************************************************
// Common Callback and Service functions. Basicly required from STM HAL Layer
//
// TIM3:
// will be used to generate the HAL Signals
// tim3ReloadValue determins the periode. For every change an interrupt will generated.
// The halPattern array contains valid patterns.
// TIM4:
// is used to measure the PWM. Set WM to 100% if periode elapsed
// TIM6:
// is used to generate Sinus and Netclock for mains tools
//*******************************************************************************************
static uint32_t tim3ReloadValue = 20000;
static HALL_Direction_t hallDirection = hall_right;
static volatile uint32_t NET_triacImpulseCounter = 0;
static volatile uint32_t NET_triacTimeCounter = 0;
static volatile uint32_t NET_triacTimeCount=0;
static volatile uint32_t NET_triacImpulseCount=0;
static uint8_t NET_triacTimeState=0;
static uint8_t NET_netClockState=0;
static uint8_t HALLGEN_hallIndex=0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
static uint16_t sinWaveIndex = 0;
uint16_t idx;

	if (htim->Instance == TIM3){

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);

		htim3.Instance->ARR = tim3ReloadValue;
		HALLGEN_hallIndex++;
		if (hallDirection == hall_right){
			if (HALLGEN_hallIndex >= sizeof(halPatternRechts)) HALLGEN_hallIndex = 0;
			HALL_setHallPattern(halPatternRechts[HALLGEN_hallIndex]);
		}else{
			if (HALLGEN_hallIndex >= sizeof(halPatternLinks)) HALLGEN_hallIndex = 0;
			HALL_setHallPattern(halPatternLinks[HALLGEN_hallIndex]);
		}

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
	}

	if (htim->Instance == TIM4){
		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12) == 0x01){
			ccr1Values[ccr1Index++] = 10800;
		}else{
			ccr1Values[ccr1Index++] = 0;
		}
		if (ccr1Index >= DUTY_CAPTURE_ARRAY_SIZE) ccr1Index = 0;
	}

	if (htim->Instance == TIM6){
		// generate sin wave and net clock

		// Testpin
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1,GPIO_PIN_SET);

		if (DAC_sinWaveGenEnable[0]){
			idx=sinWaveIndex;
			idx += DAC_sinWaveGenIndexOffset[0]; // Phasenverschiebung
			idx %= sizeof(DAC_sinWave)/2;

			if (((sinWaveIndex >= DAC_sinWaveGenStartIndex[0]) && (sinWaveIndex < (sizeof(DAC_sinWave)/4))) || (sinWaveIndex >= ((sizeof(DAC_sinWave)/4) + DAC_sinWaveGenStartIndex[0]))){

				DAC_shiftedSin[0][idx] = ((int32_t)((int32_t)DAC_sinWaveGenAmplitude[0] * (int32_t)DAC_sinWave[sinWaveIndex]) / 1000) + DAC_sinWaveGenOffset[0];
			}else{
				DAC_shiftedSin[0][idx] = DAC_sinWaveGenOffset[0];
			}
			DAC_setValue(0, DAC_shiftedSin[0][sinWaveIndex]);
		}

		if (DAC_sinWaveGenEnable[1]){
			idx=sinWaveIndex;
			idx += DAC_sinWaveGenIndexOffset[1]; // Phasenverschiebung
			idx %= sizeof(DAC_sinWave)/2;

			if (((sinWaveIndex >= DAC_sinWaveGenStartIndex[1]) && (sinWaveIndex < (sizeof(DAC_sinWave)/4))) || (sinWaveIndex >= ((sizeof(DAC_sinWave)/4) + DAC_sinWaveGenStartIndex[1]))){

				DAC_shiftedSin[1][idx] = ((int32_t)((int32_t)DAC_sinWaveGenAmplitude[1] * (int32_t)DAC_sinWave[sinWaveIndex]) / 1000) + DAC_sinWaveGenOffset[1];
			}else{
				DAC_shiftedSin[1][idx] = DAC_sinWaveGenOffset[1];
			}
			DAC_setValue(1, DAC_shiftedSin[1][sinWaveIndex]);
		}

		// generate Net clock
		NET_triacTimeCounter++;
		if((sinWaveIndex < (sizeof(DAC_sinWave) / 4)) && (NET_netClockState == 0)){
			// rising edge of net clock
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0,GPIO_PIN_SET);
			NET_netClockState = 1;
			NET_triacTimeState=0;

			// save triac impulse counter
			NET_triacImpulseCount=NET_triacImpulseCounter;
			NET_triacImpulseCounter=0;

			NET_triacTimeCounter=0;
		}

		if((sinWaveIndex >= (sizeof(DAC_sinWave) / 4)) && (NET_netClockState == 1)){
			// falling edge of net clock
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0,GPIO_PIN_RESET);
			NET_netClockState = 0;
			NET_triacTimeState=0;

			// save triac impulse counter
			NET_triacImpulseCount=NET_triacImpulseCounter;
			NET_triacImpulseCounter=0;

			NET_triacTimeCounter=0;
		}


		if ((NET_triacImpulseCounter > 0) && (NET_triacTimeState == 0)){
			// save the time for the first triac impulse
			NET_triacTimeState=1;
			NET_triacTimeCount=NET_triacTimeCounter;
		}


		sinWaveIndex++;
		if (sinWaveIndex >= (sizeof(DAC_sinWave) / 2))sinWaveIndex=0;

		// Testpin
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1,GPIO_PIN_RESET);
	}
}

//****************************************************
// HAL_TIM_OC_DelayElapsedCallback is a HAL callback
// It will be called whenever a compare event occurs
//
// TIM4:
// Comparevalue will be reached in case of missing PWM signals
//****************************************************
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){


	if (htim->Instance == TIM4){
		// disable interrupts
		htim->Instance->DIER &= ~(TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE);
		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12) == 0x01){
			ccr1Values[ccr1Index++] = 10800;
		}else{
			ccr1Values[ccr1Index++] = 0;
		}
		if (ccr1Index >= DUTY_CAPTURE_ARRAY_SIZE) ccr1Index = 0;
		// enable CCR1 and CCR2
		htim->Instance->DIER |= TIM_DIER_CC2IE;
	}
}

//****************************************************
// HAL_TIM_IC_CaptureCallback is a HAL callback
// It will be called whenever a capture event occurs
//
// TIM4:
// will be used to capture the PWM duty of the high side PWM
// Rising and falling edge will generat an interrupt. Currently just the falling edge interrupt is used
// to capture the timer value.
// The timer is set up to clear the timer value with the rising edge.
// The rising edge interrupt might be used to setup the DAC for current simulation
//****************************************************
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){

	if (htim->Instance == TIM4){
		//HAL_GPIO_WritePin(TestPin_GPIO_Port, TestPin_Pin, GPIO_PIN_SET);
		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12) == 0x01){
			// For Current simulation it would be possible to start DAC here

		}else{
			ccr1Values[ccr1Index++] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			if (ccr1Index >= DUTY_CAPTURE_ARRAY_SIZE) ccr1Index = 0;
		}
		//HAL_GPIO_WritePin(TestPin_GPIO_Port, TestPin_Pin, GPIO_PIN_RESET);
	}
}
//***************************************************************************************************

//***netclock simulation via TIM6********************************************************************
// Netclock is derived from timer 6. Sinus generation is done manually within the TIM6 interrupt.
// DAC channel 0 + 1 can be used to generate sin waves
// Interface:
// uint32_t NET_getTriacFireTime(void);
// uint32_t NET_getTriacFireCount(void);
// void NET_startNetClockGen(void);
// void NET_stopNetClockGen(void);
// void NET_setNetFrequency(uint32_t freq);
//***************************************************************************************************
void NET_setNetFrequency(uint32_t freq){
	// f in Hz
	htim6.Instance->ARR = 1000000/(freq*200);
}

void NET_startNetClockGen(void){
	// enable timer interrupt
	htim6.Instance->DIER |= 0x01;
}

void NET_stopNetClockGen(void){
	// disable timer interrupt
	htim6.Instance->DIER &= ~0x01;
}

uint32_t NET_getTriacFireTime(void){
	return NET_triacTimeCount;
}

uint32_t NET_getTriacFireCount(void){
	return NET_triacImpulseCount;
}


//***analog simulation via DAC channel 1 and 2*******************************************************
// DAC channel 0:	 	internal channel with extended capability which is currently not implemented
// DAC channel 1:	 	internal channel with extended capability which is currently not implemented
// DAC channel 2.. 17:	external channels for normal operation; DAC128S085 will be controlled via SPI4
// Interface:
// void DAC_start(void): initialize the internalDACs, the SPI4 interface and the DAC128S085 devices
// void DAC_setValue(uint32_t channel, uint32_t mV): set a DAC value of the specified channel (0..17) in mV
//***************************************************************************************************
#define DAC_REF_VOLTAGE		((uint32_t)3300)
#define DAC_FULL_SCALE		((uint32_t)4096)



//void DAC_setSinFrequency(uint32_t freq){
//	// f in Hz
//	htim6.Instance->ARR = 1000000/(freq*200);
//}


void DAC_start(void){
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	SPI4_init();
}

void DAC_enableSinGen(uint32_t channel){
	if (channel < 2){
		DAC_sinWaveGenEnable[channel] = 1;
	}
}

void DAC_disableSinGen(uint32_t channel){
	if (channel < 2){
		DAC_sinWaveGenEnable[channel] = 0;
	}
}

void DAC_setSinAmplitude(uint32_t channel, uint32_t amplitude){
	// Spitzenwert der Amplitude (nicht Spitze Spitze) in mV
	if (channel < 2){
		DAC_sinWaveGenAmplitude[channel] = amplitude;
	}
}

void DAC_setSinOffset(uint32_t channel, uint32_t offset){
	// Offset in mV
	if (channel < 2){
		DAC_sinWaveGenOffset[channel] = offset;
	}
}

void DAC_setSinTrigger(uint32_t channel, uint32_t ticks){
	// Zuendzeitpunkt in 1/200 Periode; => 100us bei 50Hz
	if (channel < 2){
		DAC_sinWaveGenStartIndex[channel] = ticks;
	}
}

void DAC_setSinShift(uint32_t channel, uint32_t ticks){
	// Phasenverschiebung in 1/200 Periode; => 100us bei 50Hz
	if (channel < 2){
		DAC_sinWaveGenIndexOffset[channel] = ticks;
	}
}

void DAC_setValue(uint32_t channel, uint32_t mV){
uint32_t value = DAC_FULL_SCALE * mV / DAC_REF_VOLTAGE;
	if (value >= DAC_FULL_SCALE) value = DAC_FULL_SCALE-1;
	switch (channel){
	case 0x00:
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
		break;
	case 0x01:
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);
		break;
	case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07: case 0x08: case 0x09:
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);
		SPI4_write(channel-2, value);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
		break;
	case 0x0A: case 0x0B: case 0x0C: case 0x0D: case 0x0E: case 0x0F: case 0x10: case 0x11:
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
		SPI4_write(channel-10, value);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
		break;

	default:
		SPI4_write(channel-2, value);
		break;
	}
}

//**********************************************************************************************

uint8_t spiBuffer[2];

void SPI4_init(void){
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);
	spiBuffer[0] = 0x00;
	spiBuffer[1] = 0x90;
	HAL_SPI_Transmit(&hspi4, spiBuffer, 1, 2);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi4, spiBuffer, 1, 2);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
}

void SPI4_write(uint32_t channel, uint32_t data){
uint32_t d = data & 0x00000FFF;
	d |= ((channel & 0x00000007) << 12);
	spiBuffer[0] = (uint8_t)(d & 0x000000FF);
	spiBuffer[1] = (uint8_t)((d >> 8) & 0x000000FF);
	HAL_SPI_Transmit(&hspi4, spiBuffer, 1,2);
}

//**************************ende DAC******************************************************************


//***start HAL generation***************************************************************************




//***HALL Generation via TIM3 for Motorsimolation*****************************************************
// TIM3:	 			interrupt is used to generate HALL signals via PD3, PD4, PD5
//						Timer3 clock = 1Mhz
// 						reloadValue = 1/((RPM/60)*6) * 1000000
// 						reloadValue will be written into the TIM3 HW after each interrupt.
//	 					This ensures that the new value is valid after the next interrupt.
// Interface:
// void HALL_setSpeed(uint32_t speedRPM): set HALL speed in RPM
// void HALL_setDirection(uint8_t leftRight): set direction 0 = right ; !0 = left
//***************************************************************************************************
void HALL_setSpeed(uint32_t speedRPM){
uint32_t reloadValue;

	if (speedRPM == 0){
		htim3.Instance->CR1 &= ~TIM_CR1_CEN;
		HALLGEN_hallIndex = 0;
		HALL_setHallPattern(halPatternLinks[HALLGEN_hallIndex]);
	}else{
		reloadValue=1000000*10/speedRPM;
		// make sure that you will not be interrupted here
		__disable_irq();
		tim3ReloadValue = reloadValue;
		__enable_irq();
		htim3.Instance->CR1 |= TIM_CR1_CEN;
	}
}

void HALL_setDirection(HALL_Direction_t direction){
	hallDirection = direction;
}


void HALL_setHallPattern(uint8_t pattern){

	if ( pattern & 0x01){
		HAL_GPIO_WritePin(HAL_OUT_0_GPIO_Port, HAL_OUT_0_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(HAL_OUT_0_GPIO_Port, HAL_OUT_0_Pin, GPIO_PIN_RESET);
	}

	if ( pattern & 0x02){
		HAL_GPIO_WritePin(HAL_OUT_1_GPIO_Port, HAL_OUT_1_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(HAL_OUT_1_GPIO_Port, HAL_OUT_1_Pin, GPIO_PIN_RESET);
	}

	if ( pattern & 0x04){
		HAL_GPIO_WritePin(HAL_OUT_2_GPIO_Port, HAL_OUT_2_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(HAL_OUT_2_GPIO_Port, HAL_OUT_2_Pin, GPIO_PIN_RESET);
	}
}
//***end HAL generation*****************************************************************************


//***PWM TIM2 for test********************************************************************************
// TIM2 Channel 1: 10khz PWM
// OUTPUT: PA0
// Interface:
// void PWM_setDuty(uint8_t duty): set the duty cycle 0..100%
//***************************************************************************************************
void PWM_setDuty(uint8_t duty){
	htim2.Instance->CCR1 = (uint32_t)duty;
}
//**************************ende PWM******************************************************************


//***start duty measurement**************************************************************************
//****************************************************
// getPWMDuty
// calculate and return the actual PWM duty in 1/100 %
//
// TIM4:
// will be used to capture the PWM duty of the high side PWM
// TIM4 will be clocked with 108Mhz
// Rising and falling edge will generate an interrupt. Currently just the falling edge interrupt is used
// to capture the timer value.
// The timer is set up to clear the timer value with the rising edge.
// The rising edge interrupt might be used to setup the DAC for current simulation
// Interface: POWER_getPWMDuty(void)
//****************************************************
uint32_t POWER_getPWMDuty(void){
uint32_t duty = 0;

	// make sure that you will not be interrupted here
	__disable_irq();
	for (uint32_t i = 0; i < DUTY_CAPTURE_ARRAY_SIZE;i++){
		duty+=ccr1Values[i];
	}
	__enable_irq();

	duty /= DUTY_CAPTURE_ARRAY_SIZE;
	duty *= 100;
	duty /= 108;

	return duty;
}

//***end duty measurement****************************************************************************

//***start External Interrupts***********************************************************************
//****************************************************
// External Interrupts used to react fast on external events
//
// EXTI0: PD0
// EXTI1: PD1
//****************************************************
PInterruptConjPort *exti0Port = NULL;
PInterruptConjPort *exti1Port = NULL;

void EXTI_registerExti_0_Port(PInterruptConjPort *p){
	exti0Port = p;
}

void EXTI_registerExti_1_Port(PInterruptConjPort *p){
	exti1Port = p;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	switch (GPIO_Pin){
	case GPIO_PIN_0:
		// PD0 Interrupt
		if(exti0Port != NULL){
			PInterruptConjPort_fire(exti0Port);
			}
		break;

	case GPIO_PIN_1:
		// PD1 Interrupt
		if(exti1Port != NULL){
			PInterruptConjPort_fire(exti1Port);
			}
		break;

	case GPIO_PIN_13:
		// PD13 Interrupt
		// Triac control
		NET_triacImpulseCounter++;
		break;
	default: break;
	}
}
//***end External interrupts*************************************************************************


//***start UART defines*************************************************************************
// general defines and variables for UART

#define AKK_UARTPORT_MODE_REGISTERA_ADDR 	0x40020800
#define AKKU_UARTPORT_TXPIN_MODE_MASK		0x03000000
#define AKKU_UARTPORT_TXPIN_MODE_GPIO		0x01000000
#define AKKU_UARTPORT_TXPIN_MODE_UART		0x02000000

#define AKKU_UART_STATE_RECEIVING_BYTE		0x01
#define AKKU_UART_STATE_RECEIVING_FRAME		0x02

#define UART6_UART_STATE_RECEIVING_BYTE		0x01
#define UART6_UART_STATE_RECEIVING_FRAME	0x02

#define UART7_UART_STATE_RECEIVING_BYTE		0x01
#define UART7_UART_STATE_RECEIVING_FRAME	0x02

uint8_t AKKU_rxBuffer[10];
uint8_t AKKU_txBuffer[10];
uint8_t UART6_rxBuffer[10];
uint8_t UART6_txBuffer[10];
uint8_t UART7_rxBuffer[64];
uint8_t UART7_txBuffer[64];

uint8_t AKKU_uartState = 0;
uint8_t UART6_uartState = 0;
uint8_t UART7_uartState = 0;

PInterruptConjPort *AKKU_uartPort = NULL;
PInterruptConjPort *AKKU_uartErrorPort = NULL;

PInterruptConjPort *UART6_uartPort = NULL;
PInterruptConjPort *UART6_uartErrorPort = NULL;

PInterruptConjPort *UART7_uartPort = NULL;
PInterruptConjPort *UART7_uartErrorPort = NULL;

// Calculate Uart Checksum
uint8_t UART_getCs(uint8_t * buffer, uint8_t len){
uint8_t c;
	c = 0;
    for(uint8_t i=0;i < len; i++){
        c ^= buffer[i];
     }
     return c;
}

//UART callbacks:
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
printQueueObj * pBuf;

	if (UART5 == huart->Instance){

	}

	if (USART6 == huart->Instance){

	}

	if (UART7 == huart->Instance){

	}

	if (USART3 == huart->Instance){
		pBuf = (printQueueObj *)etQueue_pop(&printUsedQueue);
		etQueue_push(&printFreeQueue, (etQueueObj *)pBuf);

		if (etQueue_isNotEmpty(&printUsedQueue)){
			pBuf = (printQueueObj *) etQueue_getFirst(&printUsedQueue);
			HAL_UART_Transmit_IT(&huart3, (uint8_t *)pBuf->charBuffer, pBuf->len);
		}else{
			debugUartIdle = 1;
		}
	}

	if (UART8 == huart->Instance){
		// Testreporting Interface
		pBuf = (printQueueObj *)etQueue_pop(&etUnitPrintUsedQueue);
		etQueue_push(&etUnitPrintFreeQueue, (etQueueObj *)pBuf);

		if (etQueue_isNotEmpty(&etUnitPrintUsedQueue)){
			pBuf = (printQueueObj *) etQueue_getFirst(&etUnitPrintUsedQueue);
			HAL_UART_Transmit_IT(&huart8, (uint8_t *)pBuf->charBuffer, pBuf->len);
		}else{
			etUnitUartIdle = 1;
		}

	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if (UART5 == huart->Instance){
		if (AKKU_uartState == AKKU_UART_STATE_RECEIVING_BYTE){
			if (AKKU_uartPort != NULL ){
				PInterruptConjPort_fire(AKKU_uartPort);
			}
		}

		if (AKKU_uartState == AKKU_UART_STATE_RECEIVING_FRAME){
			if (UART_getCs(AKKU_rxBuffer,5) == AKKU_rxBuffer[5]){
				if (AKKU_uartPort != NULL ){
					PInterruptConjPort_fire(AKKU_uartPort);
				}
			}else{
				if (AKKU_uartErrorPort != NULL ){
					PInterruptConjPort_fire(AKKU_uartErrorPort);
				}
			}
		}
		AKKU_uartState = 0;
	}
	if (USART6 == huart->Instance){
		if (UART6_uartState == UART6_UART_STATE_RECEIVING_BYTE){
			if (UART6_uartPort != NULL ){
				PInterruptConjPort_fire(UART6_uartPort);
			}
		}

		if (UART6_uartState == UART6_UART_STATE_RECEIVING_FRAME){
			if (UART_getCs(UART6_rxBuffer,5) == UART6_rxBuffer[5]){ // hier noch generalisieren, dass der general UART auch ohne CS und mit variabler Länge verwendet werden kann
				if (UART6_uartPort != NULL ){
					PInterruptConjPort_fire(UART6_uartPort);
				}
			}else{
				if (UART6_uartErrorPort != NULL ){
					PInterruptConjPort_fire(UART6_uartErrorPort);
				}
			}
		}
		UART6_uartState = 0;
	}
	if (UART7 == huart->Instance){
		if (UART7_uartState == UART7_UART_STATE_RECEIVING_BYTE){
			if (UART7_uartPort != NULL ){
				PInterruptConjPort_fire(UART7_uartPort);
			}
		}

		if (UART7_uartState == UART7_UART_STATE_RECEIVING_FRAME){
			if (UART_getCs(UART7_rxBuffer,5) == UART7_rxBuffer[5]){ // hier noch generalisieren, dass der general UART auch ohne CS und mit variabler Länge verwendet werden kann
				if (UART7_uartPort != NULL ){
					PInterruptConjPort_fire(UART7_uartPort);
				}
			}else{
				if (UART7_uartErrorPort != NULL ){
					PInterruptConjPort_fire(UART7_uartErrorPort);
				}
			}
		}
		UART7_uartState = 0;
	}
	if (USART3 == huart->Instance){

	}

	if (UART8 == huart->Instance){

	}

}

//***end UART defines*************************************************************************


// Akku simulation uses UART5
//***start Akku Simulation***************************************************************************
// Akku simulation uses UART5
void AKKU_registerUartPort(PInterruptConjPort *p){
	AKKU_uartPort=p;
}

void AKKU_registerUartErrorPort(PInterruptConjPort *p){
	AKKU_uartErrorPort=p;
}

uint8_t * AKKU_getRxBuffer(void){
	return AKKU_rxBuffer;
}

void AKKU_initUart(void){
	Hal_initUart5();
}

uint8_t AKKU_getRxLevel(void){
	return (uint8_t) HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2);
}

void AKKU_setUartTxToLow(void){
uint32_t regVal;
	regVal = (*(uint32_t *)AKK_UARTPORT_MODE_REGISTERA_ADDR);
	regVal &= ~AKKU_UARTPORT_TXPIN_MODE_MASK;
	regVal |= AKKU_UARTPORT_TXPIN_MODE_GPIO;
	(*(uint32_t *)AKK_UARTPORT_MODE_REGISTERA_ADDR) = regVal;

}

void AKKU_setUartTxToUart(void){
	uint32_t regVal;
		regVal = (*(uint32_t *)AKK_UARTPORT_MODE_REGISTERA_ADDR);
		regVal &= ~AKKU_UARTPORT_TXPIN_MODE_MASK;
		regVal |= AKKU_UARTPORT_TXPIN_MODE_UART;
		(*(uint32_t *)AKK_UARTPORT_MODE_REGISTERA_ADDR) = regVal;

		huart5.RxState = HAL_UART_STATE_READY;
}

void AKKU_receiveByte(void){
	AKKU_uartState = AKKU_UART_STATE_RECEIVING_BYTE;
	HAL_UART_Receive_IT(&huart5, AKKU_rxBuffer, 1);
}

void AKKU_receiveFrame(void){
	AKKU_uartState = AKKU_UART_STATE_RECEIVING_FRAME;
	HAL_UART_Receive_IT(&huart5, AKKU_rxBuffer, 6);
}

void AKKU_sendByte(uint8_t byte){
	AKKU_txBuffer[0] = byte;
	HAL_UART_Transmit_IT(&huart5, AKKU_txBuffer, 1);
}

void AKKU_sendFrame(uint8_t * buffer){
uint8_t *p = buffer;

	for (uint8_t i = 0; i<6; i++ ){
		AKKU_txBuffer[i] = *p++;
	}

	AKKU_txBuffer[5] = UART_getCs(AKKU_txBuffer,5);
	HAL_UART_Transmit_IT(&huart5, AKKU_txBuffer, 6);
}

//***end Akku Simulation*****************************************************************************

//***start UART6 Simulation***************************************************************************
// Generic UART6
void UART6_registerUartPort(PInterruptConjPort *p){
	UART6_uartPort=p;
}

void UART6_registerUartErrorPort(PInterruptConjPort *p){
	UART6_uartErrorPort=p;
}

uint8_t * UART6_getRxBuffer(void){
	return UART6_rxBuffer;
}

void UART6_initUart(void){
	Hal_initUsart6();
}

void UART6_receiveByte(void){
	UART6_uartState = UART6_UART_STATE_RECEIVING_BYTE;
	HAL_UART_Receive_IT(&huart6, UART6_rxBuffer, 1);
}

void UART6_receiveFrame(void){
	UART6_uartState = UART6_UART_STATE_RECEIVING_FRAME;
	HAL_UART_Receive_IT(&huart6, UART6_rxBuffer, 6);
}

void UART6_sendByte(uint8_t byte){
	UART6_txBuffer[0] = byte;
	HAL_UART_Transmit_IT(&huart6, UART6_txBuffer, 1);
}

void UART6_sendFrame(uint8_t * buffer){
uint8_t *p = buffer;

	for (uint8_t i = 0; i<6; i++ ){
		UART6_txBuffer[i] = *p++;
	}

	UART6_txBuffer[5] = UART_getCs(UART6_txBuffer,5);
	HAL_UART_Transmit_IT(&huart6, UART6_txBuffer, 6);
}

//***end UART6 *****************************************************************************

//***start UART7 Simulation***************************************************************************
// Generic UART7
void UART7_registerUartPort(PInterruptConjPort *p){
	UART7_uartPort=p;
}

void UART7_registerUartErrorPort(PInterruptConjPort *p){
	UART7_uartErrorPort=p;
}

uint8_t * UART7_getRxBuffer(void){
	return UART7_rxBuffer;
}

void UART7_initUart(void){
	Hal_initUart7();
}

void UART7_receiveByte(void){
	UART7_uartState = UART7_UART_STATE_RECEIVING_BYTE;
	HAL_UART_Receive_IT(&huart7, UART7_rxBuffer, 1);
}

void UART7_receiveFrame(void){
	UART7_uartState = UART7_UART_STATE_RECEIVING_FRAME;
	HAL_UART_Receive_IT(&huart7, UART7_rxBuffer, 6);
}

void UART7_sendByte(uint8_t byte){
	UART7_txBuffer[0] = byte;
	HAL_UART_Transmit_IT(&huart7, UART7_txBuffer, 1);
}

void UART7_sendFrame(uint8_t * buffer){
uint8_t *p = buffer;

	for (uint8_t i = 0; i<6; i++ ){
		UART7_txBuffer[i] = *p++;
	}

	UART7_txBuffer[5] = UART_getCs(UART7_txBuffer,5);
	HAL_UART_Transmit_IT(&huart7, UART7_txBuffer, 6);
}

//***end UART7 *****************************************************************************


//**************************************************************************************************
//***start handling port extender I2C4***************************************************************
//****************************************************
// I2C4 is used for the Port Extender chip
// Both Port extender will be read out periodically with standard i2c speed (100kHz)
// If an input has changed, a message will be sent
// Changing an output takes place on request
//
// Interface:
// I2C4_start(void);
// I2C4_setIOBits(uint8_t pattern, uint8_t device);
// I2C4_resetIOBits(uint8_t pattern, uint8_t device);
// uint32_t I2C4_getIOBits(void);
//****************************************************
void i2c4Init(void);
uint8_t I2C4_rx0Buffer[2];
uint8_t I2C4_rx1Buffer[2];
uint8_t I2C4_tx0Buffer[2];
uint8_t I2C4_tx1Buffer[2];
uint8_t I2C4_rxtx_state = 0;
uint8_t I2C4_tx0Request = 0;
uint8_t I2C4_tx1Request = 0;

uint32_t I2C4_getIOBits(void){

	return (((uint32_t)I2C4_rx0Buffer[1])<<24 | ((uint32_t)I2C4_rx0Buffer[0])<<16 | ((uint32_t)I2C4_rx1Buffer[1])<<8 | I2C4_rx1Buffer[0]);
}

void I2C4_changeIOBits(uint32_t pattern, uint8_t onOff){
uint8_t pattern0 = (uint8_t) ((pattern >> 16) & 0x00FF);
uint8_t pattern1 = (uint8_t) ((pattern >> 24) & 0x00FF);
uint8_t pattern2 = (uint8_t) ((pattern) & 0x00FF);
uint8_t pattern3 = (uint8_t) ((pattern >> 8) & 0x00FF);

	if (onOff){
		I2C4_tx0Buffer[0] |= pattern0;
		I2C4_tx0Buffer[1] |= pattern1;
		I2C4_tx1Buffer[0] |= pattern2;
		I2C4_tx1Buffer[1] |= pattern3;
	}else{
		I2C4_tx0Buffer[0] &= ~pattern0;
		I2C4_tx0Buffer[1] &= ~pattern1;
		I2C4_tx1Buffer[0] &= ~pattern2;
		I2C4_tx1Buffer[1] &= ~pattern3;
	}
	I2C4_tx0Request = 1;
	I2C4_tx1Request = 1;
}


void I2C4_start(void){
	I2C4_tx0Buffer[0] = (uint8_t) ((PORTEXTENDER_INPUT_MASK >> 16) & 0xFF);
	I2C4_tx0Buffer[1] = (uint8_t) ((PORTEXTENDER_INPUT_MASK >> 24) & 0xFF);
	while (HAL_I2C_Mem_Write(&hi2c4, 0x0040, 0x06, I2C_MEMADD_SIZE_8BIT, I2C4_tx0Buffer, 0x02, 0x02) != HAL_OK){
		i2c4Init();
	}
//	if (HAL_I2C_Mem_Write(&hi2c4, 0x0040, 0x06, I2C_MEMADD_SIZE_8BIT, I2C4_tx0Buffer, 0x02, 0x02) != HAL_OK){
//		while(1){}
//	}

	I2C4_tx1Buffer[0] = (uint8_t) ((PORTEXTENDER_INPUT_MASK) & 0xFF);
	I2C4_tx1Buffer[1] = (uint8_t) ((PORTEXTENDER_INPUT_MASK >> 8) & 0xFF);
	while (HAL_I2C_Mem_Write(&hi2c4, 0x0042, 0x06, I2C_MEMADD_SIZE_8BIT, I2C4_tx1Buffer, 0x02, 0x02) != HAL_OK){
		i2c4Init();
	}
//	if (HAL_I2C_Mem_Write(&hi2c4, 0x0042, 0x06, I2C_MEMADD_SIZE_8BIT, I2C4_tx1Buffer, 0x02, 0x02) != HAL_OK){
//		while(1){}
//	}

	I2C4_tx0Buffer[0] = 0x00;
	I2C4_tx0Buffer[1] = 0x00;
	I2C4_tx1Buffer[0] = 0x00;
	I2C4_tx1Buffer[1] = 0x00;

	I2C4_tx0Request = 1;
	I2C4_tx1Request = 1;

	HAL_I2C_Mem_Read_DMA(&hi2c4, 0x0040, 0x00, I2C_MEMADD_SIZE_8BIT, I2C4_rx0Buffer, 0x02);
}

void I2C4_nextRead(void){

	if (I2C4_tx0Request){
		I2C4_tx0Request = 0;
		HAL_I2C_Mem_Write_DMA(&hi2c4, 0x0040, 0x00, I2C_MEMADD_SIZE_8BIT, I2C4_tx0Buffer, 0x02);
		return;
	}

	if (I2C4_tx1Request){
		I2C4_tx1Request = 0;
		HAL_I2C_Mem_Write_DMA(&hi2c4, 0x0042, 0x00, I2C_MEMADD_SIZE_8BIT, I2C4_tx1Buffer, 0x02);
		return;
	}

	switch (I2C4_rxtx_state){
	case 0:
		HAL_I2C_Mem_Read_DMA(&hi2c4, 0x0040, 0x00, I2C_MEMADD_SIZE_8BIT, I2C4_rx0Buffer, 0x02);
		I2C4_rxtx_state++;
		break;
	case 1:
		HAL_I2C_Mem_Read_DMA(&hi2c4, 0x0042, 0x00, I2C_MEMADD_SIZE_8BIT, I2C4_rx1Buffer, 0x02);
		I2C4_rxtx_state = 0;
		break;
	default:
		I2C4_rxtx_state = 0;
		break;
	}
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){

	if (hi2c->Instance == I2C4){
		I2C4_nextRead();
	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if (hi2c->Instance == I2C4){
		I2C4_nextRead();
	}
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
	volatile uint32_t dummy = 0;
		dummy = HAL_I2C_GetError(hi2c);
}


//***start Debug Uart****n***************************************************************************
// LOGGING UART via  ST-Link UASART 3
void LOGGING_init(void){

	etQueue_init(&printFreeQueue);
	etQueue_init(&printUsedQueue);
	for (uint8_t i=0; i< DEBUG_AMOUNT_OF_PRINT_BUFFERS; i++){
		etQueue_push(&printFreeQueue, &(printBuffers[i].queueElem));
	}
}

void LOGGING_serialOut(DSerialBuffer *buf){

printQueueObj * pBuf;

	if (buf->len > DEBUG_PRINT_BUFFER_SIZE)return;

	__disable_irq();
	pBuf = (printQueueObj *)etQueue_pop(&printFreeQueue);
	__enable_irq();

	pBuf->len = buf->len;
	memcpy(pBuf->charBuffer, buf->buffer, buf->len);

	__disable_irq();
	etQueue_push(&printUsedQueue, (etQueueObj *)pBuf);
	if (debugUartIdle == 1){
		debugUartIdle = 0;
		HAL_UART_Transmit_IT(&huart3, (uint8_t *)pBuf->charBuffer,pBuf->len);
	}
	__enable_irq();
}

//***end Debug UART****n*****************************************************************************

//***start etUnit print UART*******************************************************************************
// etUnit print UART via  UART8 / FTDI2

void ETUNIT_init(void){

	etQueue_init(&etUnitPrintFreeQueue);
	etQueue_init(&etUnitPrintUsedQueue);
	for (uint8_t i=0; i< ETUNIT_AMOUNT_OF_PRINT_BUFFERS; i++){
		etQueue_push(&etUnitPrintFreeQueue, &(etUnitPrintBuffers[i].queueElem));
	}
}

void ETUNIT_serialOut(uint8_t *buf){
uint16_t len = 0;
uint8_t *p1 = buf;
uint8_t *p2;

printQueueObj * pBuf;


	__disable_irq();
	pBuf = (printQueueObj *)etQueue_pop(&etUnitPrintFreeQueue);
	__enable_irq();

	p2=(uint8_t *)&(pBuf->charBuffer);

	do{
		*p2++ = *p1++;
		len++;
	} while((*p1 != 0) && (len < DEBUG_PRINT_BUFFER_SIZE));

	pBuf->len=len;

	__disable_irq();
	etQueue_push(&etUnitPrintUsedQueue, (etQueueObj *)pBuf);
	if (etUnitUartIdle == 1){
		etUnitUartIdle = 0;
		HAL_UART_Transmit_IT(&huart8, (uint8_t *)pBuf->charBuffer, len);
	}
	__enable_irq();
}

//***end etUnit UART*********************************************************************************


//****************************************************
// ADC1 is used to convert the Potis on the Simulation board
// This is for manuual testing
//
// Interface:
// void ADC_init(void); => starts the conversion of the ADC with DMA transfere
// uint16_t ADC_getValue(uint8_t channel); => returns the converted value of the specified channel
//****************************************************
uint16_t ADC_buffer[24];

void ADC_init(void){
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_buffer, 24);
}

uint16_t ADC_getValue(uint8_t channel){
uint32_t value = 0;
uint32_t mV;

	if (channel > 5) return 0;

	for (uint8_t i = 0; i < 4; i++){
		value += ADC_buffer[channel + i*6];
	}
	value >>= 2;

	mV = value * 3300 / 4096;

	return mV;
}
