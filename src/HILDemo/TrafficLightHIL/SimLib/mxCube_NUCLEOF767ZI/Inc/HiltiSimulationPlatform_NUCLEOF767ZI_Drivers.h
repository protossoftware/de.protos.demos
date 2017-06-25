/*
 * HiltiSimulationPlatform_NUCLEOF767ZI_Drivers.h
 *
 *  Created on: 06.12.2016
 *      Author: JUNGTHOM
 */

#ifndef HILTISIMULATIONPLATFORM_NUCLEOF767ZI_DRIVERS_H_
#define HILTISIMULATIONPLATFORM_NUCLEOF767ZI_DRIVERS_H_
#include "PInterrupt.h"
#include "DSerialBuffer.h"

#define PORTEXTENDER_INPUT_MASK 0xCFF0FF00
//FF00CFF0

#define PE_IC9_P00_MASK 0x00010000
#define PE_IC9_P01_MASK 0x00020000
#define PE_IC9_P02_MASK 0x00040000
#define PE_IC9_P03_MASK 0x00080000
#define PE_IC9_P04_MASK 0x00100000
#define PE_IC9_P05_MASK 0x00200000
#define PE_IC9_P06_MASK 0x00400000
#define PE_IC9_P07_MASK 0x00800000

#define PE_IC9_P10_MASK 0x01000000
#define PE_IC9_P11_MASK 0x02000000
#define PE_IC9_P12_MASK 0x04000000
#define PE_IC9_P13_MASK 0x08000000
#define PE_IC9_P14_MASK 0x10000000
#define PE_IC9_P15_MASK 0x20000000
#define PE_IC9_P16_MASK 0x40000000
#define PE_IC9_P17_MASK 0x80000000

#define PE_IC10_P00_MASK 0x00000001
#define PE_IC10_P01_MASK 0x00000002
#define PE_IC10_P02_MASK 0x00000004
#define PE_IC10_P03_MASK 0x00000008
#define PE_IC10_P04_MASK 0x00000010
#define PE_IC10_P05_MASK 0x00000020
#define PE_IC10_P06_MASK 0x00000040
#define PE_IC10_P07_MASK 0x00000080

#define PE_IC10_P10_MASK 0x00000100
#define PE_IC10_P11_MASK 0x00000200
#define PE_IC10_P12_MASK 0x00000400
#define PE_IC10_P13_MASK 0x00000800
#define PE_IC10_P14_MASK 0x00001000
#define PE_IC10_P15_MASK 0x00002000
#define PE_IC10_P16_MASK 0x00004000
#define PE_IC10_P17_MASK 0x00008000

typedef enum HALL_Direction {hall_left, hall_right} HALL_Direction_t;

void NET_setNetFrequency(uint32_t freq);
void NET_startNetClockGen(void);
void NET_stopNetClockGen(void);
uint32_t NET_getTriacFireTime(void);
uint32_t NET_getTriacFireCount(void);

//void CURRENT_setValue(uint32_t value);
void DAC_setValue(uint32_t channel, uint32_t value);
//void POTI_setValue(uint32_t value);
void DAC_start(void);
void DAC_enableSinGen(uint32_t channel);
void DAC_disableSinGen(uint32_t channel);
void DAC_setSinAmplitude(uint32_t channel, uint32_t amplitude);
void DAC_setSinOffset(uint32_t channel, uint32_t offset);
void DAC_setSinTrigger(uint32_t channel, uint32_t ticks);
void DAC_setSinShift(uint32_t channel, uint32_t ticks);

void PWM_setDuty(uint8_t duty);
uint32_t POWER_getPWMDuty(void);

void EXTI_registerExti_0_Port(PInterruptConjPort *p);
void EXTI_registerExti_1_Port(PInterruptConjPort *p);

void LOGGING_init(void);
void LOGGING_serialOut(DSerialBuffer *buf);
void ETUNIT_init(void);
void ETUNIT_serialOut(uint8_t *buf);


// rework interface
void AKKU_setUartTxToLow(void);
void AKKU_setUartTxToUart(void);
void AKKU_receiveByte(void);
void AKKU_registerUartPort(PInterruptConjPort *p);
void AKKU_registerUartErrorPort(PInterruptConjPort *p);
void AKKU_initUart(void);
uint8_t * AKKU_getRxBuffer(void);
uint8_t AKKU_getRxLevel(void);

uint32_t I2C4_getIOBits(void);
void I2C4_changeIOBits(uint32_t pattern, uint8_t onOff);

// ADC
void ADC_init(void);
uint16_t ADC_getValue(uint8_t channel);

void HALL_setSpeed(uint32_t speedRPM);
void HALL_setDirection(HALL_Direction_t direction);


#endif /* HILTISIMULATIONPLATFORM_NUCLEOF767ZI_DRIVERS_H_ */
