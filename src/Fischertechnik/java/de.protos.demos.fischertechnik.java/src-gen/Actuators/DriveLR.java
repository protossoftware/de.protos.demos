package Actuators;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import AutomationProtocols.*;
import protos.automation.service.io.*;
import protos.automation.service.io.PDigOut.*;
import AutomationProtocols.PDriveLR.*;

/*--------------------- begin user code ---------------------*/
import de.protos.automation.demos.fischertechnik.config.*;
/*--------------------- end user code ---------------------*/


public class DriveLR extends ActorClassBase {

	
	//--------------------- ports
	protected PDriveLRPort fct = null;
	
	//--------------------- saps
	protected PDigOutConjPort lr = null;
	protected PDigOutConjPort start = null;
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_fct = 1;
	public static final int IFITEM_lr = 2;
	public static final int IFITEM_start = 3;
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public DriveLR(IRTObject parent, String name) {
		super(parent, name);
		setClassName("DriveLR");
		
		// initialize attributes

		// own ports
		fct = new PDriveLRPort(this, "fct", IFITEM_fct);
		
		// own saps
		lr = new PDigOutConjPort(this, "lr", IFITEM_lr, 0);
		start = new PDigOutConjPort(this, "start", IFITEM_start, 0);
		
		// own service implementations
		
		// sub actors
		
		// wiring
		
		

	}
	
	/* --------------------- attribute setters and getters */
	
	
	//--------------------- port getters
	public PDriveLRPort getFct (){
		return this.fct;
	}
	public PDigOutConjPort getLr (){
		return this.lr;
	}
	public PDigOutConjPort getStart (){
		return this.start;
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
	public static final int STATE_Ready = 2;
	public static final int STATE_Moving = 3;
	public static final int STATE_MAX = 4;
	
	/* transition chains */
	public static final int CHAIN_TRANS_INITIAL_TO__Ready = 1;
	public static final int CHAIN_TRANS_tr0_FROM_Ready_TO_Moving_BY_startfct = 2;
	public static final int CHAIN_TRANS_tr1_FROM_Moving_TO_Ready_BY_stopfct = 3;
	public static final int CHAIN_TRANS_tr2_FROM_Ready_TO_Ready_BY_changeDirectionfct_tr2 = 4;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_fct__changeDirection = IFITEM_fct + EVT_SHIFT*PDriveLR.IN_changeDirection;
	public static final int TRIG_fct__start = IFITEM_fct + EVT_SHIFT*PDriveLR.IN_start;
	public static final int TRIG_fct__stop = IFITEM_fct + EVT_SHIFT*PDriveLR.IN_stop;
	public static final int TRIG_lr__registerChannelDone = IFITEM_lr + EVT_SHIFT*PDigOut.OUT_registerChannelDone;
	public static final int TRIG_lr__error = IFITEM_lr + EVT_SHIFT*PDigOut.OUT_error;
	public static final int TRIG_start__registerChannelDone = IFITEM_start + EVT_SHIFT*PDigOut.OUT_registerChannelDone;
	public static final int TRIG_start__error = IFITEM_start + EVT_SHIFT*PDigOut.OUT_error;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"Ready",
		"Moving"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	protected void entry_Moving() {
		start.setOn();
	}
	protected void exit_Moving() {
		start.setOff();
	}
	
	/* Action Codes */
	protected void action_TRANS_tr2_FROM_Ready_TO_Ready_BY_changeDirectionfct_tr2(InterfaceItemBase ifitem, boolean x) {
		if(x) lr.setOn();
		else lr.setOff();
	}
	protected void action_TRANS_INITIAL_TO__Ready() {
		FischertechnikConfiguration config = FischertechnikConfiguration.getInstance();
		lr.registerChannel(config.getIntValue(getInstancePath(), "lr"));
		start.registerChannel(config.getIntValue(getInstancePath(), "start"));
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
				case STATE_Ready:
					this.history[STATE_TOP] = STATE_Ready;
					current__et = STATE_TOP;
					break;
				case STATE_Moving:
					exit_Moving();
					this.history[STATE_TOP] = STATE_Moving;
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
			case CHAIN_TRANS_tr0_FROM_Ready_TO_Moving_BY_startfct:
			{
				return STATE_Moving;
			}
			case CHAIN_TRANS_tr1_FROM_Moving_TO_Ready_BY_stopfct:
			{
				return STATE_Ready;
			}
			case CHAIN_TRANS_tr2_FROM_Ready_TO_Ready_BY_changeDirectionfct_tr2:
			{
				boolean x = (Boolean) generic_data__et;
				action_TRANS_tr2_FROM_Ready_TO_Ready_BY_changeDirectionfct_tr2(ifitem, x);
				return STATE_Ready;
			}
			case CHAIN_TRANS_INITIAL_TO__Ready:
			{
				action_TRANS_INITIAL_TO__Ready();
				return STATE_Ready;
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
				case STATE_Ready:
					/* in leaf state: return state id */
					return STATE_Ready;
				case STATE_Moving:
					if (!(skip_entry__et)) entry_Moving();
					/* in leaf state: return state id */
					return STATE_Moving;
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
		int chain__et = CHAIN_TRANS_INITIAL_TO__Ready;
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
				case STATE_Ready:
					switch(trigger__et) {
							case TRIG_fct__start:
								{
									chain__et = CHAIN_TRANS_tr0_FROM_Ready_TO_Moving_BY_startfct;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_fct__changeDirection:
								{
									chain__et = CHAIN_TRANS_tr2_FROM_Ready_TO_Ready_BY_changeDirectionfct_tr2;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Moving:
					switch(trigger__et) {
							case TRIG_fct__stop:
								{
									chain__et = CHAIN_TRANS_tr1_FROM_Moving_TO_Ready_BY_stopfct;
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
