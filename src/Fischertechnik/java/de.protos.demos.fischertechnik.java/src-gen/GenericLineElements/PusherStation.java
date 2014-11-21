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
import AutomationProtocols.PInlineElement.*;
import AutomationProtocols.PLinearUnit.*;
import AutomationProtocols.PProcessing.*;
import room.basic.service.timing.PTimer.*;
import AutomationProtocols.PTransport.*;



public class PusherStation extends ActorClassBase {

	
	//--------------------- ports
	
	//--------------------- saps
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public PusherStation(IRTObject parent, String name) {
		super(parent, name);
		setClassName("PusherStation");
		
		// initialize attributes

		// own ports
		
		// own saps
		
		// own service implementations
		
		// sub actors
		DebuggingService.getInstance().addMessageActorCreate(this, "InlineStation");
		new GenericInlineStation(this, "InlineStation");
		DebuggingService.getInstance().addMessageActorCreate(this, "Pusher");
		new Pusher(this, "Pusher");
		
		// wiring
		InterfaceItemBase.connect(this, "InlineStation/transport", "Pusher/fct");
		
		

	}
	
	/* --------------------- attribute setters and getters */
	
	
	//--------------------- port getters

	//--------------------- lifecycle functions
	public void stop(){
		stopUser();
		super.stop();
	}
	
	public void destroy() {
		DebuggingService.getInstance().addMessageActorDestroy(this);
		super.destroy();
	}

	//--------------------- no state machine
	public void receiveEvent(InterfaceItemBase ifitem, int evt, Object data) {
		handleSystemEvent(ifitem, evt, data);
	}
	
	public void executeInitTransition() {}
	
	
};
