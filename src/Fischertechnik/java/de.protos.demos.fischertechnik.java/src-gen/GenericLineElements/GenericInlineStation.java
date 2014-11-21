package GenericLineElements;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import AutomationProtocols.*;
import AutomationProtocols.PInlineElement.*;
import AutomationProtocols.PProcessing.*;
import AutomationProtocols.PTransport.*;

/*--------------------- begin user code ---------------------*/
import de.protos.automation.demos.fischertechnik.config.*;
/*--------------------- end user code ---------------------*/


public class GenericInlineStation extends ActorClassBase {

	
	//--------------------- ports
	protected PInlineElementPort prev = null;
	protected PInlineElementConjPort next = null;
	protected PTransportConjPort transport = null;
	protected PProcessingConjPort job = null;
	
	//--------------------- saps
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_prev = 1;
	public static final int IFITEM_next = 2;
	public static final int IFITEM_transport = 3;
	public static final int IFITEM_job = 4;
	
	/*--------------------- attributes ---------------------*/
	boolean processingActive;
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public GenericInlineStation(IRTObject parent, String name) {
		super(parent, name);
		setClassName("GenericInlineStation");
		
		// initialize attributes
		this.setProcessingActive(false);

		// own ports
		prev = new PInlineElementPort(this, "prev", IFITEM_prev);
		next = new PInlineElementConjPort(this, "next", IFITEM_next);
		transport = new PTransportConjPort(this, "transport", IFITEM_transport);
		job = new PProcessingConjPort(this, "job", IFITEM_job);
		
		// own saps
		
		// own service implementations
		
		// sub actors
		
		// wiring
		
		

	}
	
	/* --------------------- attribute setters and getters */
	public void setProcessingActive (boolean processingActive) {
		 this.processingActive = processingActive;
	}
	public boolean getProcessingActive () {
		return this.processingActive;
	}
	
	
	//--------------------- port getters
	public PInlineElementPort getPrev (){
		return this.prev;
	}
	public PInlineElementConjPort getNext (){
		return this.next;
	}
	public PTransportConjPort getTransport (){
		return this.transport;
	}
	public PProcessingConjPort getJob (){
		return this.job;
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
	public static final int STATE_GetStatusTransport = 2;
	public static final int STATE_FullWaitingForNext = 3;
	public static final int STATE_Empty = 4;
	public static final int STATE_ReleasePart = 5;
	public static final int STATE_SendPartToNext = 6;
	public static final int STATE_Processing = 7;
	public static final int STATE_HandOver = 8;
	public static final int STATE_CheckingTransportForEmpty = 9;
	public static final int STATE_MAX = 10;
	
	/* transition chains */
	public static final int CHAIN_TRANS_INITIAL_TO__GetStatusTransport = 1;
	public static final int CHAIN_TRANS_tr11_FROM_Processing_TO_FullWaitingForNext_BY_doneProcessingjob = 2;
	public static final int CHAIN_TRANS_tr12_FROM_Empty_TO_HandOver_BY_sendPartprev = 3;
	public static final int CHAIN_TRANS_tr13_FROM_HandOver_TO_GetStatusTransport_BY_takePartDonetransport = 4;
	public static final int CHAIN_TRANS_tr14_FROM_CheckingTransportForEmpty_TO_Empty_BY_isEmptytransport = 5;
	public static final int CHAIN_TRANS_tr1_FROM_GetStatusTransport_TO_Empty_BY_isEmptytransport = 6;
	public static final int CHAIN_TRANS_tr2_FROM_Empty_TO_Empty_BY_getStatusprev_tr2 = 7;
	public static final int CHAIN_TRANS_tr3_FROM_FullWaitingForNext_TO_ReleasePart_BY_isEmptynext = 8;
	public static final int CHAIN_TRANS_tr4_FROM_ReleasePart_TO_SendPartToNext_BY_releasePartDonetransport = 9;
	public static final int CHAIN_TRANS_tr5_FROM_SendPartToNext_TO_CheckingTransportForEmpty_BY_receivedPartnext = 10;
	public static final int CHAIN_TRANS_tr6_FROM_Empty_TO_FullWaitingForNext_BY_isFulltransport = 11;
	public static final int CHAIN_TRANS_tr7_FROM_FullWaitingForNext_TO_Empty_BY_isEmptytransport = 12;
	public static final int CHAIN_TRANS_tr8_FROM_GetStatusTransport_TO_CP1_BY_isFulltransport = 13;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_prev__getStatus = IFITEM_prev + EVT_SHIFT*PInlineElement.IN_getStatus;
	public static final int TRIG_prev__sendPart = IFITEM_prev + EVT_SHIFT*PInlineElement.IN_sendPart;
	public static final int TRIG_next__isEmpty = IFITEM_next + EVT_SHIFT*PInlineElement.OUT_isEmpty;
	public static final int TRIG_next__receivedPart = IFITEM_next + EVT_SHIFT*PInlineElement.OUT_receivedPart;
	public static final int TRIG_transport__isFull = IFITEM_transport + EVT_SHIFT*PTransport.OUT_isFull;
	public static final int TRIG_transport__isEmpty = IFITEM_transport + EVT_SHIFT*PTransport.OUT_isEmpty;
	public static final int TRIG_transport__releasePartDone = IFITEM_transport + EVT_SHIFT*PTransport.OUT_releasePartDone;
	public static final int TRIG_transport__takePartDone = IFITEM_transport + EVT_SHIFT*PTransport.OUT_takePartDone;
	public static final int TRIG_job__doneProcessing = IFITEM_job + EVT_SHIFT*PProcessing.OUT_doneProcessing;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"GetStatusTransport",
		"FullWaitingForNext",
		"Empty",
		"ReleasePart",
		"SendPartToNext",
		"Processing",
		"HandOver",
		"CheckingTransportForEmpty"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	protected void entry_GetStatusTransport() {
		transport.getStatus();
	}
	protected void entry_FullWaitingForNext() {
		next.getStatus();
	}
	protected void entry_Empty() {
		prev.isEmpty();
	}
	protected void entry_ReleasePart() {
		transport.releasePart();
	}
	protected void entry_SendPartToNext() {
		next.sendPart();
	}
	protected void entry_Processing() {
		job.startProcessing();
	}
	protected void entry_HandOver() {
		transport.takePart();
	}
	protected void entry_CheckingTransportForEmpty() {
		transport.getStatus();
	}
	
	/* Action Codes */
	protected void action_TRANS_INITIAL_TO__GetStatusTransport() {
		FischertechnikConfiguration config = FischertechnikConfiguration.getInstance();
		processingActive = (config.getIntValue(getInstancePath(), "processingActive") != 0);
	}
	protected void action_TRANS_tr13_FROM_HandOver_TO_GetStatusTransport_BY_takePartDonetransport(InterfaceItemBase ifitem) {
		prev.receivedPart();
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
				case STATE_GetStatusTransport:
					this.history[STATE_TOP] = STATE_GetStatusTransport;
					current__et = STATE_TOP;
					break;
				case STATE_FullWaitingForNext:
					this.history[STATE_TOP] = STATE_FullWaitingForNext;
					current__et = STATE_TOP;
					break;
				case STATE_Empty:
					this.history[STATE_TOP] = STATE_Empty;
					current__et = STATE_TOP;
					break;
				case STATE_ReleasePart:
					this.history[STATE_TOP] = STATE_ReleasePart;
					current__et = STATE_TOP;
					break;
				case STATE_SendPartToNext:
					this.history[STATE_TOP] = STATE_SendPartToNext;
					current__et = STATE_TOP;
					break;
				case STATE_Processing:
					this.history[STATE_TOP] = STATE_Processing;
					current__et = STATE_TOP;
					break;
				case STATE_HandOver:
					this.history[STATE_TOP] = STATE_HandOver;
					current__et = STATE_TOP;
					break;
				case STATE_CheckingTransportForEmpty:
					this.history[STATE_TOP] = STATE_CheckingTransportForEmpty;
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
			case CHAIN_TRANS_INITIAL_TO__GetStatusTransport:
			{
				action_TRANS_INITIAL_TO__GetStatusTransport();
				return STATE_GetStatusTransport;
			}
			case CHAIN_TRANS_tr1_FROM_GetStatusTransport_TO_Empty_BY_isEmptytransport:
			{
				return STATE_Empty;
			}
			case CHAIN_TRANS_tr2_FROM_Empty_TO_Empty_BY_getStatusprev_tr2:
			{
				return STATE_Empty;
			}
			case CHAIN_TRANS_tr3_FROM_FullWaitingForNext_TO_ReleasePart_BY_isEmptynext:
			{
				return STATE_ReleasePart;
			}
			case CHAIN_TRANS_tr4_FROM_ReleasePart_TO_SendPartToNext_BY_releasePartDonetransport:
			{
				return STATE_SendPartToNext;
			}
			case CHAIN_TRANS_tr6_FROM_Empty_TO_FullWaitingForNext_BY_isFulltransport:
			{
				return STATE_FullWaitingForNext;
			}
			case CHAIN_TRANS_tr7_FROM_FullWaitingForNext_TO_Empty_BY_isEmptytransport:
			{
				return STATE_Empty;
			}
			case CHAIN_TRANS_tr8_FROM_GetStatusTransport_TO_CP1_BY_isFulltransport:
			{
				if (processingActive) {
				return STATE_Processing;}
				else {
				return STATE_FullWaitingForNext;}
			}
			case CHAIN_TRANS_tr11_FROM_Processing_TO_FullWaitingForNext_BY_doneProcessingjob:
			{
				return STATE_FullWaitingForNext;
			}
			case CHAIN_TRANS_tr12_FROM_Empty_TO_HandOver_BY_sendPartprev:
			{
				return STATE_HandOver;
			}
			case CHAIN_TRANS_tr13_FROM_HandOver_TO_GetStatusTransport_BY_takePartDonetransport:
			{
				action_TRANS_tr13_FROM_HandOver_TO_GetStatusTransport_BY_takePartDonetransport(ifitem);
				return STATE_GetStatusTransport;
			}
			case CHAIN_TRANS_tr5_FROM_SendPartToNext_TO_CheckingTransportForEmpty_BY_receivedPartnext:
			{
				return STATE_CheckingTransportForEmpty;
			}
			case CHAIN_TRANS_tr14_FROM_CheckingTransportForEmpty_TO_Empty_BY_isEmptytransport:
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
				case STATE_GetStatusTransport:
					if (!(skip_entry__et)) entry_GetStatusTransport();
					/* in leaf state: return state id */
					return STATE_GetStatusTransport;
				case STATE_FullWaitingForNext:
					if (!(skip_entry__et)) entry_FullWaitingForNext();
					/* in leaf state: return state id */
					return STATE_FullWaitingForNext;
				case STATE_Empty:
					if (!(skip_entry__et)) entry_Empty();
					/* in leaf state: return state id */
					return STATE_Empty;
				case STATE_ReleasePart:
					if (!(skip_entry__et)) entry_ReleasePart();
					/* in leaf state: return state id */
					return STATE_ReleasePart;
				case STATE_SendPartToNext:
					if (!(skip_entry__et)) entry_SendPartToNext();
					/* in leaf state: return state id */
					return STATE_SendPartToNext;
				case STATE_Processing:
					if (!(skip_entry__et)) entry_Processing();
					/* in leaf state: return state id */
					return STATE_Processing;
				case STATE_HandOver:
					if (!(skip_entry__et)) entry_HandOver();
					/* in leaf state: return state id */
					return STATE_HandOver;
				case STATE_CheckingTransportForEmpty:
					if (!(skip_entry__et)) entry_CheckingTransportForEmpty();
					/* in leaf state: return state id */
					return STATE_CheckingTransportForEmpty;
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
		int chain__et = CHAIN_TRANS_INITIAL_TO__GetStatusTransport;
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
				case STATE_GetStatusTransport:
					switch(trigger__et) {
							case TRIG_transport__isEmpty:
								{
									chain__et = CHAIN_TRANS_tr1_FROM_GetStatusTransport_TO_Empty_BY_isEmptytransport;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_transport__isFull:
								{
									chain__et = CHAIN_TRANS_tr8_FROM_GetStatusTransport_TO_CP1_BY_isFulltransport;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_FullWaitingForNext:
					switch(trigger__et) {
							case TRIG_next__isEmpty:
								{
									chain__et = CHAIN_TRANS_tr3_FROM_FullWaitingForNext_TO_ReleasePart_BY_isEmptynext;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_transport__isEmpty:
								{
									chain__et = CHAIN_TRANS_tr7_FROM_FullWaitingForNext_TO_Empty_BY_isEmptytransport;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Empty:
					switch(trigger__et) {
							case TRIG_prev__getStatus:
								{
									chain__et = CHAIN_TRANS_tr2_FROM_Empty_TO_Empty_BY_getStatusprev_tr2;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_transport__isFull:
								{
									chain__et = CHAIN_TRANS_tr6_FROM_Empty_TO_FullWaitingForNext_BY_isFulltransport;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_prev__sendPart:
								{
									chain__et = CHAIN_TRANS_tr12_FROM_Empty_TO_HandOver_BY_sendPartprev;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_ReleasePart:
					switch(trigger__et) {
							case TRIG_transport__releasePartDone:
								{
									chain__et = CHAIN_TRANS_tr4_FROM_ReleasePart_TO_SendPartToNext_BY_releasePartDonetransport;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_SendPartToNext:
					switch(trigger__et) {
							case TRIG_next__receivedPart:
								{
									chain__et = CHAIN_TRANS_tr5_FROM_SendPartToNext_TO_CheckingTransportForEmpty_BY_receivedPartnext;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_Processing:
					switch(trigger__et) {
							case TRIG_job__doneProcessing:
								{
									chain__et = CHAIN_TRANS_tr11_FROM_Processing_TO_FullWaitingForNext_BY_doneProcessingjob;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_HandOver:
					switch(trigger__et) {
							case TRIG_transport__takePartDone:
								{
									chain__et = CHAIN_TRANS_tr13_FROM_HandOver_TO_GetStatusTransport_BY_takePartDonetransport;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_CheckingTransportForEmpty:
					switch(trigger__et) {
							case TRIG_transport__isEmpty:
								{
									chain__et = CHAIN_TRANS_tr14_FROM_CheckingTransportForEmpty_TO_Empty_BY_isEmptytransport;
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
