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

/*--------------------- begin user code ---------------------*/
import de.protos.automation.demos.fischertechnik.config.*;
/*--------------------- end user code ---------------------*/


public class LinearUnit extends ActorClassBase {

	
	//--------------------- ports
	protected PLinearUnitPort fct = null;
	protected PDriveLRConjPort drive = null;
	
	//--------------------- saps
	protected PDigInConjPort sensorFront = null;
	protected PDigInConjPort sensorBack = null;
	protected PTimerConjPort timeout = null;
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_fct = 2;
	public static final int IFITEM_drive = 1;
	public static final int IFITEM_sensorFront = 3;
	public static final int IFITEM_sensorBack = 4;
	public static final int IFITEM_timeout = 5;
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public LinearUnit(IRTObject parent, String name) {
		super(parent, name);
		setClassName("LinearUnit");
		
		// initialize attributes

		// own ports
		fct = new PLinearUnitPort(this, "fct", IFITEM_fct);
		drive = new PDriveLRConjPort(this, "drive", IFITEM_drive);
		
		// own saps
		sensorFront = new PDigInConjPort(this, "sensorFront", IFITEM_sensorFront, 0);
		sensorBack = new PDigInConjPort(this, "sensorBack", IFITEM_sensorBack, 0);
		timeout = new PTimerConjPort(this, "timeout", IFITEM_timeout, 0);
		
		// own service implementations
		
		// sub actors
		DebuggingService.getInstance().addMessageActorCreate(this, "Drive");
		new DriveLR(this, "Drive");
		
		// wiring
		InterfaceItemBase.connect(this, "Drive/fct", "drive");
		
		

	}
	
	/* --------------------- attribute setters and getters */
	
	
	//--------------------- port getters
	public PLinearUnitPort getFct (){
		return this.fct;
	}
	public PDriveLRConjPort getDrive (){
		return this.drive;
	}
	public PDigInConjPort getSensorFront (){
		return this.sensorFront;
	}
	public PDigInConjPort getSensorBack (){
		return this.sensorBack;
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
	public static final int STATE_Undefined = 2;
	public static final int STATE_LinearUnitBackwards = 3;
	public static final int STATE_LinearUnitInPosBack = 4;
	public static final int STATE_Error = 5;
	public static final int STATE_LinearUnitForwards = 6;
	public static final int STATE_LinearUnitInPosFront = 7;
	public static final int STATE_MAX = 8;
	
	/* transition chains */
	public static final int CHAIN_TRANS_INITIAL_TO__Undefined = 1;
	public static final int CHAIN_TRANS_tr1_FROM_LinearUnitBackwards_TO_LinearUnitInPosBack_BY_inputChangedsensorBack = 2;
	public static final int CHAIN_TRANS_tr2_FROM_LinearUnitBackwards_TO_Error_BY_timeouttimeout = 3;
	public static final int CHAIN_TRANS_tr3_FROM_LinearUnitInPosBack_TO_LinearUnitForwards_BY_moveForwardfct = 4;
	public static final int CHAIN_TRANS_tr4_FROM_LinearUnitForwards_TO_LinearUnitInPosFront_BY_inputChangedsensorFront = 5;
	public static final int CHAIN_TRANS_tr5_FROM_LinearUnitInPosFront_TO_LinearUnitBackwards_BY_moveBackwardfct = 6;
	public static final int CHAIN_TRANS_tr6_FROM_LinearUnitForwards_TO_Error_BY_timeouttimeout = 7;
	public static final int CHAIN_TRANS_tr7_FROM_Undefined_TO_LinearUnitBackwards_BY_moveBackwardfct = 8;
	public static final int CHAIN_TRANS_tr8_FROM_Undefined_TO_LinearUnitForwards_BY_moveForwardfct = 9;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_fct__moveForward = IFITEM_fct + EVT_SHIFT*PLinearUnit.IN_moveForward;
	public static final int TRIG_fct__moveBackward = IFITEM_fct + EVT_SHIFT*PLinearUnit.IN_moveBackward;
	public static final int TRIG_sensorFront__inputChanged = IFITEM_sensorFront + EVT_SHIFT*PDigIn.OUT_inputChanged;
	public static final int TRIG_sensorFront__registerChannelDone = IFITEM_sensorFront + EVT_SHIFT*PDigIn.OUT_registerChannelDone;
	public static final int TRIG_sensorFront__error = IFITEM_sensorFront + EVT_SHIFT*PDigIn.OUT_error;
	public static final int TRIG_sensorBack__inputChanged = IFITEM_sensorBack + EVT_SHIFT*PDigIn.OUT_inputChanged;
	public static final int TRIG_sensorBack__registerChannelDone = IFITEM_sensorBack + EVT_SHIFT*PDigIn.OUT_registerChannelDone;
	public static final int TRIG_sensorBack__error = IFITEM_sensorBack + EVT_SHIFT*PDigIn.OUT_error;
	public static final int TRIG_timeout__timeout = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_timeout;
	public static final int TRIG_timeout__internalTimer = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_internalTimer;
	public static final int TRIG_timeout__internalTimeout = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_internalTimeout;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"Undefined",
		"LinearUnitBackwards",
		"LinearUnitInPosBack",
		"Error",
		"LinearUnitForwards",
		"LinearUnitInPosFront"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	protected void entry_LinearUnitBackwards() {
		drive.changeDirection(true);
		drive.start();
		timeout.startTimeout(3000);
		sensorBack.getStatus();
	}
	protected void exit_LinearUnitBackwards() {
		drive.stop();
		timeout.kill();
		drive.changeDirection(false);
	}
	protected void entry_LinearUnitInPosBack() {
		fct.doneMoveBackward();
	}
	protected void entry_LinearUnitForwards() {
		drive.changeDirection(false);
		drive.start();
		timeout.startTimeout(3000);
		sensorFront.getStatus();
	}
	protected void exit_LinearUnitForwards() {
		drive.stop();
		timeout.kill();
	}
	protected void entry_LinearUnitInPosFront() {
		fct.doneMoveForward();
	}
	
	/* Action Codes */
	protected void action_TRANS_INITIAL_TO__Undefined() {
		FischertechnikConfiguration config = FischertechnikConfiguration.getInstance();
		sensorFront.registerChannel(config.getIntValue(getInstancePath(), "sensorFront"));
		sensorBack.registerChannel(config.getIntValue(getInstancePath(), "sensorBack"));
	}
	protected void action_TRANS_tr2_FROM_LinearUnitBackwards_TO_Error_BY_timeouttimeout(InterfaceItemBase ifitem) {
		System.out.println("ERROR : timeout sensorBack ");
	}
	protected void action_TRANS_tr6_FROM_LinearUnitForwards_TO_Error_BY_timeouttimeout(InterfaceItemBase ifitem) {
		System.out.println("ERROR : timeout sensorFront ");
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
				case STATE_Undefined:
					this.history[STATE_TOP] = STATE_Undefined;
					current__et = STATE_TOP;
					break;
				case STATE_LinearUnitBackwards:
					exit_LinearUnitBackwards();
					this.history[STATE_TOP] = STATE_LinearUnitBackwards;
					current__et = STATE_TOP;
					break;
				case STATE_LinearUnitInPosBack:
					this.history[STATE_TOP] = STATE_LinearUnitInPosBack;
					current__et = STATE_TOP;
					break;
				case STATE_Error:
					this.history[STATE_TOP] = STATE_Error;
					current__et = STATE_TOP;
					break;
				case STATE_LinearUnitForwards:
					exit_LinearUnitForwards();
					this.history[STATE_TOP] = STATE_LinearUnitForwards;
					current__et = STATE_TOP;
					break;
				case STATE_LinearUnitInPosFront:
					this.history[STATE_TOP] = STATE_LinearUnitInPosFront;
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
			case CHAIN_TRANS_INITIAL_TO__Undefined:
			{
				action_TRANS_INITIAL_TO__Undefined();
				return STATE_Undefined;
			}
			case CHAIN_TRANS_tr1_FROM_LinearUnitBackwards_TO_LinearUnitInPosBack_BY_inputChangedsensorBack:
			{
				int x = (Integer) generic_data__et;
				return STATE_LinearUnitInPosBack;
			}
			case CHAIN_TRANS_tr2_FROM_LinearUnitBackwards_TO_Error_BY_timeouttimeout:
			{
				action_TRANS_tr2_FROM_LinearUnitBackwards_TO_Error_BY_timeouttimeout(ifitem);
				return STATE_Error;
			}
			case CHAIN_TRANS_tr3_FROM_LinearUnitInPosBack_TO_LinearUnitForwards_BY_moveForwardfct:
			{
				return STATE_LinearUnitForwards;
			}
			case CHAIN_TRANS_tr4_FROM_LinearUnitForwards_TO_LinearUnitInPosFront_BY_inputChangedsensorFront:
			{
				int x = (Integer) generic_data__et;
				return STATE_LinearUnitInPosFront;
			}
			case CHAIN_TRANS_tr5_FROM_LinearUnitInPosFront_TO_LinearUnitBackwards_BY_moveBackwardfct:
			{
				return STATE_LinearUnitBackwards;
			}
			case CHAIN_TRANS_tr6_FROM_LinearUnitForwards_TO_Error_BY_timeouttimeout:
			{
				action_TRANS_tr6_FROM_LinearUnitForwards_TO_Error_BY_timeouttimeout(ifitem);
				return STATE_Error;
			}
			case CHAIN_TRANS_tr7_FROM_Undefined_TO_LinearUnitBackwards_BY_moveBackwardfct:
			{
				return STATE_LinearUnitBackwards;
			}
			case CHAIN_TRANS_tr8_FROM_Undefined_TO_LinearUnitForwards_BY_moveForwardfct:
			{
				return STATE_LinearUnitForwards;
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
				case STATE_Undefined:
					/* in leaf state: return state id */
					return STATE_Undefined;
				case STATE_LinearUnitBackwards:
					if (!(skip_entry__et)) entry_LinearUnitBackwards();
					/* in leaf state: return state id */
					return STATE_LinearUnitBackwards;
				case STATE_LinearUnitInPosBack:
					if (!(skip_entry__et)) entry_LinearUnitInPosBack();
					/* in leaf state: return state id */
					return STATE_LinearUnitInPosBack;
				case STATE_Error:
					/* in leaf state: return state id */
					return STATE_Error;
				case STATE_LinearUnitForwards:
					if (!(skip_entry__et)) entry_LinearUnitForwards();
					/* in leaf state: return state id */
					return STATE_LinearUnitForwards;
				case STATE_LinearUnitInPosFront:
					if (!(skip_entry__et)) entry_LinearUnitInPosFront();
					/* in leaf state: return state id */
					return STATE_LinearUnitInPosFront;
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
		int chain__et = CHAIN_TRANS_INITIAL_TO__Undefined;
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
				case STATE_Undefined:
					switch(trigger__et) {
							case TRIG_fct__moveBackward:
								{
									chain__et = CHAIN_TRANS_tr7_FROM_Undefined_TO_LinearUnitBackwards_BY_moveBackwardfct;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_fct__moveForward:
								{
									chain__et = CHAIN_TRANS_tr8_FROM_Undefined_TO_LinearUnitForwards_BY_moveForwardfct;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_LinearUnitBackwards:
					switch(trigger__et) {
							case TRIG_sensorBack__inputChanged:
								{ int x = (Integer) generic_data__et;
								if (x==0)
								{
									chain__et = CHAIN_TRANS_tr1_FROM_LinearUnitBackwards_TO_LinearUnitInPosBack_BY_inputChangedsensorBack;
									catching_state__et = STATE_TOP;
								}
								}
							break;
							case TRIG_timeout__timeout:
								{
									chain__et = CHAIN_TRANS_tr2_FROM_LinearUnitBackwards_TO_Error_BY_timeouttimeout;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_LinearUnitInPosBack:
					switch(trigger__et) {
							case TRIG_fct__moveForward:
								{
									chain__et = CHAIN_TRANS_tr3_FROM_LinearUnitInPosBack_TO_LinearUnitForwards_BY_moveForwardfct;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Error:
					break;
				case STATE_LinearUnitForwards:
					switch(trigger__et) {
							case TRIG_sensorFront__inputChanged:
								{ int x = (Integer) generic_data__et;
								if (x==0)
								{
									chain__et = CHAIN_TRANS_tr4_FROM_LinearUnitForwards_TO_LinearUnitInPosFront_BY_inputChangedsensorFront;
									catching_state__et = STATE_TOP;
								}
								}
							break;
							case TRIG_timeout__timeout:
								{
									chain__et = CHAIN_TRANS_tr6_FROM_LinearUnitForwards_TO_Error_BY_timeouttimeout;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_LinearUnitInPosFront:
					switch(trigger__et) {
							case TRIG_fct__moveBackward:
								{
									chain__et = CHAIN_TRANS_tr5_FROM_LinearUnitInPosFront_TO_LinearUnitBackwards_BY_moveBackwardfct;
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
