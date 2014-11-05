/**
 * @author generated by eTrice
 *
 * Source File of ProtocolClass PCabineControl
 * 
 */

#include "PCabineControl.h"
#include "debugging/etMSCLogger.h"
#include "PCabineControl_Utils.h"


/*--------------------- port methods */

void PCabineControlPort_floorRequest(const PCabineControlPort* self, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlPort", "floorRequest")
		etPort_sendMessage(self, PCabineControl_OUT_floorRequest, sizeof(uint8), &data__et);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlReplPort_floorRequest_broadcast(const PCabineControlReplPort* self, uint8 data__et) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlReplPort", "floorRequest")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_OUT_floorRequest, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlReplPort_floorRequest(const PCabineControlReplPort* self, int idx__et, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlReplPort", "floorRequest")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_OUT_floorRequest, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCabineControlPort_doorRequest(const PCabineControlPort* self) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlPort", "doorRequest")
		etPort_sendMessage(self, PCabineControl_OUT_doorRequest, 0, NULL);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlReplPort_doorRequest_broadcast(const PCabineControlReplPort* self) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlReplPort", "doorRequest")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_OUT_doorRequest, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlReplPort_doorRequest(const PCabineControlReplPort* self, int idx__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlReplPort", "doorRequest")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_OUT_doorRequest, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCabineControlPort_done(const PCabineControlPort* self) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlPort", "done")
		etPort_sendMessage(self, PCabineControl_OUT_done, 0, NULL);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlReplPort_done_broadcast(const PCabineControlReplPort* self) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlReplPort", "done")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_OUT_done, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlReplPort_done(const PCabineControlReplPort* self, int idx__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlReplPort", "done")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_OUT_done, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

etInt32 PCabineControlReplPort_getReplication(const PCabineControlReplPort* self) {
	return ((etReplPort*)self)->size;
}



void PCabineControlConjPort_set7seg(const PCabineControlConjPort* self, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjPort", "set7seg")
		etPort_sendMessage(self, PCabineControl_IN_set7seg, sizeof(uint8), &data__et);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_set7seg_broadcast(const PCabineControlConjReplPort* self, uint8 data__et) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "set7seg")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_IN_set7seg, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_set7seg(const PCabineControlConjReplPort* self, int idx__et, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "set7seg")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_IN_set7seg, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCabineControlConjPort_openDoor(const PCabineControlConjPort* self) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjPort", "openDoor")
		etPort_sendMessage(self, PCabineControl_IN_openDoor, 0, NULL);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_openDoor_broadcast(const PCabineControlConjReplPort* self) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "openDoor")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_IN_openDoor, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_openDoor(const PCabineControlConjReplPort* self, int idx__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "openDoor")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_IN_openDoor, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCabineControlConjPort_closeDoor(const PCabineControlConjPort* self) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjPort", "closeDoor")
		etPort_sendMessage(self, PCabineControl_IN_closeDoor, 0, NULL);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_closeDoor_broadcast(const PCabineControlConjReplPort* self) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "closeDoor")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_IN_closeDoor, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_closeDoor(const PCabineControlConjReplPort* self, int idx__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "closeDoor")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_IN_closeDoor, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCabineControlConjPort_floorRequestAck(const PCabineControlConjPort* self, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjPort", "floorRequestAck")
		etPort_sendMessage(self, PCabineControl_IN_floorRequestAck, sizeof(uint8), &data__et);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_floorRequestAck_broadcast(const PCabineControlConjReplPort* self, uint8 data__et) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "floorRequestAck")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_IN_floorRequestAck, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_floorRequestAck(const PCabineControlConjReplPort* self, int idx__et, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "floorRequestAck")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_IN_floorRequestAck, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCabineControlConjPort_floorRequestClear(const PCabineControlConjPort* self, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjPort", "floorRequestClear")
		etPort_sendMessage(self, PCabineControl_IN_floorRequestClear, sizeof(uint8), &data__et);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_floorRequestClear_broadcast(const PCabineControlConjReplPort* self, uint8 data__et) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "floorRequestClear")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_IN_floorRequestClear, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_floorRequestClear(const PCabineControlConjReplPort* self, int idx__et, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "floorRequestClear")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_IN_floorRequestClear, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCabineControlConjPort_startIndicateFloors(const PCabineControlConjPort* self, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjPort", "startIndicateFloors")
		etPort_sendMessage(self, PCabineControl_IN_startIndicateFloors, sizeof(uint8), &data__et);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_startIndicateFloors_broadcast(const PCabineControlConjReplPort* self, uint8 data__et) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "startIndicateFloors")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_IN_startIndicateFloors, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_startIndicateFloors(const PCabineControlConjReplPort* self, int idx__et, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "startIndicateFloors")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_IN_startIndicateFloors, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCabineControlConjPort_stopIndicateFloors(const PCabineControlConjPort* self) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjPort", "stopIndicateFloors")
		etPort_sendMessage(self, PCabineControl_IN_stopIndicateFloors, 0, NULL);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_stopIndicateFloors_broadcast(const PCabineControlConjReplPort* self) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "stopIndicateFloors")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCabineControl_IN_stopIndicateFloors, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCabineControlConjReplPort_stopIndicateFloors(const PCabineControlConjReplPort* self, int idx__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCabineControlConjReplPort", "stopIndicateFloors")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCabineControl_IN_stopIndicateFloors, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

etInt32 PCabineControlConjReplPort_getReplication(const PCabineControlConjReplPort* self) {
	return ((etReplPort*)self)->size;
}



