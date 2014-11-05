#include "msp430f5438a.h"
#include "platforms/etTimer.h"

/* global timer */

static etTargetTime_t targetTime;
static etTargetTime_t lastTargetTime;
static volatile etBool etTimer_executeFlag = FALSE;

void etTimer_init(void){
	targetTime.nSec=0;
	targetTime.sec=0;
	lastTargetTime.nSec=0;
	lastTargetTime.sec=0;
}

etBool etTimer_executeNeeded(void){
	if (etTimer_executeFlag == TRUE){
		etTimer_executeFlag = FALSE;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int isTimeGreaterThanActualTime(const etTargetTime_t *t) {

	_disable_interrupt();
	if (t->sec > targetTime.sec) {
		_enable_interrupt();
		return 1;
	}

	if (t->sec < targetTime.sec) {
		_enable_interrupt();
		return 0;
	}

	if (t->nSec > targetTime.nSec) {
		_enable_interrupt();
		return 1;
	}
	else {
		_enable_interrupt();
		return 0;
	}
}

uint32 getNSecFromTarget(void){
	etTargetTime_t time;
	getTimeFromTarget(&time);
	return time.nSec;
}

uint32 getSecFromTarget(void){
	etTargetTime_t time;
	getTimeFromTarget(&time);
	return time.sec;
}


void getTimeFromTarget(etTargetTime_t *t) {
	_disable_interrupt();
	*t = targetTime;
	_enable_interrupt();
}

#define ET_TIMER_TIME_BASE_NS 15625000L
#define ET_TIMER_TIME_BASE_US ET_TIMER_TIME_BASE_NS / 1000L
#define ET_TIMER_TIME_BASE_MS ET_TIMER_TIME_BASE_US / 1000L

uint32 getTimeBaseNS(void){
	return ET_TIMER_TIME_BASE_NS;
}

uint32 getTimeBaseUS(void){
	return ET_TIMER_TIME_BASE_US;
}

uint32 getTimeBaseMS(void){
	return ET_TIMER_TIME_BASE_MS;
}


/* the timer interrupt */
#pragma INTERRUPT(wdt_isr)
#pragma vector=WDT_VECTOR
void wdt_isr(void) {
// this interrupt will be called every 15,625ms

	etTimer_executeFlag = TRUE;
	targetTime.nSec += 15625000L;

	if (targetTime.nSec >= 1000000000L) {
		targetTime.nSec -= 1000000000L;
		targetTime.sec++;
	}
} // end interrupt
