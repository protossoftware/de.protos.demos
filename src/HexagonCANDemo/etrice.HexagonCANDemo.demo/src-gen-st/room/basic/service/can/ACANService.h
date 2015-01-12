/**
 * @author generated by eTrice
 *
 * Header File of ActorClass ACANService
 * 
 */

#ifndef _ROOM_BASIC_SERVICE_CAN_ACANSERVICE_H_
#define _ROOM_BASIC_SERVICE_CAN_ACANSERVICE_H_

#include "etDatatypes.h"
#include "messaging/etMessage.h"

#include "room/basic/service/can/DCANData.h"
#include "room/basic/service/can/PCANRx.h"
#include "room/basic/service/can/PCANTx.h"
#include "room/basic/service/timing/PTimer.h"

/*--------------------- begin user code ---------------------*/
/*uc1*/
/*--------------------- end user code ---------------------*/

typedef struct ACANService ACANService;

/* const part of ActorClass (ROM) */
typedef struct ACANService_const {
	/* simple ports */
	
	/* data receive ports */

	/* saps */
	const PTimerConjPort timer;
	
	/* replicated ports */
	
	/* services */
	const etReplPort canTx;
	const etReplPort canRx;
} ACANService_const;


/* constant for state machine data */
#define ACANSERVICE_HISTORY_SIZE 2

/* variable part of ActorClass (RAM) */
struct ACANService {
	const ACANService_const* const constData;
	
	/* data send ports */
	
	/*--------------------- attributes ---------------------*/
	DCANData rxData[10];
	DCANData txData[10];
	uint32 pollTime;
	
	
	/* state machine variables */
	etInt16 state;
	etInt16 history[ACANSERVICE_HISTORY_SIZE];
};

void ACANService_init(ACANService* self);

void ACANService_receiveMessage(void* self, const void* ifitem, const etMessage* msg);


/*--------------------- operations ---------------------*/
void ACANService_pollAllRxMsgs(ACANService* self);

/*--------------------- begin user code ---------------------*/
/*uc2*/
/*--------------------- end user code ---------------------*/

#endif /* _ROOM_BASIC_SERVICE_CAN_ACANSERVICE_H_ */
