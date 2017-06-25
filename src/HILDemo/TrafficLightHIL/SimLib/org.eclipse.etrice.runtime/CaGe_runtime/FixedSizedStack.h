
#ifndef CAGE_RUNTIME_FIXEDSIZEDSTACK_H_
#define CAGE_RUNTIME_FIXEDSIZEDSTACK_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef char FixedSizedStack;
typedef void (FSStack_finalize)(void* data);
typedef void* FSS_Data;

bool FSStack_init(FixedSizedStack* self, size_t byteSize);
void FSStack_clear(FixedSizedStack* self);

FSS_Data FSStack_push(FixedSizedStack* self, size_t byteSize);
FSS_Data FSStack_push2(FixedSizedStack* self, size_t byteSize, FSStack_finalize finalize);

bool FSStack_pop(FixedSizedStack* self);
bool FSStack_popAll(FixedSizedStack* self, size_t count);

FSS_Data FSStack_peek(const FixedSizedStack* self);
FSS_Data FSStack_previous(const FixedSizedStack* self, FSS_Data data);

size_t FSStack_size(const FixedSizedStack* self);
bool FSStack_empty(const FixedSizedStack* self);


#endif /* CAGE_RUNTIME_FIXEDSIZEDSTACK_H_ */
