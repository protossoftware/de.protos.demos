/**
 * @author generated by eTrice
 *
 * Header File of Node msp430FreeRTOS with SubSystem elevator_subSysRef
 * 
 */

#ifndef _MSP430FREERTOS_ELEVATOR_SUBSYSREF_H_
#define _MSP430FREERTOS_ELEVATOR_SUBSYSREF_H_

#include "etDatatypes.h"



/* lifecycle functions
 * init -> start -> run (loop) -> stop -> destroy
 */

void msp430FreeRTOS_elevator_subSysRef_init(void);		/* lifecycle init  	 */
void msp430FreeRTOS_elevator_subSysRef_start(void);	/* lifecycle start 	 */

void msp430FreeRTOS_elevator_subSysRef_run(etBool runAsTest);		/* lifecycle run 	 */

void msp430FreeRTOS_elevator_subSysRef_stop(void); 	/* lifecycle stop	 */
void msp430FreeRTOS_elevator_subSysRef_destroy(void); 	/* lifecycle destroy */

void msp430FreeRTOS_elevator_subSysRef_shutdown(void);  /* shutdown the dispatcher loop */


#endif /* _MSP430FREERTOS_ELEVATOR_SUBSYSREF_H_ */

