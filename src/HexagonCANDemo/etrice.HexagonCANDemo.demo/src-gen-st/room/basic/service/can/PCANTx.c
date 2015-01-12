/**
 * @author generated by eTrice
 *
 * Source File of ProtocolClass PCANTx
 * 
 */

#include "PCANTx.h"
#include "debugging/etMSCLogger.h"
#include "PCANTx_Utils.h"


/*--------------------- port methods */

void PCANTxPort_valueChanged(const PCANTxPort* self, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxPort", "valueChanged")
		etPort_sendMessage(self, PCANTx_OUT_valueChanged, sizeof(uint8), &data__et);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCANTxReplPort_valueChanged_broadcast(const PCANTxReplPort* self, uint8 data__et) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxReplPort", "valueChanged")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCANTx_OUT_valueChanged, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCANTxReplPort_valueChanged(const PCANTxReplPort* self, int idx__et, uint8 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxReplPort", "valueChanged")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCANTx_OUT_valueChanged, sizeof(uint8), &data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

etInt32 PCANTxReplPort_getReplication(const PCANTxReplPort* self) {
	return ((etReplPort*)self)->size;
}



void PCANTxConjPort_init(const PCANTxConjPort* self, uint32 data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxConjPort", "init")
	if(data__et != ET_CAN_CHANNEL_NOT_DEFINED) pChannel=data__et;
	etPort_sendMessage(self, PCANTx_IN_init, sizeof(uint32), &pChannel);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCANTxConjReplPort_init_broadcast(const PCANTxConjReplPort* self, uint32 data__et) {
	int i;
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		PCANTxConjPort_init(&((etReplPort*)self)->ports[i].port, data__et);
	}					
}

void PCANTxConjReplPort_init(const PCANTxConjReplPort* self, int idx__et, uint32 data__et) {
	PCANTxConjPort_init(&((etReplPort*)self)->ports[idx__et].port, data__et);
}


void PCANTxConjPort_sendMsg(const PCANTxConjPort* self, pclCANMsg* data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxConjPort", "sendMsg")
		etPort_sendMessage(self, PCANTx_IN_sendMsg, sizeof(pclCANMsg), data__et);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCANTxConjReplPort_sendMsg_broadcast(const PCANTxConjReplPort* self, pclCANMsg* data__et) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxConjReplPort", "sendMsg")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCANTx_IN_sendMsg, sizeof(pclCANMsg), data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCANTxConjReplPort_sendMsg(const PCANTxConjReplPort* self, int idx__et, pclCANMsg* data__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxConjReplPort", "sendMsg")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCANTx_IN_sendMsg, sizeof(pclCANMsg), data__et);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}


void PCANTxConjPort_resendMsg(const PCANTxConjPort* self) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxConjPort", "resendMsg")
		etPort_sendMessage(self, PCANTx_IN_resendMsg, 0, NULL);
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCANTxConjReplPort_resendMsg_broadcast(const PCANTxConjReplPort* self) {
	int i;
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxConjReplPort", "resendMsg")
	for (i=0; i<((etReplPort*)self)->size; ++i) {
		etPort_sendMessage((&((etReplPort*)self)->ports[i].port), PCANTx_IN_resendMsg, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

void PCANTxConjReplPort_resendMsg(const PCANTxConjReplPort* self, int idx__et) {
	ET_MSC_LOGGER_SYNC_ENTRY("PCANTxConjReplPort", "resendMsg")
	if (0<=idx__et && idx__et<((etReplPort*)self)->size) {
		etPort_sendMessage((&((etReplPort*)self)->ports[idx__et].port), PCANTx_IN_resendMsg, 0, NULL);
	}
	ET_MSC_LOGGER_SYNC_EXIT
}

/* begin PCANTxConjPort specific */

/*--------------------- operations ---------------------*/
/* end PCANTxConjPort specific */

etInt32 PCANTxConjReplPort_getReplication(const PCANTxConjReplPort* self) {
	return ((etReplPort*)self)->size;
}



