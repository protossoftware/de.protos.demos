package GenericLineElements;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import Actuators.*;
import AutomationProtocols.*;
import protos.automation.service.io.*;
import room.basic.service.timing.*;
import protos.automation.service.io.PDigIn.*;
import protos.automation.service.io.PDigOut.*;
import AutomationProtocols.PDriveLR.*;
import room.basic.service.timing.PTimer.*;
import AutomationProtocols.PTransport.*;

/*--------------------- begin user code ---------------------*/
import de.protos.automation.demos.fischertechnik.config.*;
/*--------------------- end user code ---------------------*/


public class BeltWithEndsensor extends ActorClassBase {

	
	//--------------------- ports
	protected PTransportPort fkt = null;
	protected PDriveLRConjPort motor = null;
	
	//--------------------- saps
	protected PTimerConjPort timeout = null;
	protected PDigInConjPort sensor = null;
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_fkt = 2;
	public static final int IFITEM_motor = 1;
	public static final int IFITEM_timeout = 3;
	public static final int IFITEM_sensor = 4;
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public BeltWithEndsensor(IRTObject parent, String name) {
		super(parent, name);
		setClassName("BeltWithEndsensor");
		
		// initialize attributes

		// own ports
		fkt = new PTransportPort(this, "fkt", IFITEM_fkt);
		motor = new PDriveLRConjPort(this, "motor", IFITEM_motor);
		
		// own saps
		timeout = new PTimerConjPort(this, "timeout", IFITEM_timeout, 0);
		sensor = new PDigInConjPort(this, "sensor", IFITEM_sensor, 0);
		
		// own service implementations
		
		// sub actors
		DebuggingService.getInstance().addMessageActorCreate(this, "BeltDrive");
		new DriveLR(this, "BeltDrive");
		
		// wiring
		InterfaceItemBase.connect(this, "BeltDrive/fct", "motor");
		
		

	}
	
	/* --------------------- attribute setters and getters */
	
	
	//--------------------- port getters
	public PTransportPort getFkt (){
		return this.fkt;
	}
	public PDriveLRConjPort getMotor (){
		return this.motor;
	}
	public PTimerConjPort getTimeout (){
		return this.timeout;
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
	public static final int STATE_Full = 2;
	public static final int STATE_MoveUntilSensorOrTimeout = 3;
	public static final int STATE_Empty = 4;
	public static final int STATE_GetSensorStatus = 5;
	public static final int STATE_MoveUntilSensorOff = 6;
	public static final int STATE_ExtendedMove = 7;
	public static final int STATE_MAX = 8;
	
	/* transition chains */
	public static final int CHAIN_TRANS_INITIAL_TO__GetSensorStatus = 1;
	public static final int CHAIN_TRANS_tr10_FROM_Full_TO_MoveUntilSensorOff_BY_releasePartfkt = 2;
	public static final int CHAIN_TRANS_tr11_FROM_Empty_TO_MoveUntilSensorOrTimeout_BY_takePartfkt = 3;
	public static final int CHAIN_TRANS_tr12_FROM_MoveUntilSensorOff_TO_ExtendedMove_BY_inputChangedsensor = 4;
	public static final int CHAIN_TRANS_tr13_FROM_ExtendedMove_TO_Empty_BY_timeouttimeout = 5;
	public static final int CHAIN_TRANS_tr2_FROM_MoveUntilSensorOrTimeout_TO_Full_BY_inputChangedsensor = 6;
	public static final int CHAIN_TRANS_tr3_FROM_MoveUntilSensorOrTimeout_TO_Empty_BY_timeouttimeout = 7;
	public static final int CHAIN_TRANS_tr4_FROM_GetSensorStatus_TO_CP1_BY_inputChangedsensor = 8;
	public static final int CHAIN_TRANS_tr6_FROM_Empty_TO_Full_BY_inputChangedsensor = 9;
	public static final int CHAIN_TRANS_tr7_FROM_Full_TO_Empty_BY_inputChangedsensor = 10;
	public static final int CHAIN_TRANS_tr8_FROM_Full_TO_Full_BY_getStatusfkt_tr8 = 11;
	public static final int CHAIN_TRANS_tr9_FROM_Empty_TO_Empty_BY_getStatusfkt_tr9 = 12;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_fkt__getStatus = IFITEM_fkt + EVT_SHIFT*PTransport.IN_getStatus;
	public static final int TRIG_fkt__releasePart = IFITEM_fkt + EVT_SHIFT*PTransport.IN_releasePart;
	public static final int TRIG_fkt__takePart = IFITEM_fkt + EVT_SHIFT*PTransport.IN_takePart;
	public static final int TRIG_timeout__timeout = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_timeout;
	public static final int TRIG_timeout__internalTimer = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_internalTimer;
	public static final int TRIG_timeout__internalTimeout = IFITEM_timeout + EVT_SHIFT*PTimer.OUT_internalTimeout;
	public static final int TRIG_sensor__inputChanged = IFITEM_sensor + EVT_SHIFT*PDigIn.OUT_inputChanged;
	public static final int TRIG_sensor__registerChannelDone = IFITEM_sensor + EVT_SHIFT*PDigIn.OUT_registerChannelDone;
	public static final int TRIG_sensor__error = IFITEM_sensor + EVT_SHIFT*PDigIn.OUT_error;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"Full",
		"MoveUntilSensorOrTimeout",
		"Empty",
		"GetSensorStatus",
		"MoveUntilSensorOff",
		"ExtendedMove"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	protected void entry_Full() {
		motor.stop();
		fkt.isFull();
	}
	protected void entry_MoveUntilSensorOrTimeout() {
		motor.start();
		timeout.startTimeout(5000);
	}
	protected void entry_Empty() {
		motor.stop();
		fkt.isEmpty();
	}
	protected void entry_GetSensorStatus() {
		sensor.getStatus();
	}
	protected void entry_MoveUntilSensorOff() {
		motor.start();
		timeout.startTimeout(3000);
	}
	protected void exit_MoveUntilSensorOff() {
		timeout.kill();
	}
	protected void entry_ExtendedMove() {
		timeout.startTimeout(1000);
	}
	
	/* Action Codes */
	protected void action_TRANS_tr2_FROM_MoveUntilSensorOrTimeout_TO_Full_BY_inputChangedsensor(InterfaceItemBase ifitem, int x) {
		fkt.takePartDone();
	}
	protected void action_TRANS_INITIAL_TO__GetSensorStatus() {
		FischertechnikConfiguration config = FischertechnikConfiguration.getInstance();
		sensor.registerChannel(config.getIntValue(getInstancePath(), "sensor"));
	}
	protected void action_TRANS_tr12_FROM_MoveUntilSensorOff_TO_ExtendedMove_BY_inputChangedsensor(InterfaceItemBase ifitem, int x) {
		fkt.releasePartDone();
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
				case STATE_Full:
					this.history[STATE_TOP] = STATE_Full;
					current__et = STATE_TOP;
					break;
				case STATE_MoveUntilSensorOrTimeout:
					this.history[STATE_TOP] = STATE_MoveUntilSensorOrTimeout;
					current__et = STATE_TOP;
					break;
				case STATE_Empty:
					this.history[STATE_TOP] = STATE_Empty;
					current__et = STATE_TOP;
					break;
				case STATE_GetSensorStatus:
					this.history[STATE_TOP] = STATE_GetSensorStatus;
					current__et = STATE_TOP;
					break;
				case STATE_MoveUntilSensorOff:
					exit_MoveUntilSensorOff();
					this.history[STATE_TOP] = STATE_MoveUntilSensorOff;
					current__et = STATE_TOP;
					break;
				case STATE_ExtendedMove:
					this.history[STATE_TOP] = STATE_ExtendedMove;
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
			case CHAIN_TRANS_tr2_FROM_MoveUntilSensorOrTimeout_TO_Full_BY_inputChangedsensor:
			{
				int x = (Integer) generic_data__et;
				action_TRANS_tr2_FROM_MoveUntilSensorOrTimeout_TO_Full_BY_inputChangedsensor(ifitem, x);
				return STATE_Full;
			}
			case CHAIN_TRANS_tr3_FROM_MoveUntilSensorOrTimeout_TO_Empty_BY_timeouttimeout:
			{
				return STATE_Empty;
			}
			case CHAIN_TRANS_tr4_FROM_GetSensorStatus_TO_CP1_BY_inputChangedsensor:
			{
				int x = (Integer) generic_data__et;
				if (x==0) {
				return STATE_Full;}
				else {
				return STATE_MoveUntilSensorOrTimeout;}
			}
			case CHAIN_TRANS_INITIAL_TO__GetSensorStatus:
			{
				action_TRANS_INITIAL_TO__GetSensorStatus();
				return STATE_GetSensorStatus;
			}
			case CHAIN_TRANS_tr6_FROM_Empty_TO_Full_BY_inputChangedsensor:
			{
				int x = (Integer) generic_data__et;
				return STATE_Full;
			}
			case CHAIN_TRANS_tr7_FROM_Full_TO_Empty_BY_inputChangedsensor:
			{
				int x = (Integer) generic_data__et;
				return STATE_Empty;
			}
			case CHAIN_TRANS_tr8_FROM_Full_TO_Full_BY_getStatusfkt_tr8:
			{
				return STATE_Full;
			}
			case CHAIN_TRANS_tr9_FROM_Empty_TO_Empty_BY_getStatusfkt_tr9:
			{
				return STATE_Empty;
			}
			case CHAIN_TRANS_tr10_FROM_Full_TO_MoveUntilSensorOff_BY_releasePartfkt:
			{
				return STATE_MoveUntilSensorOff;
			}
			case CHAIN_TRANS_tr11_FROM_Empty_TO_MoveUntilSensorOrTimeout_BY_takePartfkt:
			{
				return STATE_MoveUntilSensorOrTimeout;
			}
			case CHAIN_TRANS_tr12_FROM_MoveUntilSensorOff_TO_ExtendedMove_BY_inputChangedsensor:
			{
				int x = (Integer) generic_data__et;
				action_TRANS_tr12_FROM_MoveUntilSensorOff_TO_ExtendedMove_BY_inputChangedsensor(ifitem, x);
				return STATE_ExtendedMove;
			}
			case CHAIN_TRANS_tr13_FROM_ExtendedMove_TO_Empty_BY_timeouttimeout:
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
				case STATE_Full:
					if (!(skip_entry__et)) entry_Full();
					/* in leaf state: return state id */
					return STATE_Full;
				case STATE_MoveUntilSensorOrTimeout:
					if (!(skip_entry__et)) entry_MoveUntilSensorOrTimeout();
					/* in leaf state: return state id */
					return STATE_MoveUntilSensorOrTimeout;
				case STATE_Empty:
					if (!(skip_entry__et)) entry_Empty();
					/* in leaf state: return state id */
					return STATE_Empty;
				case STATE_GetSensorStatus:
					if (!(skip_entry__et)) entry_GetSensorStatus();
					/* in leaf state: return state id */
					return STATE_GetSensorStatus;
				case STATE_MoveUntilSensorOff:
					if (!(skip_entry__et)) entry_MoveUntilSensorOff();
					/* in leaf state: return state id */
					return STATE_MoveUntilSensorOff;
				case STATE_ExtendedMove:
					if (!(skip_entry__et)) entry_ExtendedMove();
					/* in leaf state: return state id */
					return STATE_ExtendedMove;
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
		int chain__et = CHAIN_TRANS_INITIAL_TO__GetSensorStatus;
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
				case STATE_Full:
					switch(trigger__et) {
							case TRIG_sensor__inputChanged:
								{ int x = (Integer) generic_data__et;
								if (x==1)
								{
									chain__et = CHAIN_TRANS_tr7_FROM_Full_TO_Empty_BY_inputChangedsensor;
									catching_state__et = STATE_TOP;
								}
								}
							break;
							case TRIG_fkt__getStatus:
								{
									chain__et = CHAIN_TRANS_tr8_FROM_Full_TO_Full_BY_getStatusfkt_tr8;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_fkt__releasePart:
								{
									chain__et = CHAIN_TRANS_tr10_FROM_Full_TO_MoveUntilSensorOff_BY_releasePartfkt;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_MoveUntilSensorOrTimeout:
					switch(trigger__et) {
							case TRIG_sensor__inputChanged:
								{ int x = (Integer) generic_data__et;
								if (x==0)
								{
									chain__et = CHAIN_TRANS_tr2_FROM_MoveUntilSensorOrTimeout_TO_Full_BY_inputChangedsensor;
									catching_state__et = STATE_TOP;
								}
								}
							break;
							case TRIG_timeout__timeout:
								{
									chain__et = CHAIN_TRANS_tr3_FROM_MoveUntilSensorOrTimeout_TO_Empty_BY_timeouttimeout;
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
							case TRIG_sensor__inputChanged:
								{ int x = (Integer) generic_data__et;
								if (x==0)
								{
									chain__et = CHAIN_TRANS_tr6_FROM_Empty_TO_Full_BY_inputChangedsensor;
									catching_state__et = STATE_TOP;
								}
								}
							break;
							case TRIG_fkt__getStatus:
								{
									chain__et = CHAIN_TRANS_tr9_FROM_Empty_TO_Empty_BY_getStatusfkt_tr9;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_fkt__takePart:
								{
									chain__et = CHAIN_TRANS_tr11_FROM_Empty_TO_MoveUntilSensorOrTimeout_BY_takePartfkt;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_GetSensorStatus:
					switch(trigger__et) {
							case TRIG_sensor__inputChanged:
								{
									chain__et = CHAIN_TRANS_tr4_FROM_GetSensorStatus_TO_CP1_BY_inputChangedsensor;
									catching_state__et = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_MoveUntilSensorOff:
					switch(trigger__et) {
							case TRIG_sensor__inputChanged:
								{ int x = (Integer) generic_data__et;
								if (x==1)
								{
									chain__et = CHAIN_TRANS_tr12_FROM_MoveUntilSensorOff_TO_ExtendedMove_BY_inputChangedsensor;
									catching_state__et = STATE_TOP;
								}
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_ExtendedMove:
					switch(trigger__et) {
							case TRIG_timeout__timeout:
								{
									chain__et = CHAIN_TRANS_tr13_FROM_ExtendedMove_TO_Empty_BY_timeouttimeout;
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
