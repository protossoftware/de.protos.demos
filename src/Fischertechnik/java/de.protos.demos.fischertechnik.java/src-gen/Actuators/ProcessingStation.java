package Actuators;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import AutomationProtocols.*;
import protos.automation.service.io.*;
import room.basic.service.timing.*;
import protos.automation.service.io.PDigOut.*;
import AutomationProtocols.PDriveLR.*;
import AutomationProtocols.PProcessing.*;
import room.basic.service.timing.PTimer.*;



public class ProcessingStation extends ActorClassBase {

	
	//--------------------- ports
	protected PProcessingPort fct = null;
	protected PDriveLRConjPort drive = null;
	
	//--------------------- saps
	protected PTimerConjPort timeout = null;
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_fct = 2;
	public static final int IFITEM_drive = 1;
	public static final int IFITEM_timeout = 3;
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public ProcessingStation(IRTObject parent, String name) {
		super(parent, name);
		setClassName("ProcessingStation");
		
		// initialize attributes

		// own ports
		fct = new PProcessingPort(this, "fct", IFITEM_fct);
		drive = new PDriveLRConjPort(this, "drive", IFITEM_drive);
		
		// own saps
		timeout = new PTimerConjPort(this, "timeout", IFITEM_timeout, 0);
		
		// own service implementations
		
		// sub actors
		DebuggingService.getInstance().addMessageActorCreate(this, "StationDrive");
		new DriveLR(this, "StationDrive");
		
		// wiring
		InterfaceItemBase.connect(this, "StationDrive/fct", "drive");
		
		

	}
	
	/* --------------------- attribute setters and getters */
	
	
	//--------------------- port getters
	public PProcessingPort getFct (){
		return this.fct;
	}
	public PDriveLRConjPort getDrive (){
		return this.drive;
	}
	public PTimerConjPort getTimeout (){
		return this.timeout;
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
	public static final int STATE_Idle = 2;
	public static final int STATE_Working1 = 3;
	public static final int STATE_Working2 = 4;
	public static final int STATE_ChangeDirection = 5;
	public static final int STATE_MAX = 6;
	
	/* transition chains */
	public static final int CHAIN_TRANS_INITIAL_TO__Idle = 1;
	public static final int CHAIN_TRANS_tr1_FROM_Idle_TO_Working1_BY_startProcessingfct = 2;
	public static final int CHAIN_TRANS_tr2_FROM_Working2_TO_Idle_BY_timeouttimeout = 3;
	public static final int CHAIN_TRANS_tr3_FROM_Working1_TO_ChangeDirection_BY_timeouttimeout = 4;
	public static final int CHAIN_TRANS_tr4_FROM_ChangeDirection_TO_Working2_BY_timeouttimeout = 5;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_fct__startProcessing = IFITEM_fct + EVT_SHIFT*PProcessing.IN_startProcessing;
	public static final int TRIG_timeout__timeout = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_timeout;
	public static final int TRIG_timeout__internalTimer = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_internalTimer;
	public static final int TRIG_timeout__internalTimeout = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_internalTimeout;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"Idle",
		"Working1",
		"Working2",
		"ChangeDirection"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	protected void entry_Working1() {
		drive.changeDirection(false);
		drive.start();
		timeout.startTimeout(1000);
	}
	protected void exit_Working1() {
		drive.stop();
	}
	protected void entry_Working2() {
		drive.start();
		timeout.startTimeout(1000);
	}
	protected void exit_Working2() {
		drive.stop();
	}
	protected void entry_ChangeDirection() {
		drive.changeDirection(true);
		timeout.startTimeout(100);
	}
	
	/* Action Codes */
	protected void action_TRANS_tr2_FROM_Working2_TO_Idle_BY_timeouttimeout(InterfaceItemBase ifitem) {
		fct.doneProcessing();
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
				case STATE_Idle:
					this.history[STATE_TOP] = STATE_Idle;
					current__et = STATE_TOP;
					break;
				case STATE_Working1:
					exit_Working1();
					this.history[STATE_TOP] = STATE_Working1;
					current__et = STATE_TOP;
					break;
				case STATE_Working2:
					exit_Working2();
					this.history[STATE_TOP] = STATE_Working2;
					current__et = STATE_TOP;
					break;
				case STATE_ChangeDirection:
					this.history[STATE_TOP] = STATE_ChangeDirection;
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
	private int executeTransitionChain(int chain__et, InterfaceItemBase ifitem, Object generic_data__et) {
		switch (chain__et) {
			case CHAIN_TRANS_INITIAL_TO__Idle:
			{
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr1_FROM_Idle_TO_Working1_BY_startProcessingfct:
			{
				return STATE_Working1;
			}
			case CHAIN_TRANS_tr2_FROM_Working2_TO_Idle_BY_timeouttimeout:
			{
				action_TRANS_tr2_FROM_Working2_TO_Idle_BY_timeouttimeout(ifitem);
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr3_FROM_Working1_TO_ChangeDirection_BY_timeouttimeout:
			{
				return STATE_ChangeDirection;
			}
			case CHAIN_TRANS_tr4_FROM_ChangeDirection_TO_Working2_BY_timeouttimeout:
			{
				return STATE_Working2;
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
				case STATE_Idle:
					/* in leaf state: return state id */
					return STATE_Idle;
				case STATE_Working1:
					if (!(skip_entry__et)) entry_Working1();
					/* in leaf state: return state id */
					return STATE_Working1;
				case STATE_Working2:
					if (!(skip_entry__et)) entry_Working2();
					/* in leaf state: return state id */
					return STATE_Working2;
				case STATE_ChangeDirection:
					if (!(skip_entry__et)) entry_ChangeDirection();
					/* in leaf state: return state id */
					return STATE_ChangeDirection;
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
		int chain__et = CHAIN_TRANS_INITIAL_TO__Idle;
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
				case STATE_Idle:
					switch(trigger__et) {
							case TRIG_fct__startProcessing:
								{
									chain__et = CHAIN_TRANS_tr1_FROM_Idle_TO_Working1_BY_startProcessingfct;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Working1:
					switch(trigger__et) {
							case TRIG_timeout__timeout:
								{
									chain__et = CHAIN_TRANS_tr3_FROM_Working1_TO_ChangeDirection_BY_timeouttimeout;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Working2:
					switch(trigger__et) {
							case TRIG_timeout__timeout:
								{
									chain__et = CHAIN_TRANS_tr2_FROM_Working2_TO_Idle_BY_timeouttimeout;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_ChangeDirection:
					switch(trigger__et) {
							case TRIG_timeout__timeout:
								{
									chain__et = CHAIN_TRANS_tr4_FROM_ChangeDirection_TO_Working2_BY_timeouttimeout;
									catching_state__et = STATE_TOP;
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
