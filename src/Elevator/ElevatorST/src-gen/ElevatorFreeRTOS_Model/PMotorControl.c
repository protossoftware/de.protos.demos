/**
 * @author generated by eTrice
 *
 * Source File of ProtocolClass PMotorControl
 * 
 */

#include "PMotorControl.h"
#include "debugging/etMSCLogger.h"
#include "PMotorControl_Utils.h"


/*--------------------- port methods */

void PMotorControlPort_floorReached(const PMotorControlPort* self, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlPort", "floorReached")
		etPort_sendMessage(self, PMotorControl_OUT_floorReached, sizeof(uint8), &data__et);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PMotorControlReplPort_floorReached_broadcast(const PMotorControlReplPort* self, uint8 data__et) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlReplPort", "floorReached")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PMotorControl_OUT_floorReached, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PMotorControlReplPort_floorReached(const PMotorControlReplPort* self, int idx__et, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlReplPort", "floorReached")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PMotorControl_OUT_floorReached, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

etInt32 PMotorControlReplPort_getReplication(const PMotorControlReplPort* self) {
	return ((etReplPort*)self)->size;
}



void PMotorControlConjPort_goUpOneFloor(const PMotorControlConjPort* self) {
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlConjPort", "goUpOneFloor")
		etPort_sendMessage(self, PMotorControl_IN_goUpOneFloor, 0, NULL);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PMotorControlConjReplPort_goUpOneFloor_broadcast(const PMotorControlConjReplPort* self) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlConjReplPort", "goUpOneFloor")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PMotorControl_IN_goUpOneFloor, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PMotorControlConjReplPort_goUpOneFloor(const PMotorControlConjReplPort* self, int idx__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlConjReplPort", "goUpOneFloor")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PMotorControl_IN_goUpOneFloor, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PMotorControlConjPort_goDownOneFloor(const PMotorControlConjPort* self) {
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlConjPort", "goDownOneFloor")
		etPort_sendMessage(self, PMotorControl_IN_goDownOneFloor, 0, NULL);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PMotorControlConjReplPort_goDownOneFloor_broadcast(const PMotorControlConjReplPort* self) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlConjReplPort", "goDownOneFloor")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PMotorControl_IN_goDownOneFloor, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PMotorControlConjReplPort_goDownOneFloor(const PMotorControlConjReplPort* self, int idx__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PMotorControlConjReplPort", "goDownOneFloor")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PMotorControl_IN_goDownOneFloor, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

etInt32 PMotorControlConjReplPort_getReplication(const PMotorControlConjReplPort* self) {
	return ((etReplPort*)self)->size;
}



