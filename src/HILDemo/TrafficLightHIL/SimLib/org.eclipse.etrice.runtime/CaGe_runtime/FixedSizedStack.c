#include "../CaGe_runtime/FixedSizedStack.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

typedef struct {
	size_t nSize;
	char* head;
	char* start;
	const char* end;
} FSStack;

typedef struct {
	size_t entrySize;
	FSStack_finalize* finalize;
} FSStackEntry;

static void FSS_assertIntegrity(const FSStack* self) {
	assert(self->start && self->end && (uintptr_t ) self->start <= (uintptr_t ) self->end);
	assert(self->nSize != 0 || self->head == self->end);
}


bool FSStack_init(FixedSizedStack* self, size_t byteSize) {
	assert(self && byteSize > 0);

	if(sizeof(FSStack) > byteSize){
		return false;
	}

	FSStack* stack = (FSStack*) self;
	stack->nSize = 0U;
	stack->start = (char*) self + sizeof(FSStack);
	stack->head = (char*) self + byteSize;
	stack->end = stack->head;
	memset(stack->start, 0, (uintptr_t) stack->end - (uintptr_t) stack->start);

	FSS_assertIntegrity(stack);
	return true;
}

void FSStack_clear(FixedSizedStack* self) {
	assert(self);

	FSStack* stack = (FSStack*) self;
	if(!FSStack_popAll(self, FSStack_size(self))) { assert(false); }
}

FSS_Data FSStack_push(FixedSizedStack* self, size_t byteSize) {
	return FSStack_push2(self, byteSize, NULL);
}

FSS_Data FSStack_push2(FixedSizedStack* self, size_t byteSize, FSStack_finalize finalize) {
	assert(self && byteSize > 0);

	FSStack* stack = (FSStack*) self;
	FSS_assertIntegrity(stack);

	size_t entrySize = sizeof(FSStackEntry) + byteSize;
	if (stack->head - entrySize < stack->start) {
		return NULL;
	}

	stack->nSize++;
	stack->head -= entrySize;

	FSStackEntry* newEntry = (FSStackEntry*) stack->head;
	newEntry->entrySize = entrySize;
	newEntry->finalize = finalize;

	FSS_assertIntegrity(stack);
	return FSStack_peek(self);
}

bool FSStack_pop(FixedSizedStack* self) {
	assert(self);

	FSStack* stack = (FSStack*) self;
	FSS_assertIntegrity(stack);

	bool changed = false;
	if (stack->nSize > 0) {
		FSStackEntry* head = (FSStackEntry*) stack->head;
		if (head->finalize) {
			head->finalize(FSStack_peek(self));
		}

		stack->nSize--;
		stack->head += head->entrySize;
		memset(stack->start, 0, (uintptr_t) stack->head - (uintptr_t) stack->start);

		changed = true;
	}

	FSS_assertIntegrity(stack);
	return changed;
}

bool FSStack_popAll(FixedSizedStack* self, size_t count) {
	bool allChanged = true;
	for (size_t i = 0; i < count; i++) {
		allChanged &= FSStack_pop(self);
	}

	return allChanged;
}

FSS_Data FSStack_peek(const FixedSizedStack* self) {
	assert(self);

	const FSStack* stack = (FSStack*) self;
	FSS_assertIntegrity(stack);
	if(stack->nSize > 0) {
		return (FSS_Data) (stack->head + sizeof(FSStackEntry));
	}

	return NULL;
}

FSS_Data FSStack_previous(const FixedSizedStack* self, FSS_Data data) {
	assert(self && data);

	const FSStackEntry* entry = (FSStackEntry*) ((char*) data) - sizeof(FSStackEntry);
	char* previous = ((char*) entry) + entry->entrySize;

	return (previous >= ((FSStack*) self)->end) ? NULL : previous;
}

size_t FSStack_size(const FixedSizedStack* self) {
	assert(self);
	return ((const FSStack*) self)->nSize;
}

bool FSStack_empty(const FixedSizedStack* self) {
	assert(self);
	return ((const FSStack*) self)->nSize > 0;
}
