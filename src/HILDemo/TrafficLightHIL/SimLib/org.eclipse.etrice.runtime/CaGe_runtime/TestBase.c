
#include "../CaGe_runtime/TestBase.h"

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

static const char* URL_PREFIX = "http://localhost:34567/?command=de.protos.ewi.openmodel&uri=";
static const char* STEP_RETURN_NAMES[] = { "STEP_NA", "STEP_CONTINUE", "STEP_WAIT", "STEP_FINISHED", "STEP_FAILED", "STEP_ERROR" };

static TestStack* TestContext_getLastStack(TestContext* context) {
	return (TestStack*) FSStack_peek(context->fss_test);
}

static void TestContext_resetTo(TestContext* context, TestStack* newHead, void* sut) {
	for(TestStack* stack = TestContext_getLastStack(context); stack != newHead; stack = TestContext_getLastStack(context)){
		assert(stack);
		stack->next = NULL;
		stack->blockID = -1;
		assert(stack->user.function);
		(void) stack->user.function(stack, sut, NULL);

		if(stack->user.data && !FSStack_pop(context->fss_userData)) { assert(false); }
		if(!FSStack_pop(context->fss_test)) { assert(false); }
	}

	if(newHead){
		newHead->next = NULL;
	} else {
		context->firstStack = NULL;
	}
	context->lastSourceLoc[0] = '\0';
	context->lastSourceLine = -1;
}

static void TestContext_setException(TestContext* context, TestException exception) {
	switch (exception) {
	case TESTEXCEPT_OutOfMemory:
		printf("EXCEPTION:  OutOfMemory -> increase stack size\n"); fflush(stdout);
		break;
	case TESTEXCEPT_MaxLoopCount:
		printf("EXCEPTION:  MaxLoopCount -> test loop seems to be endless\n"); fflush(stdout);
		break;
	case TESTEXCEPT_None:
		break;
	default: assert(false);
	}

	context->exception = exception;
	context->hasException = context->exception != TESTEXCEPT_None;
	context->isFinished |= context->hasException;
}

static TestStack* TestStack_createStack(TestContext* context){
	assert(context && context->fss_test);
	TestStack* stack = FSStack_push(context->fss_test, sizeof(TestStack));
	if(stack) {
		stack->blockID = 0;
		stack->next = NULL;
		stack->context = context;
		stack->user.name = "unnamed";
		stack->user.function = NULL;
		stack->user.timeout = 0U;
		stack->user.timeoutCb = NULL;
		stack->user.data = NULL;
	} else {
		TestContext_setException(context, TESTEXCEPT_OutOfMemory);
	}

	return stack;
}

void TestContext_init(TestContext* context, const char* modelURI, FixedSizedStack* testStack, FixedSizedStack* userStack) {
	assert(context && testStack && userStack);

	context->modelURI = modelURI;
	FSStack_clear(testStack);
	context->fss_test = testStack;
	FSStack_clear(userStack);
	context->fss_userData = userStack;

	context->isFinished = false;
	TestContext_setException(context, TESTEXCEPT_None);
	context->waitTime = 0U;
	context->firstStack = NULL;
	context->lastSourceLoc[0] = '\0';
	context->lastSourceLine = -1;
}

TestStack* TestContext_push(TestContext* context, const char* name, StepFunction function) {
	assert(context);
	TestStack* lastStack = TestContext_getLastStack(context);
	TestStack* stack = TestStack_createStack(context);
	if(stack) {
		stack->user.name = name;
		stack->user.function = function;

		if(lastStack) {
			lastStack->next = stack;
		} else {
			assert(!context->firstStack);
			context->firstStack = stack;
		}
	}

	return stack;
}

void* TestStack_allocData(TestStack* stack, size_t userDataSize) {
	assert(stack && userDataSize > 0 && !stack->user.data);
	if(!(stack->user.data = FSStack_push(stack->context->fss_userData, userDataSize))){
		TestContext_setException(stack->context, TESTEXCEPT_OutOfMemory);
	}

	return TestStack_getData(stack);
}

void* TestStack_getData(const TestStack* stack) {
	assert(stack);
	return (stack) ? stack->user.data : NULL;
}

void TestStack_setTimeout(TestStack* stack, uint32_t timeMS, TimeoutCallback callback) {
	assert(stack);
	stack->user.timeout = timeMS;
	stack->user.timeoutCb = callback;
}

void TestStack_setWaitTime(TestStack* stack, uint32_t timeMS, const char* sourceLoc, int sourceLine) {
	assert(stack);
	TestContext* context = stack->context;
	assert(context->waitTime == 0U);
	context->waitTime = timeMS;
	strcpy(context->lastSourceLoc, sourceLoc);
	context->lastSourceLine = sourceLine;
}

void sprintModelURL(char* buffer, const TestStack* stack) {
	sprintf(buffer + strlen(buffer), "%s%s/%s/%i/0", URL_PREFIX, stack->context->modelURI, stack->user.name, stack->blockID - 1);
}

static void printStack(TestContext* context, uint32_t currentTime, StepReturn stepReturn) {
	char buffer[2000];
	sprintf(buffer, "TRACE time:%u return:%s", currentTime, STEP_RETURN_NAMES[stepReturn]);
	for(TestStack* stack = context->firstStack; stack != NULL; stack = stack->next){
		sprintf(buffer + strlen(buffer), "\n  |     ");
		sprintf(buffer + strlen(buffer), "%s(", stack->user.name);
		sprintf(buffer + strlen(buffer), "blockID:%i", stack->blockID);
		if(stack->user.timeout > 0U){
			sprintf(buffer + strlen(buffer), ", timeout:%u", stack->user.timeout);
		}
		if(!stack->next && context->waitTime > 0U){
			sprintf(buffer + strlen(buffer), ", waitTime:%u", context->waitTime);
		}
		sprintf(buffer + strlen(buffer), ")");
		if(!stack->next){
			sprintf(buffer + strlen(buffer), "          ");
			sprintModelURL(buffer, stack);
		}
	}
	if(!context->firstStack) {
		sprintf(buffer + strlen(buffer), "\n  |     empty stack");
	}
	printf("%s\n", buffer);
	printf("  -\n");
	fflush(stdout);
}

void TestStack_print(const TestStack* stack, const char* msgType, const char* file, int line, const char* format, ...) {
	assert(stack);
	char buffer[1000];
	sprintf(buffer, "%s in %s:%i REASON ", msgType, stack->user.name, stack->blockID);

	va_list arglist;
	va_start(arglist, format);
	vsnprintf(buffer + strlen(buffer), 400, format, arglist);
	if(line > 0 && file) {
		sprintf(buffer + strlen(buffer), "    (%s:%i)", file, line);
	}

	printf("%s\n", buffer);
	fflush(stdout);
}

void TestStack_printTimeout(const TestStack* timeoutStack, const TestStack* lastStack, const char* lastFile, int lastLine) {
	char buffer[1000];

	sprintf(buffer, "FAILURE in %s:%i REASON timeout of %s", lastStack->user.name, lastStack->blockID, timeoutStack->user.name);
	if(lastLine > 0 && lastFile){
		sprintf(buffer + strlen(buffer), "    (%s:%i)", lastFile, lastLine);
	}

	printf("%s\n", buffer);
	fflush(stdout);
}

void TestContext_run(TestContext* context, uint32_t currentTime, void* sut, const void* reaction){
	assert(context);

	uint16_t loopCount = 0;
	bool continueLoop = !context->isFinished;
	while(continueLoop){
		TestStack* currentStack = NULL;
		StepReturn stepReturn = STEP_NA;

		if(++loopCount >= 10000){ // endless loop protection
			TestContext_setException(context, TESTEXCEPT_MaxLoopCount);
			stepReturn = STEP_FAILED;
		}

		// check timeouts
		assert(context->firstStack);
		for(TestStack* stack = context->firstStack; stack != NULL; stack = stack->next){
			if(stack->user.timeout > 0U && stack->user.timeout <= currentTime){
				if(stack->user.timeoutCb){
					stack->user.timeoutCb(sut, stack, TestContext_getLastStack(context), context->lastSourceLoc, context->lastSourceLine);
				}
				if(!currentStack) {
					currentStack = stack;
				}
				stepReturn = STEP_FAILED;
			}
		}

		if(!currentStack) {
			currentStack = TestContext_getLastStack(context);
			assert(currentStack);
		}

		// check wait time
		if(context->waitTime > 0U){
			if(stepReturn == STEP_NA && context->waitTime > currentTime){
				stepReturn = STEP_WAIT;
			} else {
				context->waitTime = 0U;
				currentStack->blockID++; // advance, assuming wait is last action of block
			}
		}

		if(stepReturn == STEP_NA){
			assert(currentStack->user.function);
			// provide current reaction only for first call
			stepReturn = currentStack->user.function(currentStack, sut, ((loopCount == 1) ? reaction : NULL));
			assert(currentStack); // user error

			if(context->hasException) {
				stepReturn = STEP_FAILED;
			}
		}

		switch(stepReturn){
			case STEP_CONTINUE:{
				// => continue
				currentStack->blockID++; // advance
				break;
			}
			case STEP_WAIT: {
				// => quit
				continueLoop = false;
				break;
			}
			case STEP_FINISHED: {
				if(currentStack == context->firstStack) {
					// - test finished
					TestContext_resetTo(context, NULL, sut);
					context->isFinished = true;
					continueLoop = false;
				}
				else {
					// - step or sequence finished => continue
					// invalidate stack and advance
					bool match = false;
					for(TestStack* stack = context->firstStack; stack != NULL && !match; stack = stack->next){
						if(stack->next == currentStack){
							TestContext_resetTo(context, stack, sut);
							match = true;
						}
					}
					assert(match);
				}
				break;
			}
			case STEP_ERROR:
			case STEP_FAILED: {
				printStack(context, currentTime, stepReturn);
				// - test finished
				TestContext_resetTo(context, NULL, sut);
				context->isFinished = true;
				continueLoop = false;
				break;
			}
			default: assert(false);
		}

		TDEBUG(if(stepReturn != STEP_ERROR && stepReturn != STEP_FAILED) { printStack(context, currentTime, stepReturn); });
	}

}

