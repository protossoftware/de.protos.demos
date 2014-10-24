/**
 * @author generated by eTrice
 *
 * Header File of ActorClass Application
 * 
 */

#ifndef _HEXAGON_APPLICATION_H_
#define _HEXAGON_APPLICATION_H_

#include "etDatatypes.h"
#include "messaging/etMessage.h"

#include "hexagon/PBlinkyControl.h"
#include "hexagon/PButtonControlProtocoll.h"
#include "hexagon/PButtonProtocoll.h"
#include "DaveInterface/PIO004.h"
#include "room/basic/service/timing/PTimer.h"


typedef struct Application Application;

/* const part of ActorClass (ROM) */
typedef struct Application_const {
	const char* instName;
	
	/* simple ports */
	const PBlinkyControlConjPort blinkyPort;
	const PButtonControlProtocollConjPort buttonControlPort;
	const PButtonProtocollConjPort buttonPort;
	
	/* data receive ports */

	/* saps */
	
	/* replicated ports */
	
	/* services */
} Application_const;


/* constant for state machine data */
#define APPLICATION_HISTORY_SIZE 2

/* variable part of ActorClass (RAM) */
struct Application {
	const Application_const* const constData;
	
	/* data send ports */
	
	/*--------------------- attributes ---------------------*/
	
	
	/* state machine variables */
	etInt16 state;
	etInt16 history[APPLICATION_HISTORY_SIZE];
};

void Application_init(Application* self);

void Application_receiveMessage(void* self, const void* ifitem, const etMessage* msg);


/*--------------------- operations ---------------------*/


#endif /* _HEXAGON_APPLICATION_H_ */

