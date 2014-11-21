package Actuators;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import AutomationProtocols.*;
import protos.automation.service.io.*;
import room.basic.service.timing.*;
import protos.automation.service.io.PDigIn.*;
import protos.automation.service.io.PDigOut.*;
import AutomationProtocols.PDriveLR.*;
import AutomationProtocols.PLinearUnit.*;
import room.basic.service.timing.PTimer.*;
import AutomationProtocols.PTransport.*;



public class Pusher extends ActorClassBase {

	
	//--------------------- ports
	protected PTransportPort fct = null;
	protected PLinearUnitConjPort pusher = null;
	
	//--------------------- saps
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_fct = 2;
	public static final int IFITEM_pusher = 1;
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public Pusher(IRTObject parent, String name) {
		super(parent, name);
		setClassName("Pusher");
		
		// initialize attributes

		// own ports
		fct = new PTransportPort(this, "fct", IFITEM_fct);
		pusher = new PLinearUnitConjPort(this, "pusher", IFITEM_pusher);
		
		// own saps
		
		// own service implementations
		
		// sub actors
		DebuggingService.getInstance().addMessageActorCreate(this, "PusherHW");
		new LinearUnit(this, "PusherHW");
		
		// wiring
		InterfaceItemBase.connect(this, "PusherHW/fct", "pusher");
		
		

	}
	
	/* --------------------- attribute setters and getters */
	
	
	//--------------------- port getters
	public PTransportPort getFct (){
		return this.fct;
	}
	public PLinearUnitConjPort getPusher (){
		return this.pusher;
	}

	//--------------------- lifecycle functions
	public void stop(){
		stopUser();
		super.stop();
	}
	
	public void destroy() {
		DebuggingService.getInstance().addMessageActorDestroy(this);
		super.destroy();
	}

	/* state IDs */
	public static final int STATE_Initializing = 2;
	public static final int STATE_Running = 3;
	public static final int STATE_Initializing_Forewards = 4;
	public static final int STATE_Initializing_Backwards = 5;
	public static final int STATE_Running_Empty = 6;
	public static final int STATE_Running_Forewards = 7;
	public static final int STATE_Running_Backwards = 8;
	public static final int STATE_Running_Full = 9;
	public static final int STATE_MAX = 10;
	
	/* transition chains */
	public static final int CHAIN_Initializing_TRANS_tr5_FROM_Forewards_TO_Backwards_BY_doneMoveForwardpusher = 1;
	public static final int CHAIN_Initializing_TRANS_tr8_FROM_Backwards_TO_running_BY_doneMoveBackwardpusher = 2;
	public static final int CHAIN_Running_TRANS_tr0_FROM_Forewards_TO_Backwards_BY_doneMoveForwardpusher = 3;
	public static final int CHAIN_Running_TRANS_tr1_FROM_Backwards_TO_Empty_BY_doneMoveBackwardpusher = 4;
	public static final int CHAIN_Running_TRANS_tr2_FROM_Empty_TO_Full_BY_takePartfct = 5;
	public static final int CHAIN_Running_TRANS_tr3_FROM_Full_TO_Forewards_BY_releasePartfct = 6;
	public static final int CHAIN_Running_TRANS_tr6_FROM_Empty_TO_Empty_BY_getStatusfct_tr6 = 7;
	public static final int CHAIN_Running_TRANS_tr7_FROM_Full_TO_Full_BY_getStatusfct_tr7 = 8;
	public static final int CHAIN_TRANS_INITIAL_TO__Initializing_init = 9;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_pusher__doneMoveForward = IFITEM_pusher + EVT_SHIFT*PLinearUnit.OUT_doneMoveForward;
	public static final int TRIG_pusher__doneMoveBackward = IFITEM_pusher + EVT_SHIFT*PLinearUnit.OUT_doneMoveBackward;
	public static final int TRIG_fct__getStatus = IFITEM_fct + EVT_SHIFT*PTransport.IN_getStatus;
	public static final int TRIG_fct__releasePart = IFITEM_fct + EVT_SHIFT*PTransport.IN_releasePart;
	public static final int TRIG_fct__takePart = IFITEM_fct + EVT_SHIFT*PTransport.IN_takePart;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"Initializing",
		"Running",
		"Initializing_Forewards",
		"Initializing_Backwards",
		"Running_Empty",
		"Running_Forewards",
		"Running_Backwards",
		"Running_Full"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	protected void entry_Initializing_Forewards() {
		pusher.moveForward();
	}
	protected void entry_Initializing_Backwards() {
		pusher.moveBackward();
	}
	protected void entry_Running_Empty() {
		fct.isEmpty();
	}
	protected void entry_Running_Forewards() {
		pusher.moveForward();
	}
	protected void entry_Running_Backwards() {
		pusher.moveBackward();
	}
	protected void entry_Running_Full() {
		fct.takePartDone();
		fct.isFull();
	}
	
	/* Action Codes */
	protected void action_Running_TRANS_tr3_FROM_Full_TO_Forewards_BY_releasePartfct(InterfaceItemBase ifitem) {
		fct.releasePartDone();
	}
	
	/**
	 * calls exit codes while exiting from the current state to one of its
	 * parent states while remembering the history
	 * @param current__et - the current state
	 * @param to - the final parent state
	 */
	private void exitTo(int current__et, int to) {
		while (current__et!=to) {
			switch (current__et) {
				case STATE_Initializing:
					this.history[STATE_TOP] = STATE_Initializing;
					current__et = STATE_TOP;
					break;
				case STATE_Initializing_Forewards:
					this.history[STATE_Initializing] = STATE_Initializing_Forewards;
					current__et = STATE_Initializing;
					break;
				case STATE_Initializing_Backwards:
					this.history[STATE_Initializing] = STATE_Initializing_Backwards;
					current__et = STATE_Initializing;
					break;
				case STATE_Running:
					this.history[STATE_TOP] = STATE_Running;
					current__et = STATE_TOP;
					break;
				case STATE_Running_Empty:
					this.history[STATE_Running] = STATE_Running_Empty;
					current__et = STATE_Running;
					break;
				case STATE_Running_Forewards:
					this.history[STATE_Running] = STATE_Running_Forewards;
					current__et = STATE_Running;
					break;
				case STATE_Running_Backwards:
					this.history[STATE_Running] = STATE_Running_Backwards;
					current__et = STATE_Running;
					break;
				case STATE_Running_Full:
					this.history[STATE_Running] = STATE_Running_Full;
					current__et = STATE_Running;
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
	private int executeTransitionChain(int chain__et, InterfaceItemBase ifitem, Object generic_data__et) {
		switch (chain__et) {
			case CHAIN_TRANS_INITIAL_TO__Initializing_init:
			{
				return STATE_Initializing_Forewards;
			}
			case CHAIN_Initializing_TRANS_tr5_FROM_Forewards_TO_Backwards_BY_doneMoveForwardpusher:
			{
				return STATE_Initializing_Backwards;
			}
			case CHAIN_Initializing_TRANS_tr8_FROM_Backwards_TO_running_BY_doneMoveBackwardpusher:
			{
				return STATE_Running_Empty;
			}
			case CHAIN_Running_TRANS_tr0_FROM_Forewards_TO_Backwards_BY_doneMoveForwardpusher:
			{
				return STATE_Running_Backwards;
			}
			case CHAIN_Running_TRANS_tr1_FROM_Backwards_TO_Empty_BY_doneMoveBackwardpusher:
			{
				return STATE_Running_Empty;
			}
			case CHAIN_Running_TRANS_tr2_FROM_Empty_TO_Full_BY_takePartfct:
			{
				return STATE_Running_Full;
			}
			case CHAIN_Running_TRANS_tr3_FROM_Full_TO_Forewards_BY_releasePartfct:
			{
				action_Running_TRANS_tr3_FROM_Full_TO_Forewards_BY_releasePartfct(ifitem);
				return STATE_Running_Forewards;
			}
			case CHAIN_Running_TRANS_tr6_FROM_Empty_TO_Empty_BY_getStatusfct_tr6:
			{
				return STATE_Running_Empty;
			}
			case CHAIN_Running_TRANS_tr7_FROM_Full_TO_Full_BY_getStatusfct_tr7:
			{
				return STATE_Running_Full;
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
	 * @return - the ID of the final leaf state
	 */
	private int enterHistory(int state__et) {
		boolean skip_entry__et = false;
		if (state__et >= STATE_MAX) {
			state__et =  (state__et - STATE_MAX);
			skip_entry__et = true;
		}
		while (true) {
			switch (state__et) {
				case STATE_Initializing:
					/* state has a sub graph */
					/* without init transition */
					state__et = this.history[STATE_Initializing];
					break;
				case STATE_Initializing_Forewards:
					if (!(skip_entry__et)) entry_Initializing_Forewards();
					/* in leaf state: return state id */
					return STATE_Initializing_Forewards;
				case STATE_Initializing_Backwards:
					if (!(skip_entry__et)) entry_Initializing_Backwards();
					/* in leaf state: return state id */
					return STATE_Initializing_Backwards;
				case STATE_Running:
					/* state has a sub graph */
					/* without init transition */
					state__et = this.history[STATE_Running];
					break;
				case STATE_Running_Empty:
					if (!(skip_entry__et)) entry_Running_Empty();
					/* in leaf state: return state id */
					return STATE_Running_Empty;
				case STATE_Running_Forewards:
					if (!(skip_entry__et)) entry_Running_Forewards();
					/* in leaf state: return state id */
					return STATE_Running_Forewards;
				case STATE_Running_Backwards:
					if (!(skip_entry__et)) entry_Running_Backwards();
					/* in leaf state: return state id */
					return STATE_Running_Backwards;
				case STATE_Running_Full:
					if (!(skip_entry__et)) entry_Running_Full();
					/* in leaf state: return state id */
					return STATE_Running_Full;
				case STATE_TOP:
					state__et = this.history[STATE_TOP];
					break;
				default:
					/* should not occur */
					break;
			}
			skip_entry__et = false;
		}
		/* return NO_STATE; // required by CDT but detected as unreachable by JDT because of while (true) */
	}
	
	public void executeInitTransition() {
		int chain__et = CHAIN_TRANS_INITIAL_TO__Initializing_init;
		int next__et = executeTransitionChain(chain__et, null, null);
		next__et = enterHistory(next__et);
		setState(next__et);
	}
	
	/* receiveEvent contains the main implementation of the FSM */
	public void receiveEvent(InterfaceItemBase ifitem, int evt, Object generic_data__et) {
		int trigger__et = ifitem.getLocalId() + EVT_SHIFT*evt;
		int chain__et = NOT_CAUGHT;
		int catching_state__et = NO_STATE;
		
		if (!handleSystemEvent(ifitem, evt, generic_data__et)) {
			switch (getState()) {
				case STATE_Initializing_Forewards:
					switch(trigger__et) {
							case TRIG_pusher__doneMoveForward:
								{
									chain__et = CHAIN_Initializing_TRANS_tr5_FROM_Forewards_TO_Backwards_BY_doneMoveForwardpusher;
									catching_state__et = STATE_Initializing;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Initializing_Backwards:
					switch(trigger__et) {
							case TRIG_pusher__doneMoveBackward:
								{
									chain__et = CHAIN_Initializing_TRANS_tr8_FROM_Backwards_TO_running_BY_doneMoveBackwardpusher;
									catching_state__et = STATE_Initializing;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Running_Empty:
					switch(trigger__et) {
							case TRIG_fct__takePart:
								{
									chain__et = CHAIN_Running_TRANS_tr2_FROM_Empty_TO_Full_BY_takePartfct;
									catching_state__et = STATE_Running;
								}
							break;
							case TRIG_fct__getStatus:
								{
									chain__et = CHAIN_Running_TRANS_tr6_FROM_Empty_TO_Empty_BY_getStatusfct_tr6;
									catching_state__et = STATE_Running;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Running_Forewards:
					switch(trigger__et) {
							case TRIG_pusher__doneMoveForward:
								{
									chain__et = CHAIN_Running_TRANS_tr0_FROM_Forewards_TO_Backwards_BY_doneMoveForwardpusher;
									catching_state__et = STATE_Running;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Running_Backwards:
					switch(trigger__et) {
							case TRIG_pusher__doneMoveBackward:
								{
									chain__et = CHAIN_Running_TRANS_tr1_FROM_Backwards_TO_Empty_BY_doneMoveBackwardpusher;
									catching_state__et = STATE_Running;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Running_Full:
					switch(trigger__et) {
							case TRIG_fct__releasePart:
								{
									chain__et = CHAIN_Running_TRANS_tr3_FROM_Full_TO_Forewards_BY_releasePartfct;
									catching_state__et = STATE_Running;
								}
							break;
							case TRIG_fct__getStatus:
								{
									chain__et = CHAIN_Running_TRANS_tr7_FROM_Full_TO_Full_BY_getStatusfct_tr7;
									catching_state__et = STATE_Running;
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
			exitTo(getState(), catching_state__et);
			{
				int next__et = executeTransitionChain(chain__et, ifitem, generic_data__et);
				next__et = enterHistory(next__et);
				setState(next__et);
			}
		}
	}
	
	
};
