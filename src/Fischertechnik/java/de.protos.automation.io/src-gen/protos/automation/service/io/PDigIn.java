package protos.automation.service.io;

import org.eclipse.etrice.runtime.java.messaging.Message;
import org.eclipse.etrice.runtime.java.modelbase.EventMessage;
import org.eclipse.etrice.runtime.java.modelbase.EventWithDataMessage;
import org.eclipse.etrice.runtime.java.modelbase.IInterfaceItemOwner;
import org.eclipse.etrice.runtime.java.modelbase.InterfaceItemBase;
import org.eclipse.etrice.runtime.java.modelbase.PortBase;
import org.eclipse.etrice.runtime.java.modelbase.ReplicatedPortBase;
import org.eclipse.etrice.runtime.java.debugging.DebuggingService;
import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;



public class PDigIn {
	// message IDs
	public static final int MSG_MIN = 0;
	public static final int OUT_inputChanged = 1;
	public static final int OUT_registerChannelDone = 2;
	public static final int OUT_error = 3;
	public static final int IN_getStatus = 4;
	public static final int IN_registerChannel = 5;
	public static final int MSG_MAX = 6;


	private static String messageStrings[] = {"MIN", "inputChanged","registerChannelDone","error", "getStatus","registerChannel","MAX"};

	public String getMessageString(int msg_id) {
		if (msg_id<MSG_MIN || msg_id>MSG_MAX+1){
			// id out of range
			return "Message ID out of range";
		}
		else{
			return messageStrings[msg_id];
		}
	}

	
	// port class
	static public class PDigInPort extends PortBase {
		// constructors
		public PDigInPort(IInterfaceItemOwner actor, String name, int localId) {
			this(actor, name, localId, 0);
		}
		public PDigInPort(IInterfaceItemOwner actor, String name, int localId, int idx) {
			super(actor, name, localId, idx);
			// initialize attributes
			DebuggingService.getInstance().addPortInstance(this);
		}
		
		public void destroy() {
			DebuggingService.getInstance().removePortInstance(this);
			super.destroy();
		}
	
		@Override
		public void receive(Message m) {
			if (!(m instanceof EventMessage))
				return;
			EventMessage msg = (EventMessage) m;
			if (0 < msg.getEvtId() && msg.getEvtId() < MSG_MAX) {
				DebuggingService.getInstance().addMessageAsyncIn(getPeerAddress(), getAddress(), messageStrings[msg.getEvtId()]);
				if (msg instanceof EventWithDataMessage)
					getActor().receiveEvent(this, msg.getEvtId(), ((EventWithDataMessage)msg).getData());
				else
					getActor().receiveEvent(this, msg.getEvtId(), null);
			}
	}
	
		/*--------------------- attributes ---------------------*/
		int channel;
		/* --------------------- attribute setters and getters */
		public void setChannel (int channel) {
			 this.channel = channel;
		}
		public int getChannel () {
			return this.channel;
		}
		/*--------------------- operations ---------------------*/
		
		// sent messages
		public void inputChanged(int x) {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[OUT_inputChanged]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventWithDataMessage(getPeerAddress(), OUT_inputChanged, x));
		}
		public void registerChannelDone() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[OUT_registerChannelDone]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), OUT_registerChannelDone));
		}
		public void error() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[OUT_error]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), OUT_error));
		}
	}
	
	// replicated port class
	static public class PDigInReplPort extends ReplicatedPortBase {
	
		public PDigInReplPort(IInterfaceItemOwner actor, String name, int localId) {
			super(actor, name, localId);
		}
		
		public int getReplication() {
			return getNInterfaceItems();
		}
		
		public int getIndexOf(InterfaceItemBase ifitem){
				return ifitem.getIdx();
			}
		
		public PDigInPort get(int idx) {
			return (PDigInPort) getInterfaceItem(idx);
		}
		
		protected InterfaceItemBase createInterfaceItem(IInterfaceItemOwner rcv, String name, int lid, int idx) {
			return new PDigInPort(rcv, name, lid, idx);
		}
		
		// outgoing messages
		public void inputChanged(int x){
			for (InterfaceItemBase item : getItems()) {
				((PDigInPort)item).inputChanged( x);
			}
		}
		public void registerChannelDone(){
			for (InterfaceItemBase item : getItems()) {
				((PDigInPort)item).registerChannelDone();
			}
		}
		public void error(){
			for (InterfaceItemBase item : getItems()) {
				((PDigInPort)item).error();
			}
		}
	}
	
	
	// port class
	static public class PDigInConjPort extends PortBase {
		// constructors
		public PDigInConjPort(IInterfaceItemOwner actor, String name, int localId) {
			this(actor, name, localId, 0);
		}
		public PDigInConjPort(IInterfaceItemOwner actor, String name, int localId, int idx) {
			super(actor, name, localId, idx);
			// initialize attributes
			DebuggingService.getInstance().addPortInstance(this);
		}
		
		public void destroy() {
			DebuggingService.getInstance().removePortInstance(this);
			super.destroy();
		}
	
		@Override
		public void receive(Message m) {
			if (!(m instanceof EventMessage))
				return;
			EventMessage msg = (EventMessage) m;
			if (0 < msg.getEvtId() && msg.getEvtId() < MSG_MAX) {
				DebuggingService.getInstance().addMessageAsyncIn(getPeerAddress(), getAddress(), messageStrings[msg.getEvtId()]);
				switch (msg.getEvtId()) {
					case OUT_inputChanged:
					{
						value = (Integer)((EventWithDataMessage) msg).getData();
										getActor().receiveEvent(this, msg.getEvtId(),((EventWithDataMessage) msg).getData());
					}
					break;
					default:
				if (msg instanceof EventWithDataMessage)
					getActor().receiveEvent(this, msg.getEvtId(), ((EventWithDataMessage)msg).getData());
				else
					getActor().receiveEvent(this, msg.getEvtId(), null);
				}
			}
	}
	
		/*--------------------- attributes ---------------------*/
		int value;
		/* --------------------- attribute setters and getters */
		public void setValue (int value) {
			 this.value = value;
		}
		public int getValue () {
			return this.value;
		}
		/*--------------------- operations ---------------------*/
		public boolean isOn() {
			return value!=0;
		}
		public boolean isOff() {
			return value==0;
		}
		
		// sent messages
		public void getStatus() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_getStatus]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), IN_getStatus));
		}
		public void registerChannel(int x) {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_registerChannel]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventWithDataMessage(getPeerAddress(), IN_registerChannel, x));
		}
	}
	
	// replicated port class
	static public class PDigInConjReplPort extends ReplicatedPortBase {
	
		public PDigInConjReplPort(IInterfaceItemOwner actor, String name, int localId) {
			super(actor, name, localId);
		}
		
		public int getReplication() {
			return getNInterfaceItems();
		}
		
		public int getIndexOf(InterfaceItemBase ifitem){
				return ifitem.getIdx();
			}
		
		public PDigInConjPort get(int idx) {
			return (PDigInConjPort) getInterfaceItem(idx);
		}
		
		protected InterfaceItemBase createInterfaceItem(IInterfaceItemOwner rcv, String name, int lid, int idx) {
			return new PDigInConjPort(rcv, name, lid, idx);
		}
		
		// incoming messages
		public void getStatus(){
			for (InterfaceItemBase item : getItems()) {
				((PDigInConjPort)item).getStatus();
			}
		}
		public void registerChannel(int x){
			for (InterfaceItemBase item : getItems()) {
				((PDigInConjPort)item).registerChannel( x);
			}
		}
	}
	
}
