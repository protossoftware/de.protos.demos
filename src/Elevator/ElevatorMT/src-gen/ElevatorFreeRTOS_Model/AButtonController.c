/**
 * @author generated by eTrice
 *
 * Source File of ActorClass AButtonController
 * 
 */

#include "AButtonController.h"

#include "modelbase/etActor.h"
#include "debugging/etLogger.h"
#include "debugging/etMSCLogger.h"
#include "etUnit/etUnit.h"
#include "base/etMemory.h"

#include "ElevatorFreeRTOS_Model/PButtonControl.h"
#include "room/basic/service/timing/PTimer.h"

#include "AButtonController_Utils.h"


/* interface item IDs */
enum interface_items {
	IFITEM_ControlPort = 1,
	IFITEM_timer = 2
};

/* state IDs */
enum state_ids {
	NO_STATE = 0,
	STATE_TOP = 1,
	STATE_released = 2,
	STATE_pressed = 3,
	STATE_MAX = 4
};

/* transition chains */
enum chain_ids {
	CHAIN_TRANS_tr1_FROM_released_TO_cp1_BY_timeouttimer = 1,
	CHAIN_TRANS_tr2_FROM_pressed_TO_cp0_BY_timeouttimer = 2,
	CHAIN_TRANS_tr7_FROM_tp0_TO_tp0_BY_setButtonIdControlPort_tr7 = 3,
	CHAIN_TRANS_tr8_FROM_tp0_TO_tp0_BY_setFloorControlPort_tr8 = 4,
	CHAIN_TRANS_INITIAL_TO__released = 5,
	CHAIN_TRANS_tr0_FROM_tp1_TO_tp1_BY_ledOnControlPort_tr0 = 6,
	CHAIN_TRANS_tr9_FROM_tp1_TO_tp1_BY_ledOffControlPort_tr9 = 7,
	CHAIN_TRANS_tr10_FROM_tp0_TO_tp0_BY_setLedIdControlPort_tr10 = 8,
	CHAIN_TRANS_tr11_FROM_tp1_TO_tp1_BY_ledToggleControlPort_tr11 = 9
};

/* triggers */
enum triggers {
	POLLING = 0,
	TRIG_ControlPort__setButtonId = IFITEM_ControlPort + EVT_SHIFT*PButtonControl_IN_setButtonId,
	TRIG_ControlPort__setLedId = IFITEM_ControlPort + EVT_SHIFT*PButtonControl_IN_setLedId,
	TRIG_ControlPort__setFloor = IFITEM_ControlPort + EVT_SHIFT*PButtonControl_IN_setFloor,
	TRIG_ControlPort__ledOn = IFITEM_ControlPort + EVT_SHIFT*PButtonControl_IN_ledOn,
	TRIG_ControlPort__ledOff = IFITEM_ControlPort + EVT_SHIFT*PButtonControl_IN_ledOff,
	TRIG_ControlPort__ledToggle = IFITEM_ControlPort + EVT_SHIFT*PButtonControl_IN_ledToggle,
	TRIG_timer__timeout = IFITEM_timer + EVT_SHIFT*PTimer_OUT_timeout
};


static void setState(AButtonController* self, etInt16 new_state) {
	self->state = new_state;
}

static etInt16 getState(AButtonController* self) {
	return self->state;
}

/* Entry and Exit Codes */

/* Action Codes */
static void action_TRANS_tr1_FROM_released_TO_cp1_BY_timeouttimer(AButtonController* self, const InterfaceItemBase* ifitem) {
	timer_startTimeout(50);
}
static void action_TRANS_tr4_FROM_cp1_TO_pressed_COND_tr4(AButtonController* self, const InterfaceItemBase* ifitem) {
	ControlPort_pressed();
}
static void action_TRANS_tr2_FROM_pressed_TO_cp0_BY_timeouttimer(AButtonController* self, const InterfaceItemBase* ifitem) {
	timer_startTimeout(50);
}
static void action_TRANS_tr6_FROM_cp0_TO_released_COND_tr6(AButtonController* self, const InterfaceItemBase* ifitem) {
	ControlPort_released();
}
static void action_TRANS_tr7_FROM_tp0_TO_tp0_BY_setButtonIdControlPort_tr7(AButtonController* self, const InterfaceItemBase* ifitem, uint8 data) {
	buttonId=data;
}
static void action_TRANS_tr8_FROM_tp0_TO_tp0_BY_setFloorControlPort_tr8(AButtonController* self, const InterfaceItemBase* ifitem, uint8 data) {
	floor=data;
}
static void action_TRANS_INITIAL_TO__released(AButtonController* self) {
	timer_startTimeout(50);
}
static void action_TRANS_tr0_FROM_tp1_TO_tp1_BY_ledOnControlPort_tr0(AButtonController* self, const InterfaceItemBase* ifitem) {
	writeToButtonLed(floor, ledId, ON);
}
static void action_TRANS_tr9_FROM_tp1_TO_tp1_BY_ledOffControlPort_tr9(AButtonController* self, const InterfaceItemBase* ifitem) {
	writeToButtonLed(floor, ledId, OFF);
}
static void action_TRANS_tr10_FROM_tp0_TO_tp0_BY_setLedIdControlPort_tr10(AButtonController* self, const InterfaceItemBase* ifitem, uint8 data) {
	ledId=data;
}
static void action_TRANS_tr5_FROM_cp0_TO_pressed(AButtonController* self, const InterfaceItemBase* ifitem) {
	repeatPressed();
}
static void action_TRANS_tr11_FROM_tp1_TO_tp1_BY_ledToggleControlPort_tr11(AButtonController* self, const InterfaceItemBase* ifitem) {
	writeToButtonLed(floor, ledId, TOGGLE);
}

/**
 * calls exit codes while exiting from the current state to one of its
 * parent states while remembering the history
 * @param current__et - the current state
 * @param to - the final parent state
 * @param handler__et - entry and exit codes are called only if not handler (for handler TransitionPoints)
 */
static void exitTo(AButtonController* self, etInt16 current__et, etInt16 to, boolean handler__et) {
	while (current__et!=to) {
		switch (current__et) {
			case STATE_released:
				self->history[STATE_TOP] = STATE_released;
				current__et = STATE_TOP;
				break;
			case STATE_pressed:
				self->history[STATE_TOP] = STATE_pressed;
				current__et = STATE_TOP;
				break;
			default:
				/* should not occur */
				break;
		}
	}
}

/**
 * calls action, entry and exit codes along a transition chain. The generic data are cast to typed data
 * matching the trigger of this chain. The ID of the final state is returned
 * @param chain__et - the chain ID
 * @param generic_data__et - the generic data pointer
 * @return the +/- ID of the final state either with a positive sign, that indicates to execute the state's entry code, or a negative sign vice versa
 */
static etInt16 executeTransitionChain(AButtonController* self, int chain__et, const InterfaceItemBase* ifitem, void* generic_data__et) {
	switch (chain__et) {
		case CHAIN_TRANS_tr1_FROM_released_TO_cp1_BY_timeouttimer:
		{
			action_TRANS_tr1_FROM_released_TO_cp1_BY_timeouttimer(self, ifitem);
			if (getButtonStatus(floor,buttonId)) {
			action_TRANS_tr4_FROM_cp1_TO_pressed_COND_tr4(self, ifitem);
			return STATE_pressed;}
			else {
			return STATE_released;}
		}
		case CHAIN_TRANS_tr2_FROM_pressed_TO_cp0_BY_timeouttimer:
		{
			action_TRANS_tr2_FROM_pressed_TO_cp0_BY_timeouttimer(self, ifitem);
			if (!getButtonStatus(floor,buttonId)) {
			action_TRANS_tr6_FROM_cp0_TO_released_COND_tr6(self, ifitem);
			return STATE_released;}
			else {
			action_TRANS_tr5_FROM_cp0_TO_pressed(self, ifitem);
			return STATE_pressed;}
		}
		case CHAIN_TRANS_tr7_FROM_tp0_TO_tp0_BY_setButtonIdControlPort_tr7:
		{
			uint8 data = *((uint8*) generic_data__et);
			action_TRANS_tr7_FROM_tp0_TO_tp0_BY_setButtonIdControlPort_tr7(self, ifitem, data);
			return STATE_TOP + STATE_MAX;
		}
		case CHAIN_TRANS_tr8_FROM_tp0_TO_tp0_BY_setFloorControlPort_tr8:
		{
			uint8 data = *((uint8*) generic_data__et);
			action_TRANS_tr8_FROM_tp0_TO_tp0_BY_setFloorControlPort_tr8(self, ifitem, data);
			return STATE_TOP + STATE_MAX;
		}
		case CHAIN_TRANS_INITIAL_TO__released:
		{
			action_TRANS_INITIAL_TO__released(self);
			return STATE_released;
		}
		case CHAIN_TRANS_tr0_FROM_tp1_TO_tp1_BY_ledOnControlPort_tr0:
		{
			action_TRANS_tr0_FROM_tp1_TO_tp1_BY_ledOnControlPort_tr0(self, ifitem);
			return STATE_TOP + STATE_MAX;
		}
		case CHAIN_TRANS_tr9_FROM_tp1_TO_tp1_BY_ledOffControlPort_tr9:
		{
			action_TRANS_tr9_FROM_tp1_TO_tp1_BY_ledOffControlPort_tr9(self, ifitem);
			return STATE_TOP + STATE_MAX;
		}
		case CHAIN_TRANS_tr10_FROM_tp0_TO_tp0_BY_setLedIdControlPort_tr10:
		{
			uint8 data = *((uint8*) generic_data__et);
			action_TRANS_tr10_FROM_tp0_TO_tp0_BY_setLedIdControlPort_tr10(self, ifitem, data);
			return STATE_TOP + STATE_MAX;
		}
		case CHAIN_TRANS_tr11_FROM_tp1_TO_tp1_BY_ledToggleControlPort_tr11:
		{
			action_TRANS_tr11_FROM_tp1_TO_tp1_BY_ledToggleControlPort_tr11(self, ifitem);
			return STATE_TOP + STATE_MAX;
		}
			default:
				/* should not occur */
				break;
	}
	return NO_STATE;
}

/**
 * calls entry codes while entering a state's history. The ID of the final leaf state is returned
 * @param state__et - the state which is entered
 * @param handler__et - entry code is executed if not handler
 * @return - the ID of the final leaf state
 */
static etInt16 enterHistory(AButtonController* self, etInt16 state__et, boolean handler__et) {
	boolean skip_entry__et = ET_FALSE;
	if (state__et >= STATE_MAX) {
		state__et = (etInt16) (state__et - STATE_MAX);
		skip_entry__et = ET_TRUE;
	}
	while (ET_TRUE) {
		switch (state__et) {
			case STATE_released:
				/* in leaf state: return state id */
				return STATE_released;
			case STATE_pressed:
				/* in leaf state: return state id */
				return STATE_pressed;
			case STATE_TOP:
				state__et = self->history[STATE_TOP];
				break;
			default:
				/* should not occur */
				break;
		}
		skip_entry__et = ET_FALSE;
	}
	/* return NO_STATE; // required by CDT but detected as unreachable by JDT because of while (true) */
}

static void AButtonController_executeInitTransition(AButtonController* self) {
	int chain__et = CHAIN_TRANS_INITIAL_TO__released;
	etInt16 next__et = executeTransitionChain(self, chain__et, NULL, NULL);
	next__et = enterHistory(self, next__et, ET_FALSE);
	setState(self, next__et);
}

/* receiveEvent contains the main implementation of the FSM */
static void AButtonController_receiveEvent(AButtonController* self, InterfaceItemBase* ifitem, int evt, void* generic_data__et) {
	int trigger__et = ifitem->localId + EVT_SHIFT*evt;
	int chain__et = NOT_CAUGHT;
	etInt16 catching_state__et = NO_STATE;
	boolean is_handler__et = ET_FALSE;
	((void)trigger__et);	/* avoids unused warning */
	
	if (!handleSystemEvent(ifitem, evt, generic_data__et)) {
		switch (getState(self)) {
			case STATE_released:
				switch(trigger__et) {
						case TRIG_timer__timeout:
							{
								chain__et = CHAIN_TRANS_tr1_FROM_released_TO_cp1_BY_timeouttimer;
								catching_state__et = STATE_TOP;
							}
						break;
						case TRIG_ControlPort__setButtonId:
							{
								chain__et = CHAIN_TRANS_tr7_FROM_tp0_TO_tp0_BY_setButtonIdControlPort_tr7;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__setFloor:
							{
								chain__et = CHAIN_TRANS_tr8_FROM_tp0_TO_tp0_BY_setFloorControlPort_tr8;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__setLedId:
							{
								chain__et = CHAIN_TRANS_tr10_FROM_tp0_TO_tp0_BY_setLedIdControlPort_tr10;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__ledOn:
							{
								chain__et = CHAIN_TRANS_tr0_FROM_tp1_TO_tp1_BY_ledOnControlPort_tr0;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__ledOff:
							{
								chain__et = CHAIN_TRANS_tr9_FROM_tp1_TO_tp1_BY_ledOffControlPort_tr9;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__ledToggle:
							{
								chain__et = CHAIN_TRANS_tr11_FROM_tp1_TO_tp1_BY_ledToggleControlPort_tr11;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						default:
							/* should not occur */
							break;
				}
				break;
			case STATE_pressed:
				switch(trigger__et) {
						case TRIG_timer__timeout:
							{
								chain__et = CHAIN_TRANS_tr2_FROM_pressed_TO_cp0_BY_timeouttimer;
								catching_state__et = STATE_TOP;
							}
						break;
						case TRIG_ControlPort__setButtonId:
							{
								chain__et = CHAIN_TRANS_tr7_FROM_tp0_TO_tp0_BY_setButtonIdControlPort_tr7;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__setFloor:
							{
								chain__et = CHAIN_TRANS_tr8_FROM_tp0_TO_tp0_BY_setFloorControlPort_tr8;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__setLedId:
							{
								chain__et = CHAIN_TRANS_tr10_FROM_tp0_TO_tp0_BY_setLedIdControlPort_tr10;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__ledOn:
							{
								chain__et = CHAIN_TRANS_tr0_FROM_tp1_TO_tp1_BY_ledOnControlPort_tr0;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__ledOff:
							{
								chain__et = CHAIN_TRANS_tr9_FROM_tp1_TO_tp1_BY_ledOffControlPort_tr9;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						case TRIG_ControlPort__ledToggle:
							{
								chain__et = CHAIN_TRANS_tr11_FROM_tp1_TO_tp1_BY_ledToggleControlPort_tr11;
								catching_state__et = STATE_TOP;
								is_handler__et = ET_TRUE;
							}
						break;
						default:
							/* should not occur */
							break;
				}
				break;
			default:
				/* should not occur */
				break;
		}
	}
	if (chain__et != NOT_CAUGHT) {
		exitTo(self, getState(self), catching_state__et, is_handler__et);
		{
			etInt16 next__et = executeTransitionChain(self, chain__et, ifitem, generic_data__et);
			next__et = enterHistory(self, next__et, is_handler__et);
			setState(self, next__et);
		}
	}
}

void AButtonController_init(AButtonController* self){
	ET_MSC_LOGGER_SYNC_ENTRY("AButtonController", "init")
	self->state = STATE_TOP;
	{
		int i;
		for (i=0; i<ABUTTONCONTROLLER_HISTORY_SIZE; ++i)
			self->history[i] = NO_STATE;
	}
	AButtonController_executeInitTransition(self);
	ET_MSC_LOGGER_SYNC_EXIT
}


void AButtonController_receiveMessage(void* self, const void* ifitem, const etMessage* msg){
	ET_MSC_LOGGER_SYNC_ENTRY("AButtonController", "_receiveMessage")
	
	AButtonController_receiveEvent(self, (etPort*)ifitem, msg->evtID, (void*)(((char*)msg)+MEM_CEIL(sizeof(etMessage))));
	
	ET_MSC_LOGGER_SYNC_EXIT
}


/*--------------------- operations ---------------------*/
void AButtonController_repeatPressed(AButtonController* self) {
	/*do nothing*/
}

