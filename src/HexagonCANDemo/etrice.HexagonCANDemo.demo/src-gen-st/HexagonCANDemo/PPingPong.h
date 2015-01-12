/**
 * @author generated by eTrice
 *
 * Header File of ProtocolClass PPingPong
 * 
 */

#ifndef _HEXAGONCANDEMO_PPINGPONG_H_
#define _HEXAGONCANDEMO_PPINGPONG_H_

#include "etDatatypes.h"
#include "modelbase/etPort.h"




/* message IDs */
enum PPingPong_msg_ids {
	PPingPong_MSG_MIN = 0,
	PPingPong_OUT_pong = 1,
	PPingPong_IN_ping = 2,
	PPingPong_MSG_MAX = 3
};

/*--------------------- port structs and methods */
typedef etPort PPingPongPort;
typedef etReplPort PPingPongReplPort;


void PPingPongPort_pong(const PPingPongPort* self);
void PPingPongReplPort_pong_broadcast(const PPingPongReplPort* self);
void PPingPongReplPort_pong(const PPingPongReplPort* self, int idx);


etInt32 PPingPongReplPort_getReplication(const PPingPongReplPort* self);
typedef etPort PPingPongConjPort;
typedef etReplPort PPingPongConjReplPort;


void PPingPongConjPort_ping(const PPingPongConjPort* self);
void PPingPongConjReplPort_ping_broadcast(const PPingPongConjReplPort* self);
void PPingPongConjReplPort_ping(const PPingPongConjReplPort* self, int idx);


etInt32 PPingPongConjReplPort_getReplication(const PPingPongConjReplPort* self);



#endif /* _HEXAGONCANDEMO_PPINGPONG_H_ */

