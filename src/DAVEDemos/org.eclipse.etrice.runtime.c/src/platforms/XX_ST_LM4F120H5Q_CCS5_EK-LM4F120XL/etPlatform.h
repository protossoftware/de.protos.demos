/*
 * etPlatform.h
 *
 *  Created on: 23.06.2012
 *      Author: junggtho
 */

#ifndef ETPLATFORM_H_
#define ETPLATFORM_H_

#define RED_LED   0x00000002 //GPIO_PIN_1
#define BLUE_LED  0x00000004 //GPIO_PIN_2
#define GREEN_LED 0x00000008 //GPIO_PIN_3

#define LED_ON 		0x01
#define LED_OFF		0x00

void initHw(void);
void switchLed(unsigned int led, unsigned int onOff);
unsigned long getSysTick(void);

#endif /* ETPLATFORM_H_ */
