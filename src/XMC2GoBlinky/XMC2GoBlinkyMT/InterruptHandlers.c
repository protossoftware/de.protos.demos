/*
 * InterruptHandlers.c
 *
 *  Created on: 16.11.2014
 *      Author: TJung
 */

#include "XMC2GoDemoModel/PInterrupt.h"

PInterruptConjPort* uart_isr_port;

void uartRxInt(){
volatile unsigned char i;

i++;
PInterruptConjPort_fire(uart_isr_port);
}
