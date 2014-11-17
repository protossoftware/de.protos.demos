/*
 * InterruptHandlers.c
 *
 *  Created on: 16.11.2014
 *      Author: TJung
 */

#include "room/basic/service/pinterrupt/PInterrupt.h"

PInterruptConjPort* uart_isr_port;

void uartRxInt(){
volatile unsigned char i;

i++;
PInterruptConjPort_fire(uart_isr_port);
}
