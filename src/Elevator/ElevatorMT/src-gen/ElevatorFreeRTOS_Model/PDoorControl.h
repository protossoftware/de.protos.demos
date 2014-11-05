/**
 * @author generated by eTrice
 *
 * Header File of ProtocolClass PDoorControl
 * 
 */

#ifndef _ELEVATORFREERTOS_MODEL_PDOORCONTROL_H_
#define _ELEVATORFREERTOS_MODEL_PDOORCONTROL_H_

#include "etDatatypes.h"
#include "modelbase/etPort.h"




/* message IDs */
enum PDoorControl_msg_ids {
	PDoorControl_MSG_MIN = 0,
	PDoorControl_OUT_done = 1,
	PDoorControl_IN_setFloor = 2,
	PDoorControl_IN_open = 3,
	PDoorControl_IN_close = 4,
	PDoorControl_MSG_MAX = 5
};

/*--------------------- port structs and methods */
typedef etPort PDoorControlPort;
typedef etReplPort PDoorControlReplPort;


void PDoorControlPort_done(const PDoorControlPort* self);
void PDoorControlReplPort_done_broadcast(const PDoorControlReplPort* self);
void PDoorControlReplPort_done(const PDoorControlReplPort* self, int idx);


etInt32 PDoorControlReplPort_getReplication(const PDoorControlReplPort* self);
typedef etPort PDoorControlConjPort;
typedef etReplPort PDoorControlConjReplPort;


void PDoorControlConjPort_setFloor(const PDoorControlConjPort* self, uint8 data);
void PDoorControlConjReplPort_setFloor_broadcast(const PDoorControlConjReplPort* self, uint8 data);
void PDoorControlConjReplPort_setFloor(const PDoorControlConjReplPort* self, int idx, uint8 data);
void PDoorControlConjPort_open(const PDoorControlConjPort* self);
void PDoorControlConjReplPort_open_broadcast(const PDoorControlConjReplPort* self);
void PDoorControlConjReplPort_open(const PDoorControlConjReplPort* self, int idx);
void PDoorControlConjPort_close(const PDoorControlConjPort* self);
void PDoorControlConjReplPort_close_broadcast(const PDoorControlConjReplPort* self);
void PDoorControlConjReplPort_close(const PDoorControlConjReplPort* self, int idx);


etInt32 PDoorControlConjReplPort_getReplication(const PDoorControlConjReplPort* self);



#endif /* _ELEVATORFREERTOS_MODEL_PDOORCONTROL_H_ */

