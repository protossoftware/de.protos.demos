package AutomationProtocols;

import org.eclipse.etrice.runtime.java.messaging.Message;
import org.eclipse.etrice.runtime.java.modelbase.EventMessage;
import org.eclipse.etrice.runtime.java.modelbase.EventWithDataMessage;
import org.eclipse.etrice.runtime.java.modelbase.IInterfaceItemOwner;
import org.eclipse.etrice.runtime.java.modelbase.InterfaceItemBase;
import org.eclipse.etrice.runtime.java.modelbase.PortBase;
import org.eclipse.etrice.runtime.java.modelbase.ReplicatedPortBase;
import org.eclipse.etrice.runtime.java.debugging.DebuggingService;
import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;



public class PTransport {
	// message IDs
	public static final int MSG_MIN = 0;
	public static final int OUT_isFull = 1;
	public static final int OUT_isEmpty = 2;
	public static final int OUT_releasePartDone = 3;
	public static final int OUT_takePartDone = 4;
	public static final int IN_getStatus = 5;
	public static final int IN_releasePart = 6;
	public static final int IN_takePart = 7;
	public static final int MSG_MAX = 8;


	private static String messageStrings[] = {"MIN", "isFull","isEmpty","releasePartDone","takePartDone", "getStatus","releasePart","takePart","MAX"};

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
	static public class PTransportPort extends PortBase {
		// constructors
		public PTransportPort(IInterfaceItemOwner actor, String name, int localId) {
			this(actor, name, localId, 0);
		}
		public PTransportPort(IInterfaceItemOwner actor, String name, int localId, int idx) {
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
		public void isFull() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[OUT_isFull]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), OUT_isFull));
		}
		public void isEmpty() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[OUT_isEmpty]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), OUT_isEmpty));
		}
		public void releasePartDone() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[OUT_releasePartDone]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), OUT_releasePartDone));
		}
		public void takePartDone() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[OUT_takePartDone]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), OUT_takePartDone));
		}
	}
	
	// replicated port class
	static public class PTransportReplPort extends ReplicatedPortBase {
	
		public PTransportReplPort(IInterfaceItemOwner actor, String name, int localId) {
			super(actor, name, localId);
		}
		
		public int getReplication() {
			return getNInterfaceItems();
		}
		
		public int getIndexOf(InterfaceItemBase ifitem){
				return ifitem.getIdx();
			}
		
		public PTransportPort get(int idx) {
			return (PTransportPort) getInterfaceItem(idx);
		}
		
		protected InterfaceItemBase createInterfaceItem(IInterfaceItemOwner rcv, String name, int lid, int idx) {
			return new PTransportPort(rcv, name, lid, idx);
		}
		
		// outgoing messages
		public void isFull(){
			for (InterfaceItemBase item : getItems()) {
				((PTransportPort)item).isFull();
			}
		}
		public void isEmpty(){
			for (InterfaceItemBase item : getItems()) {
				((PTransportPort)item).isEmpty();
			}
		}
		public void releasePartDone(){
			for (InterfaceItemBase item : getItems()) {
				((PTransportPort)item).releasePartDone();
			}
		}
		public void takePartDone(){
			for (InterfaceItemBase item : getItems()) {
				((PTransportPort)item).takePartDone();
			}
		}
	}
	
	
	// port class
	static public class PTransportConjPort extends PortBase {
		// constructors
		public PTransportConjPort(IInterfaceItemOwner actor, String name, int localId) {
			this(actor, name, localId, 0);
		}
		public PTransportConjPort(IInterfaceItemOwner actor, String name, int localId, int idx) {
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
		public void getStatus() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_getStatus]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), IN_getStatus));
		}
		public void releasePart() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_releasePart]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), IN_releasePart));
		}
		public void takePart() {
			DebuggingService.getInstance().addMessageAsyncOut(getAddress(), getPeerAddress(), messageStrings[IN_takePart]);
			if (getPeerAddress()!=null)
				getPeerMsgReceiver().receive(new EventMessage(getPeerAddress(), IN_takePart));
		}
	}
	
	// replicated port class
	static public class PTransportConjReplPort extends ReplicatedPortBase {
	
		public PTransportConjReplPort(IInterfaceItemOwner actor, String name, int localId) {
			super(actor, name, localId);
		}
		
		public int getReplication() {
			return getNInterfaceItems();
		}
		
		public int getIndexOf(InterfaceItemBase ifitem){
				return ifitem.getIdx();
			}
		
		public PTransportConjPort get(int idx) {
			return (PTransportConjPort) getInterfaceItem(idx);
		}
		
		protected InterfaceItemBase createInterfaceItem(IInterfaceItemOwner rcv, String name, int lid, int idx) {
			return new PTransportConjPort(rcv, name, lid, idx);
		}
		
		// incoming messages
		public void getStatus(){
			for (InterfaceItemBase item : getItems()) {
				((PTransportConjPort)item).getStatus();
			}
		}
		public void releasePart(){
			for (InterfaceItemBase item : getItems()) {
				((PTransportConjPort)item).releasePart();
			}
		}
		public void takePart(){
			for (InterfaceItemBase item : getItems()) {
				((PTransportConjPort)item).takePart();
			}
		}
	}
	
}
