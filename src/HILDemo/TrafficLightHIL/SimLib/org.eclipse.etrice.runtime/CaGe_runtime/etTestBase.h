
#ifndef _SRC_ETTESTCOMPARE_H_
#define _SRC_ETTESTCOMPARE_H_

#include "modelbase/etPort.h"
#include "etUnit/etUnit.h"
#include <assert.h>

static uint32_t getCurrentTime() {
	etTime currentTime;
	getTimeFromTarget(&currentTime);

	assert(currentTime.sec >= 0 && currentTime.nSec >= 0);

	return (uint32_t) (currentTime.sec * 1000 + currentTime.nSec / 1000000);
}

typedef const void* generic_data;

typedef struct {
	const etPort* port;
	etInt16 evtID;
	generic_data data;
} Reaction_etMessage;

static bool isExpected_reaction(const Reaction_etMessage* expected, const Reaction_etMessage* actual){
	assert(expected);
	return actual && expected->port == actual->port && expected->evtID == actual->evtID;
}

#endif /* _SRC_ETTESTCOMPARE_H_ */
