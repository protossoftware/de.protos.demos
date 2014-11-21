package protos.automation.service.io;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import room.basic.service.timing.*;
import protos.automation.service.io.PDigIn.*;
import protos.automation.service.io.PDigInSim.*;
import protos.automation.service.io.PDigOut.*;
import protos.automation.service.io.PDigOutSim.*;
import protos.automation.service.io.PIOEvent.*;
import room.basic.service.timing.PTimer.*;

/*--------------------- begin user code ---------------------*/
import de.protos.automation.io.modbus.jamod.ModbusIODriver;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.HashMap;
/*--------------------- end user code ---------------------*/


public class AIOService extends ActorClassBase {

	/*--------------------- begin user code ---------------------*/
	
					private HashMap<Integer, InterfaceItemBase> input2Port = new HashMap<Integer, InterfaceItemBase>();
					private HashMap<Integer, InterfaceItemBase> outputSim2Port = new HashMap<Integer, InterfaceItemBase>();
					// TODOTS: configurable initialization of IP and Port 
					ModbusIODriver driver = null;
					int inputRange, outputRange;
					boolean listsInitialized = false;
					
	/*--------------------- end user code ---------------------*/
	
	//--------------------- ports
	protected PIOEventConjPort io_driver = null;
	protected PDigInSimReplPort dig_in_sim = null;
	protected PDigOutSimReplPort dig_out_sim = null;
	
	//--------------------- saps
	protected PTimerConjPort polling_timer = null;
	
	//--------------------- services
	protected PDigInReplPort dig_in = null;
	protected PDigOutReplPort dig_out = null;
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_io_driver = 1;
	public static final int IFITEM_dig_in_sim = 2;
	public static final int IFITEM_dig_out_sim = 3;
	public static final int IFITEM_polling_timer = 4;
	public static final int IFITEM_dig_in = 5;
	public static final int IFITEM_dig_out = 6;
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/
	public void initializeDriverAndData() {
		
						inputRange = 32;
						outputRange = 32;
				
						// TODOTS: this has to be made much more efficient on a lower level
						try {
							driver = new ModbusIODriver(InetAddress.getByName("192.168.1.140"),502, inputRange, outputRange);
							driver.connect();
							executeIO();
						} catch (UnknownHostException e) {
							e.printStackTrace();
						}
	}
	public void checkHWInputs() {
		
						if (listsInitialized) {
							driver.readInputBufferFromHW();
							for (int channel = 0; channel < inputRange; channel++) {
								if (driver.hasInputChanged(channel)) {
									//System.out.print("Channel " + channel + "changed: "+ (driver.getInput(channel)? "1" : "0"));
									// only if value changed an event is triggered
									PDigInPort port = (PDigInPort) input2Port.get(channel);
									boolean value = driver.getInput(channel);
									if (port!=null){
										port.inputChanged(value ? 1 : 0);
									}
								} else {
									// no changes -> no events
								}
							}
							driver.invalidateInputs();
						} else {
							// the first time the list is only filled without change events
							driver.readInputBufferFromHW();
							driver.invalidateInputs();
							listsInitialized = true;
						}
	}
	public void setHWOutputs() {
		
						// write all outputs from list to hardware 
						driver.writeOutputBufferToHW();
	}
	public void executeIO() {
		
						setHWOutputs();
						checkHWInputs();
	}

	//--------------------- construction
	public AIOService(IRTObject parent, String name) {
		super(parent, name);
		setClassName("AIOService");
		
		// initialize attributes

		// own ports
		io_driver = new PIOEventConjPort(this, "io_driver", IFITEM_io_driver);
		dig_in_sim = new PDigInSimReplPort(this, "dig_in_sim", IFITEM_dig_in_sim);
		dig_out_sim = new PDigOutSimReplPort(this, "dig_out_sim", IFITEM_dig_out_sim);
		
		// own saps
		polling_timer = new PTimerConjPort(this, "polling_timer", IFITEM_polling_timer, 0);
		
		// own service implementations
		dig_in = new PDigInReplPort(this, "dig_in", IFITEM_dig_in);
		dig_out = new PDigOutReplPort(this, "dig_out", IFITEM_dig_out);
		
		// sub actors
		
		// wiring
		
		

	}
	
	/* --------------------- attribute setters and getters */
	
	
	//--------------------- port getters
	public PIOEventConjPort getIo_driver (){
		return this.io_driver;
	}
	public PDigInSimReplPort getDig_in_sim (){
		return this.dig_in_sim;
	}
	public PDigOutSimReplPort getDig_out_sim (){
		return this.dig_out_sim;
	}
	public PTimerConjPort getPolling_timer (){
		return this.polling_timer;
	}
	public PDigInReplPort getDig_in (){
		return this.dig_in;
	}
	public PDigOutReplPort getDig_out (){
		return this.dig_out;
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
	public static final int STATE_MAX = 3;
	
	/* transition chains */
	public static final int CHAIN_TRANS_INITIAL_TO__Idle = 1;
	public static final int CHAIN_TRANS_tr11_FROM_Idle_TO_Idle_BY_getStatusdig_in_tr11 = 2;
	public static final int CHAIN_TRANS_tr1_FROM_Idle_TO_Idle_BY_registerChanneldig_in_tr1 = 3;
	public static final int CHAIN_TRANS_tr2_FROM_Idle_TO_Idle_BY_registerChanneldig_out_tr2 = 4;
	public static final int CHAIN_TRANS_tr3_FROM_Idle_TO_Idle_BY_ioEventio_driver_tr3 = 5;
	public static final int CHAIN_TRANS_tr4_FROM_Idle_TO_Idle_BY_setOndig_out_tr4 = 6;
	public static final int CHAIN_TRANS_tr5_FROM_Idle_TO_Idle_BY_setOffdig_out_tr5 = 7;
	public static final int CHAIN_TRANS_tr6_FROM_Idle_TO_Idle_BY_setdig_out_tr6 = 8;
	public static final int CHAIN_TRANS_tr7_FROM_Idle_TO_Idle_BY_timeoutpolling_timer_tr7 = 9;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_io_driver__ioEvent = IFITEM_io_driver + EVT_SHIFT*PIOEvent.OUT_ioEvent;
	public static final int TRIG_dig_in_sim__registerChannel = IFITEM_dig_in_sim + EVT_SHIFT*PDigInSim.IN_registerChannel;
	public static final int TRIG_dig_in_sim__set = IFITEM_dig_in_sim + EVT_SHIFT*PDigInSim.IN_set;
	public static final int TRIG_dig_in_sim__setOn = IFITEM_dig_in_sim + EVT_SHIFT*PDigInSim.IN_setOn;
	public static final int TRIG_dig_in_sim__setOff = IFITEM_dig_in_sim + EVT_SHIFT*PDigInSim.IN_setOff;
	public static final int TRIG_dig_out_sim__registerChannel = IFITEM_dig_out_sim + EVT_SHIFT*PDigOutSim.IN_registerChannel;
	public static final int TRIG_dig_out_sim__getStatus = IFITEM_dig_out_sim + EVT_SHIFT*PDigOutSim.IN_getStatus;
	public static final int TRIG_polling_timer__timeout = IFITEM_polling_timer + EVT_SHIFT*PTimer.OUT_timeout;
	public static final int TRIG_polling_timer__internalTimer = IFITEM_polling_timer + EVT_SHIFT*PTimer.OUT_internalTimer;
	public static final int TRIG_polling_timer__internalTimeout = IFITEM_polling_timer + EVT_SHIFT*PTimer.OUT_internalTimeout;
	public static final int TRIG_dig_in__getStatus = IFITEM_dig_in + EVT_SHIFT*PDigIn.IN_getStatus;
	public static final int TRIG_dig_in__registerChannel = IFITEM_dig_in + EVT_SHIFT*PDigIn.IN_registerChannel;
	public static final int TRIG_dig_out__set = IFITEM_dig_out + EVT_SHIFT*PDigOut.IN_set;
	public static final int TRIG_dig_out__setOn = IFITEM_dig_out + EVT_SHIFT*PDigOut.IN_setOn;
	public static final int TRIG_dig_out__setOff = IFITEM_dig_out + EVT_SHIFT*PDigOut.IN_setOff;
	public static final int TRIG_dig_out__registerChannel = IFITEM_dig_out + EVT_SHIFT*PDigOut.IN_registerChannel;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"Idle"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	
	/* Action Codes */
	protected void action_TRANS_INITIAL_TO__Idle() {
		
								initializeDriverAndData();
								polling_timer.startTimer(100);  // Timer for polling IOs;
	}
	protected void action_TRANS_tr1_FROM_Idle_TO_Idle_BY_registerChanneldig_in_tr1(InterfaceItemBase ifitem, int x) {
		input2Port.put(x, ifitem);
		((PDigInPort)ifitem).setChannel(x);
	}
	protected void action_TRANS_tr11_FROM_Idle_TO_Idle_BY_getStatusdig_in_tr11(InterfaceItemBase ifitem) {
		
								PDigInPort port = ((PDigInPort) ifitem);
								int channel = port.getChannel();
								boolean value = driver.getInput(channel);
								port.inputChanged(value ? 1 : 0);
	}
	protected void action_TRANS_tr2_FROM_Idle_TO_Idle_BY_registerChanneldig_out_tr2(InterfaceItemBase ifitem, int x) {
		((PDigOutPort)ifitem).setChannel(x);
	}
	protected void action_TRANS_tr3_FROM_Idle_TO_Idle_BY_ioEventio_driver_tr3(InterfaceItemBase ifitem) {
		// TODOTS: delete unused transition and port
	}
	protected void action_TRANS_tr4_FROM_Idle_TO_Idle_BY_setOndig_out_tr4(InterfaceItemBase ifitem) {
		
								driver.setOutput(((PDigOutPort) ifitem).getChannel(), true);
	}
	protected void action_TRANS_tr5_FROM_Idle_TO_Idle_BY_setOffdig_out_tr5(InterfaceItemBase ifitem) {
		
								driver.setOutput(((PDigOutPort) ifitem).getChannel(), false);
	}
	protected void action_TRANS_tr6_FROM_Idle_TO_Idle_BY_setdig_out_tr6(InterfaceItemBase ifitem, int x) {
		
								driver.setOutput(((PDigOutPort) ifitem).getChannel(), x!=0);
	}
	protected void action_TRANS_tr7_FROM_Idle_TO_Idle_BY_timeoutpolling_timer_tr7(InterfaceItemBase ifitem) {
		executeIO();
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
				action_TRANS_INITIAL_TO__Idle();
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr1_FROM_Idle_TO_Idle_BY_registerChanneldig_in_tr1:
			{
				int x = (Integer) generic_data__et;
				action_TRANS_tr1_FROM_Idle_TO_Idle_BY_registerChanneldig_in_tr1(ifitem, x);
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr11_FROM_Idle_TO_Idle_BY_getStatusdig_in_tr11:
			{
				action_TRANS_tr11_FROM_Idle_TO_Idle_BY_getStatusdig_in_tr11(ifitem);
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr2_FROM_Idle_TO_Idle_BY_registerChanneldig_out_tr2:
			{
				int x = (Integer) generic_data__et;
				action_TRANS_tr2_FROM_Idle_TO_Idle_BY_registerChanneldig_out_tr2(ifitem, x);
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr3_FROM_Idle_TO_Idle_BY_ioEventio_driver_tr3:
			{
				action_TRANS_tr3_FROM_Idle_TO_Idle_BY_ioEventio_driver_tr3(ifitem);
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr4_FROM_Idle_TO_Idle_BY_setOndig_out_tr4:
			{
				action_TRANS_tr4_FROM_Idle_TO_Idle_BY_setOndig_out_tr4(ifitem);
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr5_FROM_Idle_TO_Idle_BY_setOffdig_out_tr5:
			{
				action_TRANS_tr5_FROM_Idle_TO_Idle_BY_setOffdig_out_tr5(ifitem);
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr6_FROM_Idle_TO_Idle_BY_setdig_out_tr6:
			{
				int x = (Integer) generic_data__et;
				action_TRANS_tr6_FROM_Idle_TO_Idle_BY_setdig_out_tr6(ifitem, x);
				return STATE_Idle;
			}
			case CHAIN_TRANS_tr7_FROM_Idle_TO_Idle_BY_timeoutpolling_timer_tr7:
			{
				action_TRANS_tr7_FROM_Idle_TO_Idle_BY_timeoutpolling_timer_tr7(ifitem);
				return STATE_Idle;
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
							case TRIG_dig_in__registerChannel:
								{
									chain__et = CHAIN_TRANS_tr1_FROM_Idle_TO_Idle_BY_registerChanneldig_in_tr1;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_dig_in__getStatus:
								{
									chain__et = CHAIN_TRANS_tr11_FROM_Idle_TO_Idle_BY_getStatusdig_in_tr11;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_dig_out__registerChannel:
								{
									chain__et = CHAIN_TRANS_tr2_FROM_Idle_TO_Idle_BY_registerChanneldig_out_tr2;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_io_driver__ioEvent:
								{
									chain__et = CHAIN_TRANS_tr3_FROM_Idle_TO_Idle_BY_ioEventio_driver_tr3;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_dig_out__setOn:
								{
									chain__et = CHAIN_TRANS_tr4_FROM_Idle_TO_Idle_BY_setOndig_out_tr4;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_dig_out__setOff:
								{
									chain__et = CHAIN_TRANS_tr5_FROM_Idle_TO_Idle_BY_setOffdig_out_tr5;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_dig_out__set:
								{
									chain__et = CHAIN_TRANS_tr6_FROM_Idle_TO_Idle_BY_setdig_out_tr6;
									catching_state__et = STATE_TOP;
								}
							break;
							case TRIG_polling_timer__timeout:
								{
									chain__et = CHAIN_TRANS_tr7_FROM_Idle_TO_Idle_BY_timeoutpolling_timer_tr7;
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
