/**
 * @author generated by eTrice
 *
 * Header File of ActorClass ACabineController
 * 
 */

#ifndef _ELEVATORFREERTOS_MODEL_ACABINECONTROLLER_H_
#define _ELEVATORFREERTOS_MODEL_ACABINECONTROLLER_H_

#include "etDatatypes.h"
#include "messaging/etMessage.h"

#include "ElevatorFreeRTOS_Model/PButtonControl.h"
#include "ElevatorFreeRTOS_Model/PCabineControl.h"
#include "ElevatorFreeRTOS_Model/PDoorControl.h"
#include "room/basic/service/timing/PTimer.h"

/*--------------------- begin user code ---------------------*/
#include "etPlatform.h"
/*--------------------- end user code ---------------------*/

typedef struct ACabineController ACabineController;

/* const part of ActorClass (ROM) */
typedef struct ACabineController_const {
	/* simple ports */
	const PCabineControlPort ControlPort;
	const PDoorControlConjPort DoorPort;
	const PButtonControlConjPort DoorButtonPort;
	
	/* data receive ports */

	/* saps */
	
	/* replicated ports */
	const etReplPort ButtonPort;
	
	/* services */
} ACabineController_const;


/* constant for state machine data */
#define ACABINECONTROLLER_HISTORY_SIZE 2

/* variable part of ActorClass (RAM) */
struct ACabineController {
	const ACabineController_const* const constData;
	
	/* data send ports */
	
	/*--------------------- attributes ---------------------*/
	
	
	/* state machine variables */
	etInt16 state;
	etInt16 history[ACABINECONTROLLER_HISTORY_SIZE];
};

void ACabineController_init(ACabineController* self);

void ACabineController_receiveMessage(void* self, const void* ifitem, const etMessage* msg);


/*--------------------- operations ---------------------*/


#endif /* _ELEVATORFREERTOS_MODEL_ACABINECONTROLLER_H_ */
