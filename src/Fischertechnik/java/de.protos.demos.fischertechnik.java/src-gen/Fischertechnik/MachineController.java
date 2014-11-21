package Fischertechnik;

import org.eclipse.etrice.runtime.java.messaging.*;
import org.eclipse.etrice.runtime.java.modelbase.*;
import org.eclipse.etrice.runtime.java.debugging.*;

import static org.eclipse.etrice.runtime.java.etunit.EtUnit.*;

import Actuators.*;
import AutomationProtocols.*;
import GenericLineElements.*;
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



public class MachineController extends ActorClassBase {

	
	//--------------------- ports
	
	//--------------------- saps
	
	//--------------------- services
	
	//--------------------- optional actors
	
	//--------------------- interface item IDs
	
	/*--------------------- attributes ---------------------*/
	/*--------------------- operations ---------------------*/

	//--------------------- construction
	public MachineController(IRTObject parent, String name) {
		super(parent, name);
		setClassName("MachineController");
		
		// initialize attributes

		// own ports
		
		// own saps
		
		// own service implementations
		
		// sub actors
		DebuggingService.getInstance().addMessageActorCreate(this, "SourceSensor1");
		new SourceSensor(this, "SourceSensor1");
		DebuggingService.getInstance().addMessageActorCreate(this, "BeltStation2");
		new BeltStation(this, "BeltStation2");
		DebuggingService.getInstance().addMessageActorCreate(this, "PusherStation3");
		new PusherStation(this, "PusherStation3");
		DebuggingService.getInstance().addMessageActorCreate(this, "ProductionStation4");
		new ProductionStation(this, "ProductionStation4");
		DebuggingService.getInstance().addMessageActorCreate(this, "ProductionStation5");
		new ProductionStation(this, "ProductionStation5");
		DebuggingService.getInstance().addMessageActorCreate(this, "PusherStation6");
		new PusherStation(this, "PusherStation6");
		DebuggingService.getInstance().addMessageActorCreate(this, "BeltStation7");
		new BeltStation(this, "BeltStation7");
		DebuggingService.getInstance().addMessageActorCreate(this, "SinkSensor8");
		new SinkSensor(this, "SinkSensor8");
		
		// wiring
		InterfaceItemBase.connect(this, "BeltStation2/InlineStation/prev", "SourceSensor1/next");
		InterfaceItemBase.connect(this, "PusherStation3/InlineStation/prev", "BeltStation2/InlineStation/next");
		InterfaceItemBase.connect(this, "ProductionStation4/InlineStation/prev", "PusherStation3/InlineStation/next");
		InterfaceItemBase.connect(this, "ProductionStation4/InlineStation/next", "ProductionStation5/InlineStation/prev");
		InterfaceItemBase.connect(this, "ProductionStation5/InlineStation/next", "PusherStation6/InlineStation/prev");
		InterfaceItemBase.connect(this, "PusherStation6/InlineStation/next", "BeltStation7/InlineStation/prev");
		InterfaceItemBase.connect(this, "BeltStation7/InlineStation/next", "SinkSensor8/prev");
		
		

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
