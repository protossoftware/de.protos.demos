package GenericLineElements;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import AutomationProtocols.*;
import protos.automation.service.io.*;
import protos.automation.service.io.PDigIn.*;
import AutomationProtocols.PInlineElement.*;

/*--------------------- begin user code ---------------------*/

				import de.protos.automation.demos.fischertechnik.config.*;
				import org.eclipse.etrice.runtime.java.debugging.DebuggingService;
				import org.eclipse.etrice.runtime.java.debugging.MSCFilter;
				
/*--------------------- end user code ---------------------*/


public class SourceSensor extends ActorClassBase {

	/*--------------------- begin user code ---------------------*/
		
					@Override
					public void initUser()
					{
						MSCFilter filter = DebuggingService.getInstance().getAsyncLogger().getMSCFilter();
						filter.addFilter(new MSCFilter.FilterItem("/MachineSubSystem/Controller/ProductionStation4", false));
					}
					
	/*--------------------- end user code ---------------------*/
	
	//--------------------- ports
	protected PInlineElementConjPort next = null;
	
	//--------------------- saps
	protected PDigInConjPort sensor = null;
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_next = 1;
	public static final int IFITEM_sensor = 2;
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public SourceSensor(IRTObject parent, String name) {
		super(parent, name);
		setClassName("SourceSensor");
		
		// initialize attributes

		// own ports
		next = new PInlineElementConjPort(this, "next", IFITEM_next);
		
		// own saps
		sensor = new PDigInConjPort(this, "sensor", IFITEM_sensor, 0);
		
		// own service implementations
		
		// sub actors
		
		// wiring
		
		

	}
	
	/* --------------------- attribute setters and getters */
	
	
	//--------------------- port getters
	public PInlineElementConjPort getNext (){
		return this.next;
	}
	public PDigInConjPort getSensor (){
		return this.sensor;
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
	public static final int STATE_NotInitialized = 2;
	public static final int STATE_Full = 3;
	public static final int STATE_Empty = 4;
	public static final int STATE_SendingPart = 5;
	public static final int STATE_MAX = 6;
	
	/* transition chains */
	public static final int CHAIN_TRANS_INITIAL_TO__NotInitialized = 1;
	public static final int CHAIN_TRANS_tr1_FROM_NotInitialized_TO_CP1_BY_inputChangedsensor = 2;
	public static final int CHAIN_TRANS_tr4_FROM_Full_TO_SendingPart_BY_isEmptynext = 3;
	public static final int CHAIN_TRANS_tr5_FROM_Full_TO_Empty_BY_inputChangedsensor = 4;
	public static final int CHAIN_TRANS_tr6_FROM_Empty_TO_Full_BY_inputChangedsensor = 5;
	public static final int CHAIN_TRANS_tr7_FROM_SendingPart_TO_Empty_BY_receivedPartnext = 6;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_next__isEmpty = IFITEM_next + EVT_SHIFT*PInlineElement.OUT_isEmpty;
	public static final int TRIG_next__receivedPart = IFITEM_next + EVT_SHIFT*PInlineElement.OUT_receivedPart;
	public static final int TRIG_sensor__inputChanged = IFITEM_sensor + EVT_SHIFT*PDigIn.OUT_inputChanged;
	public static final int TRIG_sensor__registerChannelDone = IFITEM_sensor + EVT_SHIFT*PDigIn.OUT_registerChannelDone;
	public static final int TRIG_sensor__error = IFITEM_sensor + EVT_SHIFT*PDigIn.OUT_error;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"NotInitialized",
		"Full",
		"Empty",
		"SendingPart"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	protected void entry_NotInitialized() {
		sensor.getStatus();
	}
	protected void entry_Full() {
		next.getStatus();
	}
	protected void entry_SendingPart() {
		next.sendPart();
	}
	
	/* Action Codes */
	protected void action_TRANS_INITIAL_TO__NotInitialized() {
		FischertechnikConfiguration config = FischertechnikConfiguration.getInstance();
		sensor.registerChannel(config.getIntValue(getInstancePath(), "sensor"));
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
				case STATE_NotInitialized:
					this.history[STATE_TOP] = STATE_NotInitialized;
					current__et = STATE_TOP;
					break;
				case STATE_Full:
					this.history[STATE_TOP] = STATE_Full;
					current__et = STATE_TOP;
					break;
				case STATE_Empty:
					this.history[STATE_TOP] = STATE_Empty;
					current__et = STATE_TOP;
					break;
				case STATE_SendingPart:
					this.history[STATE_TOP] = STATE_SendingPart;
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
			case CHAIN_TRANS_INITIAL_TO__NotInitialized:
			{
				action_TRANS_INITIAL_TO__NotInitialized();
				return STATE_NotInitialized;
			}
			case CHAIN_TRANS_tr1_FROM_NotInitialized_TO_CP1_BY_inputChangedsensor:
			{
				int x = (Integer) generic_data__et;
				if (x==0) {
				return STATE_Full;}
				else {
				return STATE_Empty;}
			}
			case CHAIN_TRANS_tr4_FROM_Full_TO_SendingPart_BY_isEmptynext:
			{
				return STATE_SendingPart;
			}
			case CHAIN_TRANS_tr5_FROM_Full_TO_Empty_BY_inputChangedsensor:
			{
				int x = (Integer) generic_data__et;
				return STATE_Empty;
			}
			case CHAIN_TRANS_tr6_FROM_Empty_TO_Full_BY_inputChangedsensor:
			{
				int x = (Integer) generic_data__et;
				return STATE_Full;
			}
			case CHAIN_TRANS_tr7_FROM_SendingPart_TO_Empty_BY_receivedPartnext:
			{
				return STATE_Empty;
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
				case STATE_NotInitialized:
					if (!(skip_entry__et)) entry_NotInitialized();
					/* in leaf state: return state id */
					return STATE_NotInitialized;
				case STATE_Full:
					if (!(skip_entry__et)) entry_Full();
					/* in leaf state: return state id */
					return STATE_Full;
				case STATE_Empty:
					/* in leaf state: return state id */
					return STATE_Empty;
				case STATE_SendingPart:
					if (!(skip_entry__et)) entry_SendingPart();
					/* in leaf state: return state id */
					return STATE_SendingPart;
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
		int chain__et = CHAIN_TRANS_INITIAL_TO__NotInitialized;
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
				case STATE_NotInitialized:
					switch(trigger__et) {
							case TRIG_sensor__inputChanged:
								{
									chain__et = CHAIN_TRANS_tr1_FROM_NotInitialized_TO_CP1_BY_inputChangedsensor;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Full:
					switch(trigger__et) {
							case TRIG_next__isEmpty:
								{
									chain__et = CHAIN_TRANS_tr4_FROM_Full_TO_SendingPart_BY_isEmptynext;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_sensor__inputChanged:
								{ int x = (Integer) generic_data__et;
								if (x==1)
								{
									chain__et = CHAIN_TRANS_tr5_FROM_Full_TO_Empty_BY_inputChangedsensor;
									catching_state__et = STATE_TOP;
								}
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Empty:
					switch(trigger__et) {
							case TRIG_sensor__inputChanged:
								{ int x = (Integer) generic_data__et;
								if (x==0)
								{
									chain__et = CHAIN_TRANS_tr6_FROM_Empty_TO_Full_BY_inputChangedsensor;
									catching_state__et = STATE_TOP;
								}
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_SendingPart:
					switch(trigger__et) {
							case TRIG_next__receivedPart:
								{
									chain__et = CHAIN_TRANS_tr7_FROM_SendingPart_TO_Empty_BY_receivedPartnext;
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
