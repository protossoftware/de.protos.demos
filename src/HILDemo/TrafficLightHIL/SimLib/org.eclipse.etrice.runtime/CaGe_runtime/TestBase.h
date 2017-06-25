
#ifndef _SRC_BASETESTACTOR_H_
#define _SRC_BASETESTACTOR_H_

#include <stdint.h>
#include <stdbool.h>
#include "../CaGe_runtime/FixedSizedStack.h"

//#define TDEBUG(x)   { x; }
#define TDEBUG(x)    { if (0) { x; } }

typedef enum {
	STEP_NA, STEP_CONTINUE, STEP_WAIT, STEP_FINISHED, STEP_FAILED, STEP_ERROR
} StepReturn;

typedef struct TestContext TestContext;
typedef struct TestStack TestStack;

typedef StepReturn (*StepFunction)(TestStack* stack, void* sut, const void* reaction);

typedef void (*TimeoutCallback)(void* sut, const TestStack* timeoutStack, const TestStack* lastStack, const char* lastLoc, int lastLine);

typedef struct {
	const char* name;
	StepFunction function;
	uint32_t timeout;
	TimeoutCallback timeoutCb;
	void* data;
} UserStack;

struct TestStack {
	int16_t blockID;
	TestStack* next;
	TestContext* context;
	UserStack user;
};

typedef enum {
	TESTEXCEPT_None, TESTEXCEPT_OutOfMemory, TESTEXCEPT_MaxLoopCount
} TestException;

struct TestContext {
	// init args
	FixedSizedStack* fss_test;
	FixedSizedStack* fss_userData;
	const char* modelURI;
	// state variables
	bool isFinished;
	bool hasException;
	TestException exception;
	TestStack* firstStack;
	uint32_t waitTime;
	char lastSourceLoc[100];
	int lastSourceLine;
};

void TestContext_init(TestContext* context, const char* modelURI, FixedSizedStack* testStack, FixedSizedStack* userStack);

void TestStack_print(const TestStack* stack, const char* msgType, const char* lastLoc, int line, const char* format, ...);
void TestStack_printTimeout(const TestStack* timeoutStack, const TestStack* lastStack, const char* lastLoc, int lastLine);

TestStack* TestContext_push(TestContext* context, const char* name, StepFunction function);
void* TestStack_allocData(TestStack* current, size_t userDataSize);
void* TestStack_getData(const TestStack* stack);
void TestStack_setTimeout(TestStack* stack, uint32_t timeMS, TimeoutCallback callback);
void TestStack_setWaitTime(TestStack* stack, uint32_t timeMS, const char* sourceLoc, int sourceLine);

void TestContext_run(TestContext* context, uint32_t currentTime, void* sut, const void* reaction);

#endif /* _SRC_BASETESTACTOR_H_ */
