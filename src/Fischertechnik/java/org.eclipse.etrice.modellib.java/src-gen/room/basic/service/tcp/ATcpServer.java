package room.basic.service.tcp;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import room.basic.service.tcp.PTcpControl.*;
import room.basic.service.tcp.PTcpPayload.*;

/*--------------------- begin user code ---------------------*/
import java.net.ServerSocket;
import java.net.Socket;
import java.io.*;
import java.util.*;

				class ServerRxThread extends Thread{
					private int connectionId;
					private Socket sock;
					PTcpPayloadPort port;

					public ServerRxThread (int connectionId, PTcpPayloadPort port, Socket sock){
						this.sock = sock;
						this.connectionId = connectionId;
						this.port = port;
					}

					public void run(){
						try{
							InputStream in = sock.getInputStream();
							DTcpPayload d = new DTcpPayload();
							d.setConnectionId(connectionId);
							int c;
							while ((c=in.read(d.getData()))!=-1){
								d.setLength(c);
								port.receive(d);	
							}
						}catch (IOException e){
							System.err.println("ServerRx: " + e.toString());
						}
					}
				}
		
			class ServerAcceptThread extends Thread{
				private ServerSocket sock;
				private PTcpPayloadPort port;
				private ATcpServer parent;
				public ServerAcceptThread (PTcpPayloadPort port, ServerSocket sock, ATcpServer parent){
					this.sock = sock;
					this.port = port;
					this.parent = parent;
				}
				public void run(){
					int cnt=0;
					try{
						while (true){
							Socket s = sock.accept();
							parent.addOutStreamToHashmap(cnt, s.getOutputStream());
							(new ServerRxThread(cnt, port, s)).start();
							cnt++;
						}
					}catch (IOException e){
						System.err.println("Server Accept: " + e.toString());
					}
				}
			}
		
/*--------------------- end user code ---------------------*/


public class ATcpServer extends ActorClassBase {

	/*--------------------- begin user code ---------------------*/
	ServerSocket socket = null;
	InputStream in = null;
	OutputStream out = null;
	Hashtable<Integer,OutputStream> outStreams = new Hashtable<Integer,OutputStream>();
	
					synchronized protected void addOutStreamToHashmap(int cnt, OutputStream out){
						outStreams.put(cnt,out);
					}
					
	/*--------------------- end user code ---------------------*/
	
	//--------------------- ports
	protected PTcpControlPort ControlPort = null;
	protected PTcpPayloadPort PayloadPort = null;
	
	//--------------------- saps
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	public static final int IFITEM_ControlPort = 1;
	public static final int IFITEM_PayloadPort = 2;
	
	/*--------------------- attributes ---------------------*/
	int lastError;
	int payloadPortReplocation;
	/*--------------------- operations ---------------------*/
	public void stopUser() {
		try{
		if(socket != null){
		socket.close();
		}
		}catch(IOException e){
		System.err.println(e.toString());}
	}

	//--------------------- construction
	public ATcpServer(IRTObject parent, String name) {
		super(parent, name);
		setClassName("ATcpServer");
		
		// initialize attributes
		this.setLastError(0);
		this.setPayloadPortReplocation(0);

		// own ports
		ControlPort = new PTcpControlPort(this, "ControlPort", IFITEM_ControlPort);
		PayloadPort = new PTcpPayloadPort(this, "PayloadPort", IFITEM_PayloadPort);
		
		// own saps
		
		// own service implementations
		
		// sub actors
		
		// wiring
		

	}
	
	/* --------------------- attribute setters and getters */
	public void setLastError (int lastError) {
		 this.lastError = lastError;
	}
	public int getLastError () {
		return this.lastError;
	}
	public void setPayloadPortReplocation (int payloadPortReplocation) {
		 this.payloadPortReplocation = payloadPortReplocation;
	}
	public int getPayloadPortReplocation () {
		return this.payloadPortReplocation;
	}
	
	
	//--------------------- port getters
	public PTcpControlPort getControlPort (){
		return this.ControlPort;
	}
	public PTcpPayloadPort getPayloadPort (){
		return this.PayloadPort;
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
	public static final int STATE_closed = 2;
	public static final int STATE_opened = 3;
	public static final int STATE_error = 4;
	public static final int STATE_MAX = 5;
	
	/* transition chains */
	public static final int CHAIN_TRANS_INITIAL_TO__closed = 1;
	public static final int CHAIN_TRANS_tr0_FROM_closed_TO_cp0_BY_openControlPort = 2;
	public static final int CHAIN_TRANS_tr1_FROM_opened_TO_closed_BY_closeControlPort = 3;
	public static final int CHAIN_TRANS_tr3_FROM_opened_TO_opened_BY_sendPayloadPort_tr3 = 4;
	
	/* triggers */
	public static final int POLLING = 0;
	public static final int TRIG_ControlPort__open = IFITEM_ControlPort + EVT_SHIFT*PTcpControl.IN_open;
	public static final int TRIG_ControlPort__close = IFITEM_ControlPort + EVT_SHIFT*PTcpControl.IN_close;
	public static final int TRIG_PayloadPort__send = IFITEM_PayloadPort + EVT_SHIFT*PTcpPayload.IN_send;
	
	// state names
	protected static final String stateStrings[] = {
		"<no state>",
		"<top>",
		"closed",
		"opened",
		"error"
	};
		
	// history
	protected int history[] = {NO_STATE, NO_STATE, NO_STATE, NO_STATE, NO_STATE};
	
	private void setState(int new_state) {
		DebuggingService.getInstance().addActorState(this,stateStrings[new_state]);
		this.state = new_state;
	}
	
	/* Entry and Exit Codes */
	
	/* Action Codes */
	protected void action_TRANS_tr0_FROM_closed_TO_cp0_BY_openControlPort(InterfaceItemBase ifitem, DTcpControl data) {
		lastError=0;
		try{
		socket = new ServerSocket(data.TcpPort);
		(new ServerAcceptThread(PayloadPort, socket, this)).start();
		}catch(IOException e){
		System.err.println(e.toString());
		lastError=1;
		}
	}
	protected void action_TRANS_tr1_FROM_opened_TO_closed_BY_closeControlPort(InterfaceItemBase ifitem) {
		try{
			if(socket!=null){
				socket.close();
				}
			}catch(IOException e){
			System.err.println(e.toString());
		}
	}
	protected void action_TRANS_tr2_FROM_cp0_TO_opened(InterfaceItemBase ifitem, DTcpControl data) {
		ControlPort.established();
	}
	protected void action_TRANS_socketError_FROM_cp0_TO_error_COND_socketError(InterfaceItemBase ifitem, DTcpControl data) {
		ControlPort.error();
		try{
		socket.close();
		} catch(IOException e){
		System.err.println(e.toString());
		}
	}
	protected void action_TRANS_tr3_FROM_opened_TO_opened_BY_sendPayloadPort_tr3(InterfaceItemBase ifitem, DTcpPayload data) {
		try{
		outStreams.get(data.getConnectionId()).write(data.getData(),0,data.length);
		}catch(IOException e){
		System.err.println(e.toString());
		}
	}
	
	/**
	 * calls exit codes while exiting from the current state to one of its
	 * parent states while remembering the history
	 * @param current - the current state
	 * @param to - the final parent state
	 */
	private void exitTo(int current, int to) {
		while (current!=to) {
			switch (current) {
				case STATE_closed:
					this.history[STATE_TOP] = STATE_closed;
					current = STATE_TOP;
					break;
				case STATE_opened:
					this.history[STATE_TOP] = STATE_opened;
					current = STATE_TOP;
					break;
				case STATE_error:
					this.history[STATE_TOP] = STATE_error;
					current = STATE_TOP;
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
	 * @param chain - the chain ID
	 * @param generic_data - the generic data pointer
	 * @return the +/- ID of the final state either with a positive sign, that indicates to execute the state's entry code, or a negative sign vice versa
	 */
	private int executeTransitionChain(int chain, InterfaceItemBase ifitem, Object generic_data) {
		switch (chain) {
			case CHAIN_TRANS_INITIAL_TO__closed:
			{
				return STATE_closed;
			}
			case CHAIN_TRANS_tr0_FROM_closed_TO_cp0_BY_openControlPort:
			{
				DTcpControl data = (DTcpControl) generic_data;
				action_TRANS_tr0_FROM_closed_TO_cp0_BY_openControlPort(ifitem, data);
				if (lastError!=0) {
				action_TRANS_socketError_FROM_cp0_TO_error_COND_socketError(ifitem, data);
				return STATE_error;}
				else {
				action_TRANS_tr2_FROM_cp0_TO_opened(ifitem, data);
				return STATE_opened;}
			}
			case CHAIN_TRANS_tr1_FROM_opened_TO_closed_BY_closeControlPort:
			{
				action_TRANS_tr1_FROM_opened_TO_closed_BY_closeControlPort(ifitem);
				return STATE_closed;
			}
			case CHAIN_TRANS_tr3_FROM_opened_TO_opened_BY_sendPayloadPort_tr3:
			{
				DTcpPayload data = (DTcpPayload) generic_data;
				action_TRANS_tr3_FROM_opened_TO_opened_BY_sendPayloadPort_tr3(ifitem, data);
				return STATE_opened;
			}
				default:
					/* should not occur */
					break;
		}
		return NO_STATE;
	}
	
	/**
	 * calls entry codes while entering a state's history. The ID of the final leaf state is returned
	 * @param state - the state which is entered
	 * @return - the ID of the final leaf state
	 */
	private int enterHistory(int state) {
		boolean skip_entry = false;
		if (state >= STATE_MAX) {
			state =  (state - STATE_MAX);
			skip_entry = true;
		}
		while (true) {
			switch (state) {
				case STATE_closed:
					/* in leaf state: return state id */
					return STATE_closed;
				case STATE_opened:
					/* in leaf state: return state id */
					return STATE_opened;
				case STATE_error:
					/* in leaf state: return state id */
					return STATE_error;
				case STATE_TOP:
					state = this.history[STATE_TOP];
					break;
				default:
					/* should not occur */
					break;
			}
			skip_entry = false;
		}
		/* return NO_STATE; // required by CDT but detected as unreachable by JDT because of while (true) */
	}
	
	public void executeInitTransition() {
		int chain = CHAIN_TRANS_INITIAL_TO__closed;
		int next = executeTransitionChain(chain, null, null);
		next = enterHistory(next);
		setState(next);
	}
	
	/* receiveEvent contains the main implementation of the FSM */
	public void receiveEvent(InterfaceItemBase ifitem, int evt, Object generic_data) {
		int trigger = ifitem.getLocalId() + EVT_SHIFT*evt;
		int chain = NOT_CAUGHT;
		int catching_state = NO_STATE;
		
		if (!handleSystemEvent(ifitem, evt, generic_data)) {
			switch (getState()) {
				case STATE_closed:
					switch(trigger) {
							case TRIG_ControlPort__open:
								{
									chain = CHAIN_TRANS_tr0_FROM_closed_TO_cp0_BY_openControlPort;
									catching_state = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_opened:
					switch(trigger) {
							case TRIG_ControlPort__close:
								{
									chain = CHAIN_TRANS_tr1_FROM_opened_TO_closed_BY_closeControlPort;
									catching_state = STATE_TOP;
								}
							break;
							case TRIG_PayloadPort__send:
								{
									chain = CHAIN_TRANS_tr3_FROM_opened_TO_opened_BY_sendPayloadPort_tr3;
									catching_state = STATE_TOP;
								}
							break;
							default:
								/* should not occur */
								break;
					}
					break;
				case STATE_error:
					break;
				default:
					/* should not occur */
					break;
			}
		}
		if (chain != NOT_CAUGHT) {
			exitTo(getState(), catching_state);
			{
				int next = executeTransitionChain(chain, ifitem, generic_data);
				next = enterHistory(next);
				setState(next);
			}
		}
	}
};
