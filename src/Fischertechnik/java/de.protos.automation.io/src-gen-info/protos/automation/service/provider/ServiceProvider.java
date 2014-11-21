package protos.automation.service.provider;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import protos.automation.service.io.*;
import room.basic.service.timing.*;
import protos.automation.service.io.PDigIn.*;
import protos.automation.service.io.PDigInSim.*;
import protos.automation.service.io.PDigOut.*;
import protos.automation.service.io.PDigOutSim.*;
import protos.automation.service.io.PIOEvent.*;
import room.basic.service.timing.PTimer.*;



public class ServiceProvider extends ActorClassBase {

	
	//--------------------- ports
	
	//--------------------- saps
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public ServiceProvider(IRTObject parent, String name) {
		super(parent, name);
		setClassName("ServiceProvider");
		
		// initialize attributes

		// own ports
		
		// own saps
		
		// own service implementations
		
		// sub actors
		DebuggingService.getInstance().addMessageActorCreate(this, "timingService");
		new ATimingService(this, "timingService");
		DebuggingService.getInstance().addMessageActorCreate(this, "ioService");
		new AIOService(this, "ioService");
		
		// wiring
		InterfaceItemBase.connect(this, "timingService/timer", "ioService/polling_timer");
		
		

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
