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



public class PDigOut {
	// message IDs
	public static final int MSG_MIN = 0;
	public static final int OUT_registerChannelDone = 1;
	public static final int OUT_error = 2;
	public static final int IN_set = 3;
	public static final int IN_setOn = 4;
	public static final int IN_setOff = 5;
	public static final int IN_registerChannel = 6;
	public static final int MSG_MAX = 7;


	private static String messageStrings[] = {"MIN", "registerChannelDone","error", "set","setOn","setOff","registerChannel","MAX"};

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
	static public class PDigOutPort extends PortBase {
		// constructors
		public PDigOutPort(IInterfaceItemOwner actor, String name, int localId) {
			this(actor, name, localId, 0);
		}
		public PDigOutPort(IInterfaceItemOwner actor, String name, int localId, int idx) {
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
	static public class PDigOutReplPort extends ReplicatedPortBase {
	
		public PDigOutReplPort(IInterfaceItemOwner actor, String name, int localId) {
			super(actor, name, localId);
		}
		
		public int getReplication() {
			return getNInterfaceItems();
		}
		
		public int getIndexOf(InterfaceItemBase ifitem){
				return ifitem.getIdx();
			}
		
		public PDigOutPort get(int idx) {
			return (PDigOutPort) getInterfaceItem(idx);
		}
		
		protected InterfaceItemBase createInterfaceItem(IInterfaceItemOwner rcv, String name, int lid, int idx) {
			return new PDigOutPort(rcv, name, lid, idx);
		}
		
		// outgoing messages
		public void registerChannelDone(){
			for (InterfaceItemBase item : getItems()) {
				((PDigOutPort)item).registerChannelDone();
			}
		}
		public void error(){
			for (InterfaceItemBase item : getItems()) {
				((PDigOutPort)item).error();
			}
		}
	}
	
	
	// port class
	static public class PDigOutConjPort extends PortBase {
		// constructors
		public PDigOutConjPort(IInterfaceItemOwner actor, String name, int localId) {
			this(actor, name, localId, 0);
		}
		public PDigOutConjPort(IInterfaceItemOwner actor, String name, int localId, int idx) {
			super(actor, name, localId, idx);
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
	
		
		// sent messages
		public void set(int x) {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_set]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventWithDataMessage(getPeerAddress(), IN_set, x));
		}
		public void setOn() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_setOn]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), IN_setOn));
		}
		public void setOff() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_setOff]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), IN_setOff));
		}
		public void registerChannel(int x) {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_registerChannel]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventWithDataMessage(getPeerAddress(), IN_registerChannel, x));
		}
	}
	
	// replicated port class
	static public class PDigOutConjReplPort extends ReplicatedPortBase {
	
		public PDigOutConjReplPort(IInterfaceItemOwner actor, String name, int localId) {
			super(actor, name, localId);
		}
		
		public int getReplication() {
			return getNInterfaceItems();
		}
		
		public int getIndexOf(InterfaceItemBase ifitem){
				return ifitem.getIdx();
			}
		
		public PDigOutConjPort get(int idx) {
			return (PDigOutConjPort) getInterfaceItem(idx);
		}
		
		protected InterfaceItemBase createInterfaceItem(IInterfaceItemOwner rcv, String name, int lid, int idx) {
			return new PDigOutConjPort(rcv, name, lid, idx);
		}
		
		// incoming messages
		public void set(int x){
			for (InterfaceItemBase item : getItems()) {
				((PDigOutConjPort)item).set( x);
			}
		}
		public void setOn(){
			for (InterfaceItemBase item : getItems()) {
				((PDigOutConjPort)item).setOn();
			}
		}
		public void setOff(){
			for (InterfaceItemBase item : getItems()) {
				((PDigOutConjPort)item).setOff();
			}
		}
		public void registerChannel(int x){
			for (InterfaceItemBase item : getItems()) {
				((PDigOutConjPort)item).registerChannel( x);
			}
		}
	}
	
}
